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
    misc::cout << "\n\n\t*******************************************************";
    misc::cout <<   "\n\t* TESTING HEADER: filename.hpp                        *";
    misc::cout <<   "\n\t*******************************************************";


    // 0 0 0 -> 0 0 0
    misc::string dir(U(""));
    misc::string fil(U(""));
    misc::string ext(U(""));

    misc::string filepath(dir); 
    filepath += fil; /*filepath+=U(".");*/ 
    filepath += ext;

    misc::filename filename(filepath);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);

    filename=misc::filename(dir, fil, ext);//constr(x,y,z);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);

    misc::filename filename_0(filename);//copy constr

    CPPUNIT_ASSERT(filename_0.get_directory()==dir &&
                   filename_0.get_core_name()==fil &&
                   filename_0.get_extension()==ext);

    misc::filename filename_1 ;
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
    misc::string pre_dir1(
        misc::filename::SSEP+
        U("predir . 1")+
        misc::filename::SSEP+
        U("predir ..2")+
        misc::filename::SSEP);

    filename.add_prefix_directory(pre_dir1);
    misc::string filepath_1=
        dir.empty()==true?pre_dir1:pre_dir1.substr(0, pre_dir1.size()-1)+
        dir+
        fil+
        (ext.empty()==true?U(""):(U(".")+ext));

    //-> /predir . 1/predir ..2/
    misc::string dump_file1 = filename.get_path();
    misc::string dump_file1a = filepath_1;
    misc::string filename_path = filename.get_path();

    CPPUNIT_ASSERT(filename_path == filepath_1);

    // POSTFIX  /post .fake.ext/ -> /predir . 1/predir ..2/  + dir +   /post .fake.ext/
    // -> /predir . 1/predir ..2/post .fake.ext/
    misc::string post_dir2(misc::filename::SSEP+
                           U("post .fake.ext")+
                           misc::filename::SSEP);

    filename.add_postfix_directory(post_dir2);
    misc::string filepath_2;
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
    misc::filename filename_3 = filename.substract_prefix_directory();

    misc::string filepath_3 = misc::filename::SSEP+ U("predir ..2")+ misc::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        post_dir2.substr(1, post_dir2.size()-1)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_3.get_path()==filepath_3);

    //substract POSTFIX -> /predir ..2/ + dir
    misc::filename filename_4 = filename_3.substract_postfix_directory();

    misc::string filepath_4 =  misc::filename::SSEP+U("predir ..2")+misc::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;

    misc::string dump_file4=filename_4.get_path();
    misc::string dump_file4a=filepath_4;
    CPPUNIT_ASSERT(filename_4.get_path()==filepath_4);



    //substract prefix dir -> dir
    misc::filename filename_5 = filename_4.substract_prefix_directory();
    misc::string filepath_5 =
        (dir.empty()==true?misc::filename::SSEP:dir)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_5.get_path()==filepath_5);

}


void test_filename::test1()
{
    // / 0 0 -> /
    misc::string dir(misc::filename::SSEP);
    misc::string fil(U(""));
    misc::string ext(U(""));

    misc::string filepath(dir); filepath+=fil; /*filepath+=U(".");*/ filepath+=ext;

    misc::filename filename(filepath);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);

    filename=misc::filename(dir, fil, ext);//constr(x,y,z);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);

    misc::filename filename_0(filename);//copy constr

    CPPUNIT_ASSERT(filename_0.get_directory()==dir &&
                   filename_0.get_core_name()==fil &&
                   filename_0.get_extension()==ext);

    misc::filename filename_1 ;
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
    misc::string pre_dir1(
        misc::filename::SSEP+
        U("predir . 1")+
        misc::filename::SSEP+
        U("predir ..2")+
        misc::filename::SSEP);

    filename.add_prefix_directory(pre_dir1);
    misc::string filepath_1=
        dir.empty()==true?pre_dir1:pre_dir1.substr(0, pre_dir1.size()-1)+
        dir+
        fil+
        (ext.empty()==true?U(""):(U(".")+ext));

    //-> /predir . 1/predir ..2/
    misc::string dump_file1=filename.get_path();
    misc::string dump_file1a=filepath_1;

    CPPUNIT_ASSERT(filename.get_path()==filepath_1);

    // POSTFIX  /post .fake.ext/ -> /predir . 1/predir ..2/  + dir +   /post .fake.ext/
    // -> /predir . 1/predir ..2/post .fake.ext/
    misc::string post_dir2(misc::filename::SSEP+
                           U("post .fake.ext")+
                           misc::filename::SSEP);

    filename.add_postfix_directory(post_dir2);
    misc::string filepath_2;
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
    misc::filename filename_3 = filename.substract_prefix_directory();

    misc::string filepath_3 = misc::filename::SSEP+ U("predir ..2")+ misc::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        post_dir2.substr(1, post_dir2.size()-1)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_3.get_path()==filepath_3);

    //substract POSTFIX -> /predir ..2/ + dir
    misc::filename filename_4 = filename_3.substract_postfix_directory();

    misc::string filepath_4 =  misc::filename::SSEP+U("predir ..2")+misc::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;

    misc::string dump_file4=filename_4.get_path();
    misc::string dump_file4a=filepath_4;
    CPPUNIT_ASSERT(filename_4.get_path()==filepath_4);



    //substract prefix dir -> dir
    misc::filename filename_5 = filename_4.substract_prefix_directory();
    misc::string filepath_5 =
        (dir.empty()==true?misc::filename::SSEP:dir)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_5.get_path()==filepath_5);



}


