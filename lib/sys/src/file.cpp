/*
Copyright (C) 2019 Mihai Vasilian
*/

#include "file.hpp"
#include "stream.hpp"
#include "filename.hpp"
#include "vector.hpp"

// Include Platform/OS headers
#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif


namespace sys
{
    file::file()
    {
        m_depth = 0;
    }

    file::~file()
    {
    }

    void file::scandir(
        const stl::string& dir,
        unsigned int flags,
        size_t max_depth,
        scan_callback cb)
    {
        bool aborting = false;
        return scandir_(dir, flags, max_depth, cb, aborting);
    }

    void file::scandir_(const stl::string& dir, unsigned int flags, size_t max_depth, scan_callback cb, bool& aborting)
    {
        // Activate debugging
        static bool logging = false;

#ifdef WIN32
        //  Sanitize the given directory path.
        sys::filename dirfn(dir);
        stl::string allfiles = dirfn.get_directory();
        allfiles += U("*");

        // Discovered file
        stl::string filepath;

        /*  Searches a directory for a file or subdirectory with a name
            that matches a specific name, or partial name if wildcards are used.
        */
        WIN32_FIND_DATA ffd;
        HANDLE hfind = FindFirstFile(allfiles.c_str(), &ffd);
        if (hfind == INVALID_HANDLE_VALUE)
            return;

        do
        {
            bool showAttr = false;
            bool aDir = ((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY);

            // Is a file
            if (!aDir)
            {
                bool aHiddenFile = ((ffd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) == FILE_ATTRIBUTE_HIDDEN);

                if (!aHiddenFile ||
                    (flags & S_HIDDEN_FILE))
                {
                    // Discovered file with full path
                    filepath = dirfn.get_directory();
                    filepath += ffd.cFileName;
                    cb(filepath, aborting);

                    if (aborting)
                        break;

                    if (logging)
                    {
                        // File Name
                        stl::cout << ffd.cFileName << " ";
                        // File Size
                        LARGE_INTEGER filesize;
                        filesize.LowPart = ffd.nFileSizeLow;
                        filesize.HighPart = ffd.nFileSizeHigh;
                        stl::cout << filesize.QuadPart << " bytes ";

                        // Allow attributes
                        showAttr = true;
                    }
                }
            }


            // Is a directory
            bool aDotDir = false;
            bool aHiddenDir = false;
            if (aDir)
            {
                aDotDir =
                    _tcscmp(ffd.cFileName, U(".")) == 0 ||
                    _tcscmp(ffd.cFileName, U("..")) == 0;

                aHiddenDir = ((ffd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) == FILE_ATTRIBUTE_HIDDEN);

                if ((!aHiddenDir && !aDotDir) ||
                    (aHiddenDir && (flags & S_HIDDEN_DIR)) ||
                    (aDotDir && (flags & S_DOT_DIRS)))
                {
                    // Discovered directory with full path
                    filepath = dirfn.get_directory();
                    filepath += ffd.cFileName;
                    filepath += sys::filename::SSEP;
                    cb(filepath, aborting);

                    if (aborting)
                        break;

                    if (logging)
                    {
                        stl::cout << ffd.cFileName << " ";

                        // Allow attributes
                        showAttr = true;
                    }
                }
            }

            // Show file attributes
            if (showAttr)
            {
                // File Attributes
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
                    stl::cout << "FILE_ATTRIBUTE_ARCHIVE ";
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED)
                    stl::cout << "FILE_ATTRIBUTE_COMPRESSED ";
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DEVICE)
                    stl::cout << "FILE_ATTRIBUTE_DEVICE ";
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                    stl::cout << "FILE_ATTRIBUTE_DIRECTORY ";
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED)
                    stl::cout << "FILE_ATTRIBUTE_ENCRYPTED ";
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
                    stl::cout << "FILE_ATTRIBUTE_HIDDEN ";
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_INTEGRITY_STREAM)
                    stl::cout << "FILE_ATTRIBUTE_INTEGRITY_STREAM ";
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_NORMAL)
                    stl::cout << "FILE_ATTRIBUTE_NORMAL ";
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED)
                    stl::cout << "FILE_ATTRIBUTE_NOT_CONTENT_INDEXED ";
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_OFFLINE)
                    stl::cout << "FILE_ATTRIBUTE_OFFLINE ";
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
                    stl::cout << "FILE_ATTRIBUTE_READONLY ";
                //if (ffd.dwFileAttributes & FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS)
                //    stl::cout << "FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS ";
                //if (ffd.dwFileAttributes & FILE_ATTRIBUTE_RECALL_ON_OPEN)
                //    stl::cout << "FILE_ATTRIBUTE_RECALL_ON_OPEN ";
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)
                    stl::cout << "FILE_ATTRIBUTE_REPARSE_POINT ";
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_SPARSE_FILE)
                    stl::cout << "FILE_ATTRIBUTE_SPARSE_FILE ";
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)
                    stl::cout << "FILE_ATTRIBUTE_SYSTEM ";
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY)
                    stl::cout << "FILE_ATTRIBUTE_TEMPORARY ";
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_VIRTUAL)
                    stl::cout << "FILE_ATTRIBUTE_VIRTUAL ";
                stl::cout << std::endl;
            }


            // Should traverse a directory?
            bool traverse = false;
            if (aDir &&                                                 // is a directory
                !aDotDir &&                                             // not a '.' or '..'
                (flags & S_TRAVERSE) &&                                 // should traverse
                (!aHiddenDir ||                                         // not hidden or
                 flags & S_HIDDEN_DIR))                                 // hidden but allowed
            {
                traverse = true;
            }

            if (traverse)
            {
                if (m_depth < max_depth)
                {
                    m_depth++;
                    scandir_(filepath.c_str(), flags, max_depth, cb, aborting);
                    m_depth--;
                }
            }

        } while (!aborting && FindNextFile(hfind, &ffd) != 0);

        FindClose(hfind);
