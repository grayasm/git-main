/*
Copyright (C) 2009 Mihai Vasilian
*/



//this
#include "test_filename.hpp"


//c++
#include <iostream>


//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


//libraries
#include "stream.hpp"



//###########################FILENAME TEST CLASS ####################################
void test_filename::setUp()
{
}

void test_filename::tearDown()
{
}





//CPPUNIT_ASSERT( a==b );
//CPPUNIT_ASSERT_EQUAL(it,ip);
//CPPUNIT_ASSERT(it==ip);
//CPPUNIT_ASSERT_EQUAL(t,p);


void test_filename::test0()
{
    stl::cout << "\n\n\t*******************************************************";
    stl::cout <<   "\n\t* TESTING HEADER: filename.hpp                        *";
    stl::cout <<   "\n\t*******************************************************";


    // 0 0 0 -> 0 0 0
    stl::string dir(U(""));
    stl::string fil(U(""));
    stl::string ext(U(""));

    stl::string filepath(dir); 
    filepath += fil; /*filepath+=U(".");*/ 
    filepath += ext;

    sys::filename filename(filepath);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);

    filename=sys::filename(dir, fil, ext);//constr(x,y,z);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);

    sys::filename filename_0(filename);//copy constr

    CPPUNIT_ASSERT(filename_0.get_directory()==dir &&
                   filename_0.get_core_name()==fil &&
                   filename_0.get_extension()==ext);

    sys::filename filename_1 ;
    filename_1 = filename_0 ;//operator =

    CPPUNIT_ASSERT(filename_1.get_directory()==dir &&
                   filename_1.get_core_name()==fil &&
                   filename_1.get_extension()==ext);

    CPPUNIT_ASSERT(filename_0 == filename_1);//operator ==
    CPPUNIT_ASSERT( !(filename_0 != filename_1) );//operator !=


    //2nd PART ALTERING THE PATH
    CPPUNIT_ASSERT(filename.get_path()==filepath);
    filename.set_directory(dir);
    filename.set_core_name(fil);
    filename.set_extension(ext);
    CPPUNIT_ASSERT(filename.get_path()==filepath);
    filename.set_path(filepath);
    CPPUNIT_ASSERT(filename.get_path()==filepath);

    // PREFIX /predir . 1/predir ..2/  -> /predir . 1/predir ..2/
    stl::string pre_dir1(
        sys::filename::SSEP+
        U("predir . 1")+
        sys::filename::SSEP+
        U("predir ..2")+
        sys::filename::SSEP);

    filename.add_prefix_directory(pre_dir1);
    stl::string filepath_1=
        dir.empty()==true?pre_dir1:pre_dir1.substr(0, pre_dir1.size()-1)+
        dir+
        fil+
        (ext.empty()==true?U(""):(U(".")+ext));

    //-> /predir . 1/predir ..2/
    stl::string dump_file1 = filename.get_path();
    stl::string dump_file1a = filepath_1;
    stl::string filename_path = filename.get_path();

    CPPUNIT_ASSERT(filename_path == filepath_1);

    // POSTFIX  /post .fake.ext/ -> /predir . 1/predir ..2/  + dir +   /post .fake.ext/
    // -> /predir . 1/predir ..2/post .fake.ext/
    stl::string post_dir2(sys::filename::SSEP+
                           U("post .fake.ext")+
                           sys::filename::SSEP);

    filename.add_postfix_directory(post_dir2);
    stl::string filepath_2;
    if(dir.empty())
    {
        filepath_2 =
            pre_dir1.substr(0, pre_dir1.size()-1)+
            post_dir2+
            fil+
            (ext.empty()==true?U(""):U("."))+
            ext;
    }//if
    else
    {
        filepath_2 =
            pre_dir1.substr(0, pre_dir1.size()-1)+
            dir+
            post_dir2.substr(1, post_dir2.size()-1)+
            fil+(ext.empty() == true ? U(""):U("."))+
            ext;
    }//else
    CPPUNIT_ASSERT(filename.get_path()==filepath_2);

    //substract /predir ..2/ + dir + /post .fake.ext/
    sys::filename filename_3 = filename.substract_prefix_directory();

    stl::string filepath_3 = sys::filename::SSEP+ U("predir ..2")+ sys::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        post_dir2.substr(1, post_dir2.size()-1)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_3.get_path()==filepath_3);

    //substract POSTFIX -> /predir ..2/ + dir
    sys::filename filename_4 = filename_3.substract_postfix_directory();

    stl::string filepath_4 =  sys::filename::SSEP+U("predir ..2")+sys::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;

    stl::string dump_file4=filename_4.get_path();
    stl::string dump_file4a=filepath_4;
    CPPUNIT_ASSERT(filename_4.get_path()==filepath_4);



    //substract prefix dir -> dir
    sys::filename filename_5 = filename_4.substract_prefix_directory();
    stl::string filepath_5 =
        (dir.empty()==true?sys::filename::SSEP:dir)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_5.get_path()==filepath_5);

}