void test_filename::test2()
{
    // /home/ -> /home/ 0 0
    misc::string dir(misc::filename::SSEP); dir+=U("home"); dir+=misc::filename::SSEP;
    misc::string fil(U(""));
    misc::string ext(U(""));

    misc::string filepath(dir); filepath+=fil; filepath+=ext;

    misc::filename filename(filepath);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);

    filename=misc::filename(dir, fil, ext);//constr(x,y,z);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);

    misc::filename filename_0(filename);//copy constr

    CPPUNIT_ASSERT(filename_0.get_directory()==dir &&
                   filename_0.get_core_name()==fil &&
                   filename_0.get_extension()==ext);

    misc::filename filename_1 ;
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
    misc::string pre_dir1(
        misc::filename::SSEP+
        U("predir . 1")+
        misc::filename::SSEP+
        U("predir ..2")+
        misc::filename::SSEP);

    filename.add_prefix_directory(pre_dir1);
    misc::string filepath_1=
        dir.empty()==true?pre_dir1:pre_dir1.substr(0, pre_dir1.size()-1)+
        dir+
        fil+
        (ext.empty()==true?U(""):(U(".")+ext));

    //-> /predir . 1/predir ..2/
    misc::string dump_file1=filename.get_path();
    misc::string dump_file1a=filepath_1;

    CPPUNIT_ASSERT(filename.get_path()==filepath_1);

    // POSTFIX  /post .fake.ext/ -> /predir . 1/predir ..2/  + dir +   /post .fake.ext/
    // -> /predir . 1/predir ..2/post .fake.ext/
    misc::string post_dir2(misc::filename::SSEP+
                           U("post .fake.ext")+
                           misc::filename::SSEP);

    filename.add_postfix_directory(post_dir2);
    misc::string filepath_2;
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
    misc::filename filename_3 = filename.substract_prefix_directory();

    misc::string filepath_3 = misc::filename::SSEP+ U("predir ..2")+ misc::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        post_dir2.substr(1, post_dir2.size()-1)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_3.get_path()==filepath_3);

    //substract POSTFIX -> /predir ..2/ + dir
    misc::filename filename_4 = filename_3.substract_postfix_directory();

    misc::string filepath_4 =  misc::filename::SSEP+U("predir ..2")+misc::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;

    misc::string dump_file4=filename_4.get_path();
    misc::string dump_file4a=filepath_4;
    CPPUNIT_ASSERT(filename_4.get_path()==filepath_4);



    //substract prefix dir -> dir
    misc::filename filename_5 = filename_4.substract_prefix_directory();
    misc::string filepath_5 =
        (dir.empty()==true?misc::filename::SSEP:dir)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_5.get_path()==filepath_5);


}