#else // Linux

        struct dirent **namelist;
        int n = ::scandir(dir, &namelist, NULL, alphasort);
        if (n < 0)
            return;

        // discovered file or directory
        stl::string filepath;

        // subdirectories to traverse
        stl::vector<stl::string> subdirs;

        for (int i = 0; i < n; ++i)
        {
            bool showAttr = false;
            bool aDir = (namelist[i]->d_type == DT_DIR);

            // Is a file
            if (!aDir)
            {
                size_t slen = strlen(namelist[i]->d_name);
                bool aHiddenFile = (slen > 0 && namelist[i]->d_name[slen-1] == '~');

                if (!aHiddenFile ||
                    (flags & S_HIDDEN_FILE))
                {
                    // Discovered file with full path
                    sys::filename dirfn(dir);
                    filepath = dirfn.get_directory();
                    filepath += namelist[i]->d_name;
                    cb(filepath, aborting);

                    if (aborting)
                        break;

                    if (logging)
                    {
                        // File Name
                        stl::cout << namelist[i]->d_name << " ";
                        // File Size
                        struct stat statbuf;
                        if (stat(filepath.c_str(), &statbuf) == 0)
                        {
                            stl::cout << statbuf.st_size << " bytes";
                        }

                        // Allow attributes
                        showAttr = true;
                    }
                }
            }

            // Is a directory
            bool aDotDir = false;
            bool aHiddenDir = false;
            if (aDir)
            {
                aDotDir =
                    strcmp(namelist[i]->d_name, ".") == 0 ||
                    strcmp(namelist[i]->d_name, "..") == 0;

                size_t slen = strlen(namelist[i]->d_name);
                aHiddenDir =
                    !aDotDir &&
                    slen > 0 &&
                    namelist[i]->d_name[0] == '.';

                if ((!aHiddenDir && !aDotDir) ||
                    (aHiddenDir && (flags & S_HIDDEN_DIR)) ||
                    (aDotDir && (flags & S_DOT_DIRS)))
                {
                    // Discovered directory with full path
                    sys::filename dirfn(dir);
                    filepath = dirfn.get_directory();
                    filepath += namelist[i]->d_name;
                    filepath += sys::filename::SSEP;
                    cb(filepath, aborting);

                    if (aborting)
                        break;

                    if (logging)
                    {
                        stl::cout << namelist[i]->d_name << " ";

                        // Allow attributes
                        showAttr = true;
                    }
                }
            }

            // Show file attributes
            if (showAttr)
            {
                switch(namelist[i]->d_type)
                {
                case DT_BLK:
                    stl::cout << "This is a block device.";
                    break;
                case DT_CHR:
                    stl::cout << "This is a character device.";
                    break;
                case DT_DIR:
                    stl::cout << "This is a directory.";
                    break;
                case DT_FIFO:
                    stl::cout << "This is a named pipe (FIFO).";
                    break;
                case DT_LNK:
                    stl::cout << "This is a symbolic link.";
                    break;
                case DT_REG:
                    stl::cout << "This is a regular file.";
                    break;
                case DT_SOCK:
                    stl::cout << "This is a UNIX domain socket.";
                    break;
                case DT_UNKNOWN:
                    stl::cout << "The file type could not be determined.";
                    break;
                }
                stl::cout << std::endl;
            }

            // Should traverse a directory?
            bool traverse = false;
            if (aDir &&                               // is a directory
                !aDotDir &&                           // not a '.' or '..'
                (flags & S_TRAVERSE) &&               // should traverse
                (!aHiddenDir ||                       // not hidden or
                 flags & S_HIDDEN_DIR))               // hidden but allowed
            {
                traverse = true;
            }

            if (traverse)
            {
                subdirs.push_back(filepath);
            }
        }

        // Free memory
        for (int i = 0; i < n; ++i)
            free(namelist[i]);
        free(namelist);

        // traverse subdirectories
        for (size_t i = 0; i < subdirs.size() && !aborting; ++i)
        {
            if (m_depth < max_depth)
            {
                m_depth++;
                scandir_(subdirs[i].c_str(), flags, max_depth, cb, aborting);
                m_depth--;
            }
        }
#endif
    }
} // namespace