void test_filename::test1()
{
    // / 0 0 -> /
    stl::string dir(sys::filename::SSEP);
    stl::string fil(U(""));
    stl::string ext(U(""));

    stl::string filepath(dir); filepath+=fil; /*filepath+=U(".");*/ filepath+=ext;

    sys::filename filename(filepath);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);

    filename=sys::filename(dir, fil, ext);//constr(x,y,z);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);

    sys::filename filename_0(filename);//copy constr

    CPPUNIT_ASSERT(filename_0.get_directory()==dir &&
                   filename_0.get_core_name()==fil &&
                   filename_0.get_extension()==ext);

    sys::filename filename_1 ;
    filename_1 = filename_0 ;//operator =

    CPPUNIT_ASSERT(filename_1.get_directory()==dir &&
                   filename_1.get_core_name()==fil &&
                   filename_1.get_extension()==ext);


    CPPUNIT_ASSERT(filename_0 == filename_1);//operator ==
    CPPUNIT_ASSERT( !(filename_0 != filename_1) );//operator !=



    //2nd PART ALTERING THE PATH
    CPPUNIT_ASSERT(filename.get_path()==filepath);
    filename.set_directory(dir);
    filename.set_core_name(fil);
    filename.set_extension(ext);
    CPPUNIT_ASSERT(filename.get_path()==filepath);
    filename.set_path(filepath);
    CPPUNIT_ASSERT(filename.get_path()==filepath);

    // PREFIX /predir . 1/predir ..2/  -> /predir . 1/predir ..2/
    stl::string pre_dir1(
        sys::filename::SSEP+
        U("predir . 1")+
        sys::filename::SSEP+
        U("predir ..2")+
        sys::filename::SSEP);

    filename.add_prefix_directory(pre_dir1);
    stl::string filepath_1=
        dir.empty()==true?pre_dir1:pre_dir1.substr(0, pre_dir1.size()-1)+
        dir+
        fil+
        (ext.empty()==true?U(""):(U(".")+ext));

    //-> /predir . 1/predir ..2/
    stl::string dump_file1=filename.get_path();
    stl::string dump_file1a=filepath_1;

    CPPUNIT_ASSERT(filename.get_path()==filepath_1);

    // POSTFIX  /post .fake.ext/ -> /predir . 1/predir ..2/  + dir +   /post .fake.ext/
    // -> /predir . 1/predir ..2/post .fake.ext/
    stl::string post_dir2(sys::filename::SSEP+
                           U("post .fake.ext")+
                           sys::filename::SSEP);

    filename.add_postfix_directory(post_dir2);
    stl::string filepath_2;
    if(dir.empty())
    {
        filepath_2 =
            pre_dir1.substr(0, pre_dir1.size()-1)+
            post_dir2+
            fil+
            (ext.empty()==true?U(""):U("."))+
            ext;
    }//if
    else
    {
        filepath_2 =
            pre_dir1.substr(0, pre_dir1.size()-1)+
            dir+
            post_dir2.substr(1, post_dir2.size()-1)+
            fil+(ext.empty() == true ? U(""):U("."))+
            ext;
    }//else
    CPPUNIT_ASSERT(filename.get_path()==filepath_2);

    //substract /predir ..2/ + dir + /post .fake.ext/
    sys::filename filename_3 = filename.substract_prefix_directory();

    stl::string filepath_3 = sys::filename::SSEP+ U("predir ..2")+ sys::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        post_dir2.substr(1, post_dir2.size()-1)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_3.get_path()==filepath_3);

    //substract POSTFIX -> /predir ..2/ + dir
    sys::filename filename_4 = filename_3.substract_postfix_directory();

    stl::string filepath_4 =  sys::filename::SSEP+U("predir ..2")+sys::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;

    stl::string dump_file4=filename_4.get_path();
    stl::string dump_file4a=filepath_4;
    CPPUNIT_ASSERT(filename_4.get_path()==filepath_4);



    //substract prefix dir -> dir
    sys::filename filename_5 = filename_4.substract_prefix_directory();
    stl::string filepath_5 =
        (dir.empty()==true?sys::filename::SSEP:dir)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_5.get_path()==filepath_5);



}


