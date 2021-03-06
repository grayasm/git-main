/*
  Copyright (C) 2009 Mihai Vasilian

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program. If not, see http://www.gnu.org/licenses/.

  contact: grayasm@gmail.com
*/


//c++
//exp
#include "filename.hpp"

#ifdef _WIN32
#include <io.h>
#endif // _WIN32


namespace sys
{
    
    //TODO: the path separator should be configurable and not platform dependent.
    //      can edit linux files on win32 or opposite

#ifdef _WIN32
#ifdef __MINGW32__
    const stl::char_t filename::SEP(U('/'));
    const stl::string filename::SSEP(U("/"));
#else
    const stl::char_t filename::SEP(U('\\'));
    const stl::string filename::SSEP(U("\\"));
#endif//__MINGW32__
#else /*POSIX*/
    const stl::char_t filename::SEP(U('/'));
    const stl::string filename::SSEP(U("/"));
#endif




    filename::filename(){}
    filename::~filename(){}

    filename::filename(const stl::string& file) //e.g. "/home/mihk/vParser.cpp" or "vParser.cpp"
    {
        extract_directory(m_directory, file);
        extract_core_name(m_core_name, file);
        extract_extension(m_extension, file);
    }

    filename::filename(const stl::string& directory, //e.g. "/home/mihk/"
                       const stl::string& file_core_name, //e.g. "vParser"
                       const stl::string& file_ext)
    {
        m_directory=directory ;
        m_core_name=file_core_name;
        m_extension=file_ext;

        format_directory(m_directory);
        format_file(m_core_name);
        format_extension(m_extension);
    } //e.g. "cpp"

    filename::filename(const sys::filename& file_name)
    {
        *this=(file_name);
    }

    filename& filename::operator=(const sys::filename& tocopy)
    {
        if(this!=&tocopy)
        {
            m_directory=tocopy.m_directory;
            m_core_name=tocopy.m_core_name;
            m_extension=tocopy.m_extension;
        }//if
        return *this;
    }


    bool filename::operator==(const sys::filename& tocmp)
    {
	    if(m_directory.compare(tocmp.m_directory) == 0 &&
	       m_core_name.compare(tocmp.m_core_name) == 0 &&
	       m_extension.compare(tocmp.m_extension) == 0)
        {
            return true;
        }
        return false;
    }

    bool filename::operator!=(const sys::filename& tocmp)
    {
        return !(*this==tocmp);
    }


    const stl::string& filename::get_directory() const
    {
        return m_directory ;
    }

    const stl::string& filename::get_core_name() const
    {
        return m_core_name;
    }

    stl::string filename::get_file_name() const
    {
        stl::string file_name(m_core_name);
        file_name+=U('.');
        file_name+=m_extension;
        return file_name;
    }

    stl::string filename::get_path() const
    {
        stl::string file_path(m_directory);
        file_path+=m_core_name;
        if( !m_extension.empty() )
        {
            file_path+=U('.');
            file_path+=m_extension;
        }//if

        return file_path;
    }

    const stl::string& filename::get_extension() const
    {
        return m_extension;
    }

    void filename::set_directory(const stl::string& directory)
    {
        m_directory=directory;
        format_directory(m_directory);
    }

    void filename::set_core_name(const stl::string& file_core_name)
    {
        m_core_name=file_core_name;
        format_file(m_core_name);
    }

    void filename::set_file_name(const stl::string& file_name)
    {
        extract_core_name(m_core_name, file_name);
        extract_extension(m_extension, file_name);
    }

    void filename::set_extension(const stl::string& extension)
    {
        m_extension=extension;
        format_extension(m_extension);
    }

    void filename::set_path(const stl::string& complete_path)
    {
        extract_directory(m_directory, complete_path);
        extract_core_name(m_core_name, complete_path);
        extract_extension(m_extension, complete_path);
    }


    void filename::add_prefix_directory(const stl::string& directory)
    {
        stl::string tmpdir(directory);
        stl::trim_left(tmpdir, U(' '));
        stl::trim_left(tmpdir, SEP);
        //format right side of string
        format_directory(tmpdir);

        size_t sep_pos = m_directory.find_first_of(SEP);
        if(sep_pos!=stl::string::npos)
        {
            m_directory.insert(sep_pos+1, tmpdir);
        }
        else
        {
            stl::string newstr(SEP+tmpdir);
            m_directory.insert(0, newstr);
        }
    }

    void filename::add_postfix_directory(const stl::string& directory)
    {
        stl::string tmpdir(directory);
        stl::trim_left(tmpdir, U(' '));
        stl::trim_left(tmpdir, SEP);
        //format right side
        format_directory(tmpdir);
        m_directory+=tmpdir;
    }

