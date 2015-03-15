/*
	Copyright (C) 2011 Mihai Vasilian

	This program is free software; you can redistribute it and/or modify it under the terms of the GNU General
	Public License as published by the Free Software Foundation; either version 2 of the License, or (at your
	option) any later version.

	This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the 
	implied warranty of	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License along with this program. 
	If not, see http://www.gnu.org/licenses/.

	contact: grayasm@gmail.com
*/


//test
#include "test_999.hpp"
//
#include "test_001.hpp"
#include "test_002.hpp"
#include "test_003.hpp"
#include "test_004.hpp"
#include "test_005.hpp"
#include "test_006.hpp"
#include "test_007.hpp"
#include "test_008.hpp"
#include "test_009.hpp"
#include "test_010.hpp"
#include "test_011.hpp"
#include "test_012.hpp"
#include "test_013.hpp"
#include "test_014.hpp"
#include "test_015.hpp"
#include "test_016.hpp"
#include "test_017.hpp"
#include "test_018.hpp"
#include "test_019.hpp"
#include "test_020.hpp"
#include "test_021.hpp"
#include "test_022.hpp"
#include "test_023.hpp"
//#include "test_024.hpp"




//cpp 14882/2003
#include "test_14882_2003_2.13.1.hpp"
#include "test_14882_2003_2.13.2.hpp"
#include "test_14882_2003_2.13.3.hpp"
#include "test_14882_2003_2.13.4.hpp"
#include "test_14882_2003_2.13.5.hpp"
#include "test_14882_2003_annex_e.hpp"




int main(int /*argc*/, char** /*argv*/)
{
	//test999::run("test999");
	test1::run("test1");
	test2::run("test2");
	test3::run("test3");
	test4::run("test4");
	test5::run("test5");
	test6::run("test6");
	test7::run("test7");
	test8::run("test8");
	test9::run("test9");
	test10::run("test10");
	test11::run("test11");
	test12::run("test12");
	test13::run("test13");
	test14::run("test14");
	test15::run("test15");
	test16::run("test16");
	test17::run("test17");
	test18::run("test18");
	test19::run("test19");
	test20::run("test20");
	test21::run("test21");
	test22::run("test22");
	test23::run("test23");
	//test24::run("test24");




	//cpp 14883/2003
	test_14882_2003_2_13_1::run("test_14882_2003_2_13_1");
	test_14882_2003_2_13_2::run("test_14882_2003_2_13_2");
	test_14882_2003_2_13_3::run("test_14882_2003_2_13_3");
	test_14882_2003_2_13_4::run("test_14882_2003_2_13_4");
	test_14882_2003_2_13_5::run("test_14882_2003_2_13_5");
	test_14882_2003_annex_e::run("test_14882_2003_annex_e");


	return 0;
};