void test_filename::test3()
{

    // /home/mihk/file -> /home/mihk/ file 0
    misc::string dir(misc::filename::SSEP); dir+=U("home"); dir+=misc::filename::SSEP; dir+=U("mihk"); dir+=misc::filename::SSEP;
    misc::string fil(U("file"));
    misc::string ext(U(""));

    misc::string filepath(dir); filepath+=fil; filepath+=ext;

    misc::filename filename(filepath);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);


    filename=misc::filename(dir, fil, ext);//constr(x,y,z);

    misc::filename filename_0(filename);//copy constr

    CPPUNIT_ASSERT(filename_0.get_directory()==dir &&
                   filename_0.get_core_name()==fil &&
                   filename_0.get_extension()==ext);

    misc::filename filename_1 ;
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
    misc::string pre_dir1(
        misc::filename::SSEP+
        U("predir . 1")+
        misc::filename::SSEP+
        U("predir ..2")+
        misc::filename::SSEP);

    filename.add_prefix_directory(pre_dir1);
    misc::string filepath_1=
        dir.empty()==true?pre_dir1:pre_dir1.substr(0, pre_dir1.size()-1)+
        dir+
        fil+
        (ext.empty()==true?U(""):(U(".")+ext));

    //-> /predir . 1/predir ..2/
    misc::string dump_file1=filename.get_path();
    misc::string dump_file1a=filepath_1;

    CPPUNIT_ASSERT(filename.get_path()==filepath_1);

    // POSTFIX  /post .fake.ext/ -> /predir . 1/predir ..2/  + dir +   /post .fake.ext/
    // -> /predir . 1/predir ..2/post .fake.ext/
    misc::string post_dir2(misc::filename::SSEP+
                           U("post .fake.ext")+
                           misc::filename::SSEP);

    filename.add_postfix_directory(post_dir2);
    misc::string filepath_2;
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
    misc::filename filename_3 = filename.substract_prefix_directory();

    misc::string filepath_3 = misc::filename::SSEP+ U("predir ..2")+ misc::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        post_dir2.substr(1, post_dir2.size()-1)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_3.get_path()==filepath_3);

    //substract POSTFIX -> /predir ..2/ + dir
    misc::filename filename_4 = filename_3.substract_postfix_directory();

    misc::string filepath_4 =  misc::filename::SSEP+U("predir ..2")+misc::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;

    misc::string dump_file4=filename_4.get_path();
    misc::string dump_file4a=filepath_4;
    CPPUNIT_ASSERT(filename_4.get_path()==filepath_4);



    //substract prefix dir -> dir
    misc::filename filename_5 = filename_4.substract_prefix_directory();
    misc::string filepath_5 =
        (dir.empty()==true?misc::filename::SSEP:dir)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_5.get_path()==filepath_5);


}


void test_filename::test4()
{

    // /home/mihk/parser.cpp -> /home/mihk/ parser cpp
    misc::string dir(misc::filename::SSEP); dir+=U("home"); dir+=misc::filename::SSEP; dir+=U("mihk"); dir+=misc::filename::SSEP;
    misc::string fil(U("parser"));
    misc::string ext(U("cpp"));

    misc::string filepath(dir); filepath+=fil; filepath+=U("."); filepath+=ext;

    misc::filename filename(filepath);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);


    filename=misc::filename(dir, fil, ext);//constr(x,y,z);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);


    misc::filename filename_0(filename);//copy constr

    CPPUNIT_ASSERT(filename_0.get_directory()==dir &&
                   filename_0.get_core_name()==fil &&
                   filename_0.get_extension()==ext);


    misc::filename filename_1 ;
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
    misc::string pre_dir1(
        misc::filename::SSEP+
        U("predir . 1")+
        misc::filename::SSEP+
        U("predir ..2")+
        misc::filename::SSEP);

    filename.add_prefix_directory(pre_dir1);
    misc::string filepath_1=
        dir.empty()==true?pre_dir1:pre_dir1.substr(0, pre_dir1.size()-1)+
        dir+
        fil+
        (ext.empty()==true?U(""):(U(".")+ext));

    //-> /predir . 1/predir ..2/
    misc::string dump_file1=filename.get_path();
    misc::string dump_file1a=filepath_1;

    CPPUNIT_ASSERT(filename.get_path()==filepath_1);

    // POSTFIX  /post .fake.ext/ -> /predir . 1/predir ..2/  + dir +   /post .fake.ext/
    // -> /predir . 1/predir ..2/post .fake.ext/
    misc::string post_dir2(misc::filename::SSEP+
                           U("post .fake.ext")+
                           misc::filename::SSEP);

    filename.add_postfix_directory(post_dir2);
    misc::string filepath_2;
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
    misc::filename filename_3 = filename.substract_prefix_directory();

    misc::string filepath_3 = misc::filename::SSEP+ U("predir ..2")+ misc::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        post_dir2.substr(1, post_dir2.size()-1)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_3.get_path()==filepath_3);

    //substract POSTFIX -> /predir ..2/ + dir
    misc::filename filename_4 = filename_3.substract_postfix_directory();

    misc::string filepath_4 =  misc::filename::SSEP+U("predir ..2")+misc::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;

    misc::string dump_file4=filename_4.get_path();
    misc::string dump_file4a=filepath_4;
    CPPUNIT_ASSERT(filename_4.get_path()==filepath_4);



    //substract prefix dir -> dir
    misc::filename filename_5 = filename_4.substract_prefix_directory();
    misc::string filepath_5 =
        (dir.empty()==true?misc::filename::SSEP:dir)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_5.get_path()==filepath_5);

}