void test_filename::test2()
{
    // /home/ -> /home/ 0 0
    stl::string dir(sys::filename::SSEP); dir+=U("home"); dir+=sys::filename::SSEP;
    stl::string fil(U(""));
    stl::string ext(U(""));

    stl::string filepath(dir); filepath+=fil; filepath+=ext;

    sys::filename filename(filepath);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);

    filename=sys::filename(dir, fil, ext);//constr(x,y,z);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);

    sys::filename filename_0(filename);//copy constr

    CPPUNIT_ASSERT(filename_0.get_directory()==dir &&
                   filename_0.get_core_name()==fil &&
                   filename_0.get_extension()==ext);

    sys::filename filename_1 ;
    filename_1 = filename_0 ;//operator =

    CPPUNIT_ASSERT(filename_1.get_directory()==dir &&
                   filename_1.get_core_name()==fil &&
                   filename_1.get_extension()==ext);

    CPPUNIT_ASSERT(filename_0 == filename_1);//operator ==
    CPPUNIT_ASSERT( !(filename_0 != filename_1) );//operator !=





    //2nd PART ALTERING THE PATH
    CPPUNIT_ASSERT(filename.get_path()==filepath);
    filename.set_directory(dir);
    filename.set_core_name(fil);
    filename.set_extension(ext);
    CPPUNIT_ASSERT(filename.get_path()==filepath);
    filename.set_path(filepath);
    CPPUNIT_ASSERT(filename.get_path()==filepath);

    // PREFIX /predir . 1/predir ..2/  -> /predir . 1/predir ..2/
    stl::string pre_dir1(
        sys::filename::SSEP+
        U("predir . 1")+
        sys::filename::SSEP+
        U("predir ..2")+
        sys::filename::SSEP);

    filename.add_prefix_directory(pre_dir1);
    stl::string filepath_1=
        dir.empty()==true?pre_dir1:pre_dir1.substr(0, pre_dir1.size()-1)+
        dir+
        fil+
        (ext.empty()==true?U(""):(U(".")+ext));

    //-> /predir . 1/predir ..2/
    stl::string dump_file1=filename.get_path();
    stl::string dump_file1a=filepath_1;

    CPPUNIT_ASSERT(filename.get_path()==filepath_1);

    // POSTFIX  /post .fake.ext/ -> /predir . 1/predir ..2/  + dir +   /post .fake.ext/
    // -> /predir . 1/predir ..2/post .fake.ext/
    stl::string post_dir2(sys::filename::SSEP+
                           U("post .fake.ext")+
                           sys::filename::SSEP);

    filename.add_postfix_directory(post_dir2);
    stl::string filepath_2;
    if(dir.empty())
    {
        filepath_2 =
            pre_dir1.substr(0, pre_dir1.size()-1)+
            post_dir2+
            fil+
            (ext.empty()==true?U(""):U("."))+
            ext;
    }//if
    else
    {
        filepath_2 =
            pre_dir1.substr(0, pre_dir1.size()-1)+
            dir+
            post_dir2.substr(1, post_dir2.size()-1)+
            fil+(ext.empty() == true ? U(""):U("."))+
            ext;
    }//else
    CPPUNIT_ASSERT(filename.get_path()==filepath_2);

    //substract /predir ..2/ + dir + /post .fake.ext/
    sys::filename filename_3 = filename.substract_prefix_directory();

    stl::string filepath_3 = sys::filename::SSEP+ U("predir ..2")+ sys::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        post_dir2.substr(1, post_dir2.size()-1)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_3.get_path()==filepath_3);

    //substract POSTFIX -> /predir ..2/ + dir
    sys::filename filename_4 = filename_3.substract_postfix_directory();

    stl::string filepath_4 =  sys::filename::SSEP+U("predir ..2")+sys::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;

    stl::string dump_file4=filename_4.get_path();
    stl::string dump_file4a=filepath_4;
    CPPUNIT_ASSERT(filename_4.get_path()==filepath_4);



    //substract prefix dir -> dir
    sys::filename filename_5 = filename_4.substract_prefix_directory();
    stl::string filepath_5 =
        (dir.empty()==true?sys::filename::SSEP:dir)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_5.get_path()==filepath_5);


}


