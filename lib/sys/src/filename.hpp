/*
Copyright (C) 2009 Mihai Vasilian
*/


#ifndef __filename_hpp__
#define __filename_hpp__

//exp
#include "string.hpp"
#include "strconv.hpp"
#include "stdio.hpp"





namespace sys
{
    class filename
    {
    public:
        filename();
        ~filename();

        //the "/" will be replaced with SEP according to OS
        filename(const stl::string& file); //e.g. "/home/mihk/vParser.cpp" or "vParser.cpp"
        filename(const stl::string& directory, //e.g. "/home/mihk/"
                 const stl::string& file_core_name, //e.g. "vParser"
                 const stl::string& file_ext); //e.g. "cpp"

        filename(const sys::filename& file_name);
        filename& operator=(const sys::filename& tocopy);
        bool operator==(const sys::filename& tocmp);
        bool operator!=(const sys::filename& tocmp);


        const stl::string& get_directory() const ; // "/home/mihk/repository/project/src/"
        const stl::string& get_core_name() const ;//  "Parser"
        stl::string get_file_name() const ; // "Parser.cpp" (file+ext)
        stl::string get_path() const ;// "/home/mihk/repository/project/src/Parser.cpp"
        const stl::string& get_extension() const ;// "cpp"

        void set_directory(const stl::string& directory) ;
        void set_core_name(const stl::string& file_core_name);
        void set_file_name(const stl::string& file_name);
        void set_extension(const stl::string& extension);
        void set_path(const stl::string& complete_path);


        void add_prefix_directory(const stl::string& directory);
        void add_postfix_directory(const stl::string& directory);

        filename substract_prefix_directory() const ;
        filename substract_postfix_directory() const ;

        //R_OK test for read permission
        //W_OK test for write permission
        //X_OK test for execute permission
        //F_OK test for existance
        bool access(int mode)const ;


    public:
        //members
        static const stl::char_t SEP;// separator char_t
        static const stl::string SSEP;// separator string

    protected:
        static void extract_directory(stl::string& dest, const stl::string& src);
        static void extract_core_name(stl::string& dest, const stl::string& src);
        static void extract_extension(stl::string& dest, const stl::string& src) ;

        static void merge_directories(stl::string& dest,
                                      const stl::string& dir1,
                                      const stl::string& dir2);

        static void format_directory(stl::string& directory);
        static void format_file(stl::string& file);
        static void format_extension(stl::string& ext);


    private:
//TODO: "change to internal string"
	    stl::string m_directory;
	    stl::string m_core_name;
        stl::string m_extension;

    };  // filename
}  // namespace exp


#endif//__filename_hpp__