    filename filename::substract_prefix_directory() const
    {
        size_t sep1=m_directory.find_first_of(SEP);
        if(sep1!=stl::string::npos)
        {
            size_t sep2=m_directory.find_first_of(SEP, sep1+1);
            if(sep2!=stl::string::npos)
            {
                stl::string tmpdir=m_directory.substr(0, sep1);
                tmpdir+=m_directory.substr(sep2, m_directory.size()-sep2);
                return filename(tmpdir, m_core_name, m_extension);
            }
            else
            {
                stl::string tmpdir=m_directory.substr(0, sep1+1);
                return tmpdir ;
            }
        }
        else
        {
            return filename(*this);
        }
    }

    filename filename::substract_postfix_directory() const
    {
        size_t sep1=m_directory.find_last_of(SEP);
        if(sep1!=stl::string::npos)
        {
            size_t sep2=m_directory.find_last_of(SEP, sep1-1);
            if(sep2!=stl::string::npos)
            {
                stl::string tmpdir=m_directory.substr(0, sep2+1);
                return filename(tmpdir, m_core_name, m_extension);
            }
            else
            {
                stl::string tmpdir=m_directory.substr(0, sep1+1);
                return tmpdir ;
            }
        }//if
        else
        {
            return filename(*this);
        }//else
    }

    bool filename::access(int mode)const
    {
#ifdef UNICODE
        return (::_waccess(get_path().c_str(), mode)==0);
#else
        return (::access(get_path().c_str(), mode)==0);
#endif
    }

    void filename::extract_directory(stl::string& dest, const stl::string& src)
    {
        size_t sep_pos = src.find_last_of(SEP);
        if(sep_pos == stl::string::npos)
        {
            dest=U("");
            return ;
        }//if
        else
        {
            dest = src.substr(0, sep_pos+1);//include last SEP
            return ;
        }//else
    }

    void filename::extract_core_name(stl::string& dest, const stl::string& src)
    {
        if(src.empty())
        {
            dest=U("");
            return ;
        }//if

        size_t dir_lpos = src.find_last_of(SEP);
        if(dir_lpos != stl::string::npos)
        {
            size_t dot_pos = src.find_last_of(U('.'));
            if(dot_pos != stl::string::npos && dot_pos > dir_lpos)
            {
                dest = src.substr(dir_lpos+1, dot_pos-dir_lpos-1);
            }//if '.' exist
            else
            {
                dest = src.substr(dir_lpos+1, src.size()-dir_lpos-1);
            }//else no '.'
        }//if exist SEP (dir)
        else
        {
            size_t dot_pos = src.find_last_of(U('.'));
            if(dot_pos != stl::string::npos)
            {
                dest = src.substr(0, dot_pos);
            }//if dot_pos null
            else
            {
                dest = src;
            }//else
        }//else no SEP (dir)
    }

    void filename::extract_extension(stl::string& dest, const stl::string& src)
    {
        size_t dir_lpos = src.find_last_of(SEP);
        if(dir_lpos != stl::string::npos)
        {
            size_t dot_pos = src.find_last_of(U('.'));
            if(dot_pos != stl::string::npos && dot_pos > dir_lpos)
            {
                dest = src.substr(dot_pos+1, src.size()-dot_pos-1);
            }//if '.' exist
            else
            {
                dest=U("");
            }//else no '.'
        }//if SEP exist
        else
        {
            size_t dot_pos = src.find_last_of(U('.'));
            if(dot_pos != stl::string::npos)
            {
                dest = src.substr(dot_pos+1, src.size()-dot_pos-1);
            }//if dot_pos null
            else
            {
                dest=U("");
            }
        }//else no SEP
    }

    void filename::format_directory(stl::string& directory)
    {
        if(!directory.empty())
        {
            if(*(directory.rbegin())!=SEP)
            {
                stl::trim_right(directory, U(' '));
                directory += SEP ;
            }//if
        }//if
    }

    void filename::format_file(stl::string& file)
    {
        stl::trim_left(file, U(' '));

        stl::trim_left(file, SEP);
        if(file.find_first_of(SEP)!=stl::string::npos)
            throw 0;
    }

    void filename::format_extension(stl::string& ext)
    {
        stl::trim_left(ext, U(' '));
        stl::trim_right(ext, U(' '));
        stl::trim_left(ext, U('.'));
        if(ext.find_first_of(SEP)!=stl::string::npos)
            throw 0;//stl::exception(0, U("Invalid file extension."));
    }

}  // namespace exp