void test_filename::test3()
{

    // /home/mihk/file -> /home/mihk/ file 0
    stl::string dir(sys::filename::SSEP); dir+=U("home"); dir+=sys::filename::SSEP; dir+=U("mihk"); dir+=sys::filename::SSEP;
    stl::string fil(U("file"));
    stl::string ext(U(""));

    stl::string filepath(dir); filepath+=fil; filepath+=ext;

    sys::filename filename(filepath);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);


    filename=sys::filename(dir, fil, ext);//constr(x,y,z);

    sys::filename filename_0(filename);//copy constr

    CPPUNIT_ASSERT(filename_0.get_directory()==dir &&
                   filename_0.get_core_name()==fil &&
                   filename_0.get_extension()==ext);

    sys::filename filename_1 ;
    filename_1 = filename_0 ;//operator =

    CPPUNIT_ASSERT(filename_1.get_directory()==dir &&
                   filename_1.get_core_name()==fil &&
                   filename_1.get_extension()==ext);

    CPPUNIT_ASSERT(filename_0 == filename_1);//operator ==
    CPPUNIT_ASSERT( !(filename_0 != filename_1) );//operator !=





    //2nd PART ALTERING THE PATH
    CPPUNIT_ASSERT(filename.get_path()==filepath);
    filename.set_directory(dir);
    filename.set_core_name(fil);
    filename.set_extension(ext);
    CPPUNIT_ASSERT(filename.get_path()==filepath);
    filename.set_path(filepath);
    CPPUNIT_ASSERT(filename.get_path()==filepath);

    // PREFIX /predir . 1/predir ..2/  -> /predir . 1/predir ..2/
    stl::string pre_dir1(
        sys::filename::SSEP+
        U("predir . 1")+
        sys::filename::SSEP+
        U("predir ..2")+
        sys::filename::SSEP);

    filename.add_prefix_directory(pre_dir1);
    stl::string filepath_1=
        dir.empty()==true?pre_dir1:pre_dir1.substr(0, pre_dir1.size()-1)+
        dir+
        fil+
        (ext.empty()==true?U(""):(U(".")+ext));

    //-> /predir . 1/predir ..2/
    stl::string dump_file1=filename.get_path();
    stl::string dump_file1a=filepath_1;

    CPPUNIT_ASSERT(filename.get_path()==filepath_1);

    // POSTFIX  /post .fake.ext/ -> /predir . 1/predir ..2/  + dir +   /post .fake.ext/
    // -> /predir . 1/predir ..2/post .fake.ext/
    stl::string post_dir2(sys::filename::SSEP+
                           U("post .fake.ext")+
                           sys::filename::SSEP);

    filename.add_postfix_directory(post_dir2);
    stl::string filepath_2;
    if(dir.empty())
    {
        filepath_2 =
            pre_dir1.substr(0, pre_dir1.size()-1)+
            post_dir2+
            fil+
            (ext.empty()==true?U(""):U("."))+
            ext;
    }//if
    else
    {
        filepath_2 =
            pre_dir1.substr(0, pre_dir1.size()-1)+
            dir+
            post_dir2.substr(1, post_dir2.size()-1)+
            fil+(ext.empty() == true ? U(""):U("."))+
            ext;
    }//else
    CPPUNIT_ASSERT(filename.get_path()==filepath_2);

    //substract /predir ..2/ + dir + /post .fake.ext/
    sys::filename filename_3 = filename.substract_prefix_directory();

    stl::string filepath_3 = sys::filename::SSEP+ U("predir ..2")+ sys::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        post_dir2.substr(1, post_dir2.size()-1)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_3.get_path()==filepath_3);

    //substract POSTFIX -> /predir ..2/ + dir
    sys::filename filename_4 = filename_3.substract_postfix_directory();

    stl::string filepath_4 =  sys::filename::SSEP+U("predir ..2")+sys::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;

    stl::string dump_file4=filename_4.get_path();
    stl::string dump_file4a=filepath_4;
    CPPUNIT_ASSERT(filename_4.get_path()==filepath_4);



    //substract prefix dir -> dir
    sys::filename filename_5 = filename_4.substract_prefix_directory();
    stl::string filepath_5 =
        (dir.empty()==true?sys::filename::SSEP:dir)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_5.get_path()==filepath_5);


}