void test_filename::test5()
{



    // 0 0 cpp -> .cpp
    misc::string dir(U(""));
    misc::string fil(U(""));
    misc::string ext(U("cpp"));

    misc::string filepath(dir); filepath+=fil; filepath+=U("."); filepath+=ext;

    misc::filename filename(filepath);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);


    filename=misc::filename(dir, fil, ext);//constr(x,y,z);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);


    misc::filename filename_0(filename);//copy constr

    CPPUNIT_ASSERT(filename_0.get_directory()==dir &&
                   filename_0.get_core_name()==fil &&
                   filename_0.get_extension()==ext);


    misc::filename filename_1 ;
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
    misc::string pre_dir1(
        misc::filename::SSEP+
        U("predir . 1")+
        misc::filename::SSEP+
        U("predir ..2")+
        misc::filename::SSEP);

    filename.add_prefix_directory(pre_dir1);
    misc::string filepath_1=
        dir.empty()==true?pre_dir1:pre_dir1.substr(0, pre_dir1.size()-1);
    filepath_1+=dir;
    filepath_1+=fil;
    if( !ext.empty() )
    {
        filepath_1+=U(".");
        filepath_1+=ext;
    }//if


    //-> /predir . 1/predir ..2/
    misc::string dump_file1=filename.get_path();
    misc::string dump_file1a=filepath_1;

    CPPUNIT_ASSERT(filename.get_path()==filepath_1);

    // POSTFIX  /post .fake.ext/ -> /predir . 1/predir ..2/  + dir +   /post .fake.ext/
    // -> /predir . 1/predir ..2/post .fake.ext/
    misc::string post_dir2(misc::filename::SSEP+
                           U("post .fake.ext")+
                           misc::filename::SSEP);

    filename.add_postfix_directory(post_dir2);
    misc::string filepath_2;
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
    misc::filename filename_3 = filename.substract_prefix_directory();

    misc::string filepath_3 = misc::filename::SSEP+ U("predir ..2")+ misc::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        post_dir2.substr(1, post_dir2.size()-1)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_3.get_path()==filepath_3);

    //substract POSTFIX -> /predir ..2/ + dir
    misc::filename filename_4 = filename_3.substract_postfix_directory();

    misc::string filepath_4 =  misc::filename::SSEP+U("predir ..2")+misc::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;

    misc::string dump_file4=filename_4.get_path();
    misc::string dump_file4a=filepath_4;
    CPPUNIT_ASSERT(filename_4.get_path()==filepath_4);



    //substract prefix dir -> dir
    misc::filename filename_5 = filename_4.substract_prefix_directory();
    misc::string filepath_5 =
        (dir.empty()==true?misc::filename::SSEP:dir)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_5.get_path()==filepath_5);

}