void test_filename::test4()
{

    // /home/mihk/parser.cpp -> /home/mihk/ parser cpp
    stl::string dir(sys::filename::SSEP); dir+=U("home"); dir+=sys::filename::SSEP; dir+=U("mihk"); dir+=sys::filename::SSEP;
    stl::string fil(U("parser"));
    stl::string ext(U("cpp"));

    stl::string filepath(dir); filepath+=fil; filepath+=U("."); filepath+=ext;

    sys::filename filename(filepath);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);


    filename=sys::filename(dir, fil, ext);//constr(x,y,z);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);


    sys::filename filename_0(filename);//copy constr

    CPPUNIT_ASSERT(filename_0.get_directory()==dir &&
                   filename_0.get_core_name()==fil &&
                   filename_0.get_extension()==ext);


    sys::filename filename_1 ;
    filename_1 = filename_0 ;//operator =

    CPPUNIT_ASSERT(filename_1.get_directory()==dir &&
                   filename_1.get_core_name()==fil &&
                   filename_1.get_extension()==ext);


    CPPUNIT_ASSERT(filename_0 == filename_1);//operator ==
    CPPUNIT_ASSERT( !(filename_0 != filename_1) );//operator !=






    //2nd PART ALTERING THE PATH
    CPPUNIT_ASSERT(filename.get_path()==filepath);
    filename.set_directory(dir);
    filename.set_core_name(fil);
    filename.set_extension(ext);
    CPPUNIT_ASSERT(filename.get_path()==filepath);
    filename.set_path(filepath);
    CPPUNIT_ASSERT(filename.get_path()==filepath);

    // PREFIX /predir . 1/predir ..2/  -> /predir . 1/predir ..2/
    stl::string pre_dir1(
        sys::filename::SSEP+
        U("predir . 1")+
        sys::filename::SSEP+
        U("predir ..2")+
        sys::filename::SSEP);

    filename.add_prefix_directory(pre_dir1);
    stl::string filepath_1=
        dir.empty()==true?pre_dir1:pre_dir1.substr(0, pre_dir1.size()-1)+
        dir+
        fil+
        (ext.empty()==true?U(""):(U(".")+ext));

    //-> /predir . 1/predir ..2/
    stl::string dump_file1=filename.get_path();
    stl::string dump_file1a=filepath_1;

    CPPUNIT_ASSERT(filename.get_path()==filepath_1);

    // POSTFIX  /post .fake.ext/ -> /predir . 1/predir ..2/  + dir +   /post .fake.ext/
    // -> /predir . 1/predir ..2/post .fake.ext/
    stl::string post_dir2(sys::filename::SSEP+
                           U("post .fake.ext")+
                           sys::filename::SSEP);

    filename.add_postfix_directory(post_dir2);
    stl::string filepath_2;
    if(dir.empty())
    {
        filepath_2 =
            pre_dir1.substr(0, pre_dir1.size()-1)+
            post_dir2+
            fil+
            (ext.empty()==true?U(""):U("."))+
            ext;
    }//if
    else
    {
        filepath_2 =
            pre_dir1.substr(0, pre_dir1.size()-1)+
            dir+
            post_dir2.substr(1, post_dir2.size()-1)+
            fil+(ext.empty() == true ? U(""):U("."))+
            ext;
    }//else
    CPPUNIT_ASSERT(filename.get_path()==filepath_2);

    //substract /predir ..2/ + dir + /post .fake.ext/
    sys::filename filename_3 = filename.substract_prefix_directory();

    stl::string filepath_3 = sys::filename::SSEP+ U("predir ..2")+ sys::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        post_dir2.substr(1, post_dir2.size()-1)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_3.get_path()==filepath_3);

    //substract POSTFIX -> /predir ..2/ + dir
    sys::filename filename_4 = filename_3.substract_postfix_directory();

    stl::string filepath_4 =  sys::filename::SSEP+U("predir ..2")+sys::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;

    stl::string dump_file4=filename_4.get_path();
    stl::string dump_file4a=filepath_4;
    CPPUNIT_ASSERT(filename_4.get_path()==filepath_4);



    //substract prefix dir -> dir
    sys::filename filename_5 = filename_4.substract_prefix_directory();
    stl::string filepath_5 =
        (dir.empty()==true?sys::filename::SSEP:dir)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_5.get_path()==filepath_5);

}



void test_filename::test5()
{



    // 0 0 cpp -> .cpp
    stl::string dir(U(""));
    stl::string fil(U(""));
    stl::string ext(U("cpp"));

    stl::string filepath(dir); filepath+=fil; filepath+=U("."); filepath+=ext;

    sys::filename filename(filepath);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);


    filename=sys::filename(dir, fil, ext);//constr(x,y,z);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);


    sys::filename filename_0(filename);//copy constr

    CPPUNIT_ASSERT(filename_0.get_directory()==dir &&
                   filename_0.get_core_name()==fil &&
                   filename_0.get_extension()==ext);


    sys::filename filename_1 ;
    filename_1 = filename_0 ;//operator =

    CPPUNIT_ASSERT(filename_1.get_directory()==dir &&
                   filename_1.get_core_name()==fil &&
                   filename_1.get_extension()==ext);


    CPPUNIT_ASSERT(filename_0 == filename_1);//operator ==
    CPPUNIT_ASSERT( !(filename_0 != filename_1) );//operator !=





    //2nd PART ALTERING THE PATH
    CPPUNIT_ASSERT(filename.get_path()==filepath);
    filename.set_directory(dir);
    filename.set_core_name(fil);
    filename.set_extension(ext);
    CPPUNIT_ASSERT(filename.get_path()==filepath);
    filename.set_path(filepath);
    CPPUNIT_ASSERT(filename.get_path()==filepath);

    // PREFIX /predir . 1/predir ..2/  -> /predir . 1/predir ..2/
    stl::string pre_dir1(
        sys::filename::SSEP+
        U("predir . 1")+
        sys::filename::SSEP+
        U("predir ..2")+
        sys::filename::SSEP);

    filename.add_prefix_directory(pre_dir1);
    stl::string filepath_1=
        dir.empty()==true?pre_dir1:pre_dir1.substr(0, pre_dir1.size()-1);
    filepath_1+=dir;
    filepath_1+=fil;
    if( !ext.empty() )
    {
        filepath_1+=U(".");
        filepath_1+=ext;
    }//if


    //-> /predir . 1/predir ..2/
    stl::string dump_file1=filename.get_path();
    stl::string dump_file1a=filepath_1;

    CPPUNIT_ASSERT(filename.get_path()==filepath_1);

    // POSTFIX  /post .fake.ext/ -> /predir . 1/predir ..2/  + dir +   /post .fake.ext/
    // -> /predir . 1/predir ..2/post .fake.ext/
    stl::string post_dir2(sys::filename::SSEP+
                           U("post .fake.ext")+
                           sys::filename::SSEP);

    filename.add_postfix_directory(post_dir2);
    stl::string filepath_2;
    if(dir.empty())
    {
        filepath_2 =
            pre_dir1.substr(0, pre_dir1.size()-1)+
            post_dir2+
            fil+
            (ext.empty()==true?U(""):U("."))+
            ext;
    }//if
    else
    {
        filepath_2 =
            pre_dir1.substr(0, pre_dir1.size()-1)+
            dir+
            post_dir2.substr(1, post_dir2.size()-1)+
            fil+(ext.empty() == true ? U(""):U("."))+
            ext;
    }//else
    CPPUNIT_ASSERT(filename.get_path()==filepath_2);

    //substract /predir ..2/ + dir + /post .fake.ext/
    sys::filename filename_3 = filename.substract_prefix_directory();

    stl::string filepath_3 = sys::filename::SSEP+ U("predir ..2")+ sys::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        post_dir2.substr(1, post_dir2.size()-1)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_3.get_path()==filepath_3);

    //substract POSTFIX -> /predir ..2/ + dir
    sys::filename filename_4 = filename_3.substract_postfix_directory();

    stl::string filepath_4 =  sys::filename::SSEP+U("predir ..2")+sys::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;

    stl::string dump_file4=filename_4.get_path();
    stl::string dump_file4a=filepath_4;
    CPPUNIT_ASSERT(filename_4.get_path()==filepath_4);



    //substract prefix dir -> dir
    sys::filename filename_5 = filename_4.substract_prefix_directory();
    stl::string filepath_5 =
        (dir.empty()==true?sys::filename::SSEP:dir)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_5.get_path()==filepath_5);

}



void test_filename::test6()
{

    // /home/mihk/ 0 cpp -> /home/mihk/.cpp
    stl::string dir(sys::filename::SSEP); dir+=U("home"); dir+=sys::filename::SSEP; dir+=U("mihk"); dir+=sys::filename::SSEP;
    stl::string fil(U(""));
    stl::string ext(U("cpp"));

    stl::string filepath(dir); filepath+=fil; filepath+=U("."); filepath+=ext;

    sys::filename filename(filepath);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);


    filename=sys::filename(dir, fil, ext);//constr(x,y,z);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);


    sys::filename filename_0(filename);//copy constr

    CPPUNIT_ASSERT(filename_0.get_directory()==dir &&
                   filename_0.get_core_name()==fil &&
                   filename_0.get_extension()==ext);


    sys::filename filename_1 ;
    filename_1 = filename_0 ;//operator =

    CPPUNIT_ASSERT(filename_1.get_directory()==dir &&
                   filename_1.get_core_name()==fil &&
                   filename_1.get_extension()==ext);


    CPPUNIT_ASSERT(filename_0 == filename_1);//operator ==
    CPPUNIT_ASSERT( !(filename_0 != filename_1) );//operator !=






    //2nd PART ALTERING THE PATH
    CPPUNIT_ASSERT(filename.get_path()==filepath);
    filename.set_directory(dir);
    filename.set_core_name(fil);
    filename.set_extension(ext);
    CPPUNIT_ASSERT(filename.get_path()==filepath);
    filename.set_path(filepath);
    CPPUNIT_ASSERT(filename.get_path()==filepath);

    // PREFIX /predir . 1/predir ..2/  -> /predir . 1/predir ..2/
    stl::string pre_dir1(
        sys::filename::SSEP+
        U("predir . 1")+
        sys::filename::SSEP+
        U("predir ..2")+
        sys::filename::SSEP);

    filename.add_prefix_directory(pre_dir1);
    stl::string filepath_1=
        dir.empty()==true?pre_dir1:pre_dir1.substr(0, pre_dir1.size()-1)+
        dir+
        fil+
        (ext.empty()==true?U(""):(U(".")+ext));

    //-> /predir . 1/predir ..2/
    stl::string dump_file1=filename.get_path();
    stl::string dump_file1a=filepath_1;

    CPPUNIT_ASSERT(filename.get_path()==filepath_1);

    // POSTFIX  /post .fake.ext/ -> /predir . 1/predir ..2/  + dir +   /post .fake.ext/
    // -> /predir . 1/predir ..2/post .fake.ext/
    stl::string post_dir2(sys::filename::SSEP+
                           U("post .fake.ext")+
                           sys::filename::SSEP);

    filename.add_postfix_directory(post_dir2);
    stl::string filepath_2;
    if(dir.empty())
    {
        filepath_2 =
            pre_dir1.substr(0, pre_dir1.size()-1)+
            post_dir2+
            fil+
            (ext.empty()==true?U(""):U("."))+
            ext;
    }//if
    else
    {
        filepath_2 =
            pre_dir1.substr(0, pre_dir1.size()-1)+
            dir+
            post_dir2.substr(1, post_dir2.size()-1)+
            fil+(ext.empty() == true ? U(""):U("."))+
            ext;
    }//else
    CPPUNIT_ASSERT(filename.get_path()==filepath_2);

    //substract /predir ..2/ + dir + /post .fake.ext/
    sys::filename filename_3 = filename.substract_prefix_directory();

    stl::string filepath_3 = sys::filename::SSEP+ U("predir ..2")+ sys::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        post_dir2.substr(1, post_dir2.size()-1)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_3.get_path()==filepath_3);

    //substract POSTFIX -> /predir ..2/ + dir
    sys::filename filename_4 = filename_3.substract_postfix_directory();

    stl::string filepath_4 =  sys::filename::SSEP+U("predir ..2")+sys::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;

    stl::string dump_file4=filename_4.get_path();
    stl::string dump_file4a=filepath_4;
    CPPUNIT_ASSERT(filename_4.get_path()==filepath_4);



    //substract prefix dir -> dir
    sys::filename filename_5 = filename_4.substract_prefix_directory();
    stl::string filepath_5 =
        (dir.empty()==true?sys::filename::SSEP:dir)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_5.get_path()==filepath_5);

}