void test_filename::test6()
{

    // /home/mihk/ 0 cpp -> /home/mihk/.cpp
    misc::string dir(misc::filename::SSEP); dir+=U("home"); dir+=misc::filename::SSEP; dir+=U("mihk"); dir+=misc::filename::SSEP;
    misc::string fil(U(""));
    misc::string ext(U("cpp"));

    misc::string filepath(dir); filepath+=fil; filepath+=U("."); filepath+=ext;

    misc::filename filename(filepath);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);


    filename=misc::filename(dir, fil, ext);//constr(x,y,z);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);


    misc::filename filename_0(filename);//copy constr

    CPPUNIT_ASSERT(filename_0.get_directory()==dir &&
                   filename_0.get_core_name()==fil &&
                   filename_0.get_extension()==ext);


    misc::filename filename_1 ;
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
    misc::string pre_dir1(
        misc::filename::SSEP+
        U("predir . 1")+
        misc::filename::SSEP+
        U("predir ..2")+
        misc::filename::SSEP);

    filename.add_prefix_directory(pre_dir1);
    misc::string filepath_1=
        dir.empty()==true?pre_dir1:pre_dir1.substr(0, pre_dir1.size()-1)+
        dir+
        fil+
        (ext.empty()==true?U(""):(U(".")+ext));

    //-> /predir . 1/predir ..2/
    misc::string dump_file1=filename.get_path();
    misc::string dump_file1a=filepath_1;

    CPPUNIT_ASSERT(filename.get_path()==filepath_1);

    // POSTFIX  /post .fake.ext/ -> /predir . 1/predir ..2/  + dir +   /post .fake.ext/
    // -> /predir . 1/predir ..2/post .fake.ext/
    misc::string post_dir2(misc::filename::SSEP+
                           U("post .fake.ext")+
                           misc::filename::SSEP);

    filename.add_postfix_directory(post_dir2);
    misc::string filepath_2;
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
    misc::filename filename_3 = filename.substract_prefix_directory();

    misc::string filepath_3 = misc::filename::SSEP+ U("predir ..2")+ misc::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        post_dir2.substr(1, post_dir2.size()-1)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_3.get_path()==filepath_3);

    //substract POSTFIX -> /predir ..2/ + dir
    misc::filename filename_4 = filename_3.substract_postfix_directory();

    misc::string filepath_4 =  misc::filename::SSEP+U("predir ..2")+misc::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;

    misc::string dump_file4=filename_4.get_path();
    misc::string dump_file4a=filepath_4;
    CPPUNIT_ASSERT(filename_4.get_path()==filepath_4);



    //substract prefix dir -> dir
    misc::filename filename_5 = filename_4.substract_prefix_directory();
    misc::string filepath_5 =
        (dir.empty()==true?misc::filename::SSEP:dir)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_5.get_path()==filepath_5);

}


void test_filename::test7()
{



    // /home/mihk/ .file 0 -> /home/.file
    misc::string dir(misc::filename::SSEP); dir+=U("home"); dir+=misc::filename::SSEP; dir+=U("mihk"); dir+=misc::filename::SSEP;
    misc::string fil(U(".file"));
    misc::string ext(U(""));


    misc::string filepath(dir); filepath+=fil; if(!ext.empty()) filepath+=U("."); filepath+=ext;

    misc::filename filename(filepath);

    //a workaround file core name that is identified as extension /home/.file -> /home/ 0 .file as extension.
    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==U("") &&
                   filename.get_extension()==fil.substr(1, fil.size()-1));


    filename=misc::filename(dir, fil, ext);//constr(x,y,z);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);

    misc::filename filename_0(filename);//copy constr

    CPPUNIT_ASSERT(filename_0.get_directory()==dir &&
                   filename_0.get_core_name()==fil &&
                   filename_0.get_extension()==ext);


    misc::filename filename_1 ;
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
    misc::string pre_dir1(
        misc::filename::SSEP+
        U("predir . 1")+
        misc::filename::SSEP+
        U("predir ..2")+
        misc::filename::SSEP);

    filename.add_prefix_directory(pre_dir1);
    misc::string filepath_1=
        dir.empty()==true?pre_dir1:pre_dir1.substr(0, pre_dir1.size()-1)+
        dir+
        fil+
        (ext.empty()==true?U(""):(U(".")+ext));

    //-> /predir . 1/predir ..2/
    misc::string dump_file1=filename.get_path();
    misc::string dump_file1a=filepath_1;

    CPPUNIT_ASSERT(filename.get_path()==filepath_1);

    // POSTFIX  /post .fake.ext/ -> /predir . 1/predir ..2/  + dir +   /post .fake.ext/
    // -> /predir . 1/predir ..2/post .fake.ext/
    misc::string post_dir2(misc::filename::SSEP+
                           U("post .fake.ext")+
                           misc::filename::SSEP);

    filename.add_postfix_directory(post_dir2);
    misc::string filepath_2;
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
    misc::filename filename_3 = filename.substract_prefix_directory();

    misc::string filepath_3 = misc::filename::SSEP+ U("predir ..2")+ misc::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        post_dir2.substr(1, post_dir2.size()-1)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_3.get_path()==filepath_3);

    //substract POSTFIX -> /predir ..2/ + dir
    misc::filename filename_4 = filename_3.substract_postfix_directory();

    misc::string filepath_4 =  misc::filename::SSEP+U("predir ..2")+misc::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;

    misc::string dump_file4=filename_4.get_path();
    misc::string dump_file4a=filepath_4;
    CPPUNIT_ASSERT(filename_4.get_path()==filepath_4);



    //substract prefix dir -> dir
    misc::filename filename_5 = filename_4.substract_prefix_directory();
    misc::string filepath_5 =
        (dir.empty()==true?misc::filename::SSEP:dir)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_5.get_path()==filepath_5);

}