void test_filename::test7()
{



    // /home/mihk/ .file 0 -> /home/.file
    stl::string dir(sys::filename::SSEP); dir+=U("home"); dir+=sys::filename::SSEP; dir+=U("mihk"); dir+=sys::filename::SSEP;
    stl::string fil(U(".file"));
    stl::string ext(U(""));


    stl::string filepath(dir); filepath+=fil; if(!ext.empty()) filepath+=U("."); filepath+=ext;

    sys::filename filename(filepath);

    //a workaround file core name that is identified as extension /home/.file -> /home/ 0 .file as extension.
    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==U("") &&
                   filename.get_extension()==fil.substr(1, fil.size()-1));


    filename=sys::filename(dir, fil, ext);//constr(x,y,z);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);

    sys::filename filename_0(filename);//copy constr

    CPPUNIT_ASSERT(filename_0.get_directory()==dir &&
                   filename_0.get_core_name()==fil &&
                   filename_0.get_extension()==ext);


    sys::filename filename_1 ;
    filename_1 = filename_0 ;//operator =

    CPPUNIT_ASSERT(filename_1.get_directory()==dir &&
                   filename_1.get_core_name()==fil &&
                   filename_1.get_extension()==ext);

    CPPUNIT_ASSERT(filename_0 == filename_1);//operator ==
    CPPUNIT_ASSERT( !(filename_0 != filename_1) );//operator !=






    //2nd PART ALTERING THE PATH
    CPPUNIT_ASSERT(filename.get_path()==filepath);
    filename.set_directory(dir);
    filename.set_core_name(fil);
    filename.set_extension(ext);
    CPPUNIT_ASSERT(filename.get_path()==filepath);
    filename.set_path(filepath);
    CPPUNIT_ASSERT(filename.get_path()==filepath);

    // PREFIX /predir . 1/predir ..2/  -> /predir . 1/predir ..2/
    stl::string pre_dir1(
        sys::filename::SSEP+
        U("predir . 1")+
        sys::filename::SSEP+
        U("predir ..2")+
        sys::filename::SSEP);

    filename.add_prefix_directory(pre_dir1);
    stl::string filepath_1=
        dir.empty()==true?pre_dir1:pre_dir1.substr(0, pre_dir1.size()-1)+
        dir+
        fil+
        (ext.empty()==true?U(""):(U(".")+ext));

    //-> /predir . 1/predir ..2/
    stl::string dump_file1=filename.get_path();
    stl::string dump_file1a=filepath_1;

    CPPUNIT_ASSERT(filename.get_path()==filepath_1);

    // POSTFIX  /post .fake.ext/ -> /predir . 1/predir ..2/  + dir +   /post .fake.ext/
    // -> /predir . 1/predir ..2/post .fake.ext/
    stl::string post_dir2(sys::filename::SSEP+
                           U("post .fake.ext")+
                           sys::filename::SSEP);

    filename.add_postfix_directory(post_dir2);
    stl::string filepath_2;
    if(dir.empty())
    {
        filepath_2 =
            pre_dir1.substr(0, pre_dir1.size()-1)+
            post_dir2+
            fil+
            (ext.empty()==true?U(""):U("."))+
            ext;
    }//if
    else
    {
        filepath_2 =
            pre_dir1.substr(0, pre_dir1.size()-1)+
            dir+
            post_dir2.substr(1, post_dir2.size()-1)+
            fil+(ext.empty() == true ? U(""):U("."))+
            ext;
    }//else
    CPPUNIT_ASSERT(filename.get_path()==filepath_2);

    //substract /predir ..2/ + dir + /post .fake.ext/
    sys::filename filename_3 = filename.substract_prefix_directory();

    stl::string filepath_3 = sys::filename::SSEP+ U("predir ..2")+ sys::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        post_dir2.substr(1, post_dir2.size()-1)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_3.get_path()==filepath_3);

    //substract POSTFIX -> /predir ..2/ + dir
    sys::filename filename_4 = filename_3.substract_postfix_directory();

    stl::string filepath_4 =  sys::filename::SSEP+U("predir ..2")+sys::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;

    stl::string dump_file4=filename_4.get_path();
    stl::string dump_file4a=filepath_4;
    CPPUNIT_ASSERT(filename_4.get_path()==filepath_4);



    //substract prefix dir -> dir
    sys::filename filename_5 = filename_4.substract_prefix_directory();
    stl::string filepath_5 =
        (dir.empty()==true?sys::filename::SSEP:dir)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_5.get_path()==filepath_5);

}


void test_filename::test8()
{


    // /home/mihk/ .parser .cpp
    stl::string dir(sys::filename::SSEP); dir+=U("home"); dir+=sys::filename::SSEP; dir+=U("mihk"); dir+=sys::filename::SSEP;
    stl::string fil(U(".parser"));
    stl::string ext(U("cpp"));


    stl::string filepath(dir); filepath+=fil; filepath+=U("."); filepath+=ext;

    sys::filename filename(filepath);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);

    filename=sys::filename(dir, fil, ext);//constr(x,y,z);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);

    sys::filename filename_0(filename);//copy constr

    CPPUNIT_ASSERT(filename_0.get_directory()==dir &&
                   filename_0.get_core_name()==fil &&
                   filename_0.get_extension()==ext);

    sys::filename filename_1 ;
    filename_1 = filename_0 ;//operator =

    CPPUNIT_ASSERT(filename_1.get_directory()==dir &&
                   filename_1.get_core_name()==fil &&
                   filename_1.get_extension()==ext);

    CPPUNIT_ASSERT(filename_0 == filename_1);//operator ==
    CPPUNIT_ASSERT( !(filename_0 != filename_1) );//operator !=






    //2nd PART ALTERING THE PATH
    CPPUNIT_ASSERT(filename.get_path()==filepath);
    filename.set_directory(dir);
    filename.set_core_name(fil);
    filename.set_extension(ext);
    CPPUNIT_ASSERT(filename.get_path()==filepath);
    filename.set_path(filepath);
    CPPUNIT_ASSERT(filename.get_path()==filepath);

    // PREFIX /predir . 1/predir ..2/  -> /predir . 1/predir ..2/
    stl::string pre_dir1(
        sys::filename::SSEP+
        U("predir . 1")+
        sys::filename::SSEP+
        U("predir ..2")+
        sys::filename::SSEP);

    filename.add_prefix_directory(pre_dir1);
    stl::string filepath_1=
        dir.empty()==true?pre_dir1:pre_dir1.substr(0, pre_dir1.size()-1)+
        dir+
        fil+
        (ext.empty()==true?U(""):(U(".")+ext));

    //-> /predir . 1/predir ..2/
    stl::string dump_file1=filename.get_path();
    stl::string dump_file1a=filepath_1;

    CPPUNIT_ASSERT(filename.get_path()==filepath_1);

    // POSTFIX  /post .fake.ext/ -> /predir . 1/predir ..2/  + dir +   /post .fake.ext/
    // -> /predir . 1/predir ..2/post .fake.ext/
    stl::string post_dir2(sys::filename::SSEP+
                           U("post .fake.ext")+
                           sys::filename::SSEP);

    filename.add_postfix_directory(post_dir2);
    stl::string filepath_2;
    if(dir.empty())
    {
        filepath_2 =
            pre_dir1.substr(0, pre_dir1.size()-1)+
            post_dir2+
            fil+
            (ext.empty()==true?U(""):U("."))+
            ext;
    }//if
    else
    {
        filepath_2 =
            pre_dir1.substr(0, pre_dir1.size()-1)+
            dir+
            post_dir2.substr(1, post_dir2.size()-1)+
            fil+(ext.empty() == true ? U(""):U("."))+
            ext;
    }//else
    CPPUNIT_ASSERT(filename.get_path()==filepath_2);

    //substract /predir ..2/ + dir + /post .fake.ext/
    sys::filename filename_3 = filename.substract_prefix_directory();

    stl::string filepath_3 = sys::filename::SSEP+ U("predir ..2")+ sys::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        post_dir2.substr(1, post_dir2.size()-1)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_3.get_path()==filepath_3);

    //substract POSTFIX -> /predir ..2/ + dir
    sys::filename filename_4 = filename_3.substract_postfix_directory();

    stl::string filepath_4 =  sys::filename::SSEP+U("predir ..2")+sys::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;

    stl::string dump_file4=filename_4.get_path();
    stl::string dump_file4a=filepath_4;
    CPPUNIT_ASSERT(filename_4.get_path()==filepath_4);



    //substract prefix dir -> dir
    sys::filename filename_5 = filename_4.substract_prefix_directory();
    stl::string filepath_5 =
        (dir.empty()==true?sys::filename::SSEP:dir)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_5.get_path()==filepath_5);

}