void test_filename::test8()
{


    // /home/mihk/ .parser .cpp
    misc::string dir(misc::filename::SSEP); dir+=U("home"); dir+=misc::filename::SSEP; dir+=U("mihk"); dir+=misc::filename::SSEP;
    misc::string fil(U(".parser"));
    misc::string ext(U("cpp"));


    misc::string filepath(dir); filepath+=fil; filepath+=U("."); filepath+=ext;

    misc::filename filename(filepath);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);

    filename=misc::filename(dir, fil, ext);//constr(x,y,z);

    CPPUNIT_ASSERT(filename.get_directory()==dir &&
                   filename.get_core_name()==fil &&
                   filename.get_extension()==ext);

    misc::filename filename_0(filename);//copy constr

    CPPUNIT_ASSERT(filename_0.get_directory()==dir &&
                   filename_0.get_core_name()==fil &&
                   filename_0.get_extension()==ext);

    misc::filename filename_1 ;
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
    misc::string pre_dir1(
        misc::filename::SSEP+
        U("predir . 1")+
        misc::filename::SSEP+
        U("predir ..2")+
        misc::filename::SSEP);

    filename.add_prefix_directory(pre_dir1);
    misc::string filepath_1=
        dir.empty()==true?pre_dir1:pre_dir1.substr(0, pre_dir1.size()-1)+
        dir+
        fil+
        (ext.empty()==true?U(""):(U(".")+ext));

    //-> /predir . 1/predir ..2/
    misc::string dump_file1=filename.get_path();
    misc::string dump_file1a=filepath_1;

    CPPUNIT_ASSERT(filename.get_path()==filepath_1);

    // POSTFIX  /post .fake.ext/ -> /predir . 1/predir ..2/  + dir +   /post .fake.ext/
    // -> /predir . 1/predir ..2/post .fake.ext/
    misc::string post_dir2(misc::filename::SSEP+
                           U("post .fake.ext")+
                           misc::filename::SSEP);

    filename.add_postfix_directory(post_dir2);
    misc::string filepath_2;
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
    misc::filename filename_3 = filename.substract_prefix_directory();

    misc::string filepath_3 = misc::filename::SSEP+ U("predir ..2")+ misc::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        post_dir2.substr(1, post_dir2.size()-1)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_3.get_path()==filepath_3);

    //substract POSTFIX -> /predir ..2/ + dir
    misc::filename filename_4 = filename_3.substract_postfix_directory();

    misc::string filepath_4 =  misc::filename::SSEP+U("predir ..2")+misc::filename::SSEP+
        (dir.empty()==true ? U(""):dir.substr(1, dir.size()-1))+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;

    misc::string dump_file4=filename_4.get_path();
    misc::string dump_file4a=filepath_4;
    CPPUNIT_ASSERT(filename_4.get_path()==filepath_4);



    //substract prefix dir -> dir
    misc::filename filename_5 = filename_4.substract_prefix_directory();
    misc::string filepath_5 =
        (dir.empty()==true?misc::filename::SSEP:dir)+
        fil+
        (ext.empty()==true ? U(""):U("."))+
        ext;
    CPPUNIT_ASSERT(filename_5.get_path()==filepath_5);

}

