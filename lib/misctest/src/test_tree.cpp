/*
Copyright (C) 2012 Mihai Vasilian
*/



//this
#include "test_tree.hpp"


//c++
#include <iostream>


//acutest
#include "acutest.h"

//libraries
#include "exception.hpp"
#include "string.hpp"
#include "stream.hpp"
#include "misctest_util.hpp"
#include "tree.hpp"




void test_tree::run()
{
	test_90();
	test_00();
	preorder_it();
	preorder_const_it();
	postorder_it();
	postorder_const_it();
	first_branch_it();
	first_branch_const_it();
	child_it();
	child_const_it();

	ctor();
	dtor();
	copy_ctor();
	copy_op();
	get_it();
	push_back_val();
	push_front_val();
	insert_sibling_before_val();
	insert_sibling_after_val();
	push_back_child_val();
	push_front_child_val();
	push_back_tree();
	push_front_tree();
	insert_sibling_before_tree();
	insert_sibling_after_tree();
	push_back_child_tree();
	push_front_child_tree();
	preorder_begin();
	preorder_end();
	preorder_begin_it();
	preorder_end_it();

	postorder_begin();
	postorder_end();
	postorder_begin_it();
	postorder_end_it();

	first_branch_begin();
	first_branch_end();
	first_branch_begin_it();
	first_branch_end_it();

	child_begin();
	child_end();
	child_begin_it();
	child_end_it();

	siblings_begin();
	siblings_end();
	siblings_begin_it();
	siblings_end_it();

	empty();
	size();
	clear();
	erase();	
}

//########################################################################
// test suite
void test_tree::test_90()
{
	typedef misc::tree<int> Tree;
	typedef Tree::iterator It;
	Tree mtree1;
	typedef misc::tree<int>::preorder_iterator preIt;
	typedef misc::tree<int>::preorder_const_iterator preCIt;



	int tree_data[] = { 1, 4, 5, 6, 7 };

	/*
				  root
   			        |
					1
					|
			   4 ------- 7
			   |      
		   5 ----- 6    
			
			

	*/

	It i1 = mtree1.push_back(1);

	It i4 = mtree1.push_back_child(i1, 4);
	It i7 = mtree1.push_back_child(i1, 7);

	It i5 = mtree1.push_back_child(i4, 5);
	It i6 = mtree1.push_back_child(i4, 6);




	size_t i = 0;

	//////////////////////////////////////////////////////////////////////////
	//begin tests

	const Tree ctree1 = mtree1;


	preCIt cbeg = ctree1.preorder_begin();
	preCIt cend = ctree1.preorder_end();

	// const_preorder_iterator& operator++();
	for (i = 0; cbeg != cend && i < 5; ++cbeg, ++i)
	{
		bool res = (*cbeg == tree_data[i]);
		TEST_CHECK(res);
	}//for

}

void test_tree::test_00()
{
	stl::cout << "\n\n\t*******************************************************";
    stl::cout <<   "\n\t* TESTING HEADER: tree.hpp                            *";
    stl::cout <<   "\n\t*******************************************************";

	
	
	typedef misc::tree<stl::string> Tree;
	typedef Tree::iterator It;
	Tree mtree1;
	typedef misc::tree<stl::string>::preorder_iterator preIt;
	typedef misc::tree<stl::string>::preorder_const_iterator preCIt;



	stl::string tree_data[]={
		U("1"),U("4"),U("5"),U("6"),U("7"),U("8"),U("2"),U("9"),
		U("10"),U("11"),U("3"),U("12"),U("13"),U("14")
	};

	/*
                    root
                     |
       1------------ 2 --------------- 3
       |             |                 |
    4 --- 7          9                12
    |     |          |                 |
  5---6   8         10            13 ----- 14
                     |
                    11

	*/

	It i1 = mtree1.push_back(U("1"));
	It i2 = mtree1.push_back(U("2"));
	It i3 = mtree1.push_back(U("3"));

	It i4 = mtree1.push_back_child(i1, U("4"));
	It i7 = mtree1.push_back_child(i1, U("7"));

	It i5 = mtree1.push_back_child(i4, U("5"));
	It i6 = mtree1.push_back_child(i4, U("6"));
	It i8 = mtree1.push_back_child(i7, U("8"));

	It i9 = mtree1.push_back_child(i2, U("9"));
	It i10 = mtree1.push_back_child(i9, U("10"));
	It i11 = mtree1.push_back_child(i10, U("11"));

	It i12 = mtree1.push_back_child(i3, U("12"));
	It i13 = mtree1.push_back_child(i12, U("13"));
	It i14 = mtree1.push_back_child(i12, U("14"));



	size_t i=0;

	//////////////////////////////////////////////////////////////////////////
	//begin tests

	const Tree ctree1 = mtree1;


	preCIt cbeg = ctree1.preorder_begin();
	preCIt cend = ctree1.preorder_end();

	// const_preorder_iterator& operator++();
	for(i=0; cbeg != cend && i < 7; ++cbeg, ++i)
	{
		bool res = (*cbeg == tree_data[i]);
		TEST_CHECK(res);
	}//for

	// const_preorder_iterator operator++(int);
	for(; cbeg != cend; cbeg++, ++i)
	{
		bool res = ((*cbeg) == tree_data[i]);
		TEST_CHECK(res); 
	}//for

	--cbeg;
	preCIt cbeg2 = ctree1.preorder_begin();
	i=13;

	// const_preorder_iterator& operator--();
	for(; cbeg != cbeg2 && i > 7; --cbeg, --i)
	{
		bool res = ((*cbeg) == tree_data[i]);
		TEST_CHECK(res);
	}//for


	//  const_preorder_iterator operator--(int);
	for(; cbeg != cbeg2; cbeg--, --i)
	{
		bool res = (*cbeg == tree_data[i]);
		TEST_CHECK(res);
	}//for

	TEST_CHECK(i == 0 && *cbeg == tree_data[i] && *cbeg == *cbeg2);

	//////////////////////////////////////////////////////////////////////////



	preIt beg = mtree1.preorder_begin();
	preIt end = mtree1.preorder_end();

	
	// preorder_iterator& operator++();
	for(i=0; beg != end && i < 7; ++beg, ++i)
	{
		bool res = ((*beg) == tree_data[i]);
		TEST_CHECK(res);
	}//for

	// preorder_iterator operator++(int);
	for(; beg != end; beg++, ++i)
	{
		bool res = ((*beg) == tree_data[i]);
		TEST_CHECK(res);
	}//for

	--beg;
	preIt beg2 = mtree1.preorder_begin();
	
	i=13;
	//	preorder_iterator& operator--();
	for(; beg != beg2 && i > 7; --beg, --i)
	{
		bool res = ((*beg) == tree_data[i]);
		TEST_CHECK(res);
	}//for


	// preorder_iterator operator--(int);
	for(; beg != beg2; beg--, --i)
	{
		bool res = ((*beg) == tree_data[i]);
		TEST_CHECK(res);
	}//for

	TEST_CHECK(i == 0 && *beg == tree_data[i] && *beg == *beg2);


	/*
	  preorder_iterator tree<T>::preorder_begin(iterator);
	  preorder_iterator tree<T>::preorder_end(iterator);
	*/


	stl::string recursive_data2[]={U("3"), U("12"), U("13"), U("14")};
	beg = mtree1.preorder_begin(i3);
	beg2 = mtree1.preorder_begin(i3);
	end = mtree1.preorder_end(i3);
	i=0;
	for(; beg != end; ++beg, ++i)
	{
		bool res = (*beg == recursive_data2[i]);
		TEST_CHECK(res);
	}//for

	--beg;
	--i;
	for(; beg != beg2; --beg, --i)
	{
		bool res = (*beg == recursive_data2[i]);
		TEST_CHECK(res);
	}//for




	Tree mtree2 = mtree1;
	Tree mtree3 ;
	mtree3 = mtree2 ;

//TODO: "gcc error: no match for ‘operator!=’ (operand types are ‘misc::podstring<char>’ and ‘misc::podstring<char>’ "
#define FIXED_CAN_REMOVE_THIS
#ifdef FIXED_CAN_REMOVE_THIS
	TEST_CHECK(mtree2 == mtree1);
	TEST_CHECK(mtree3 == mtree2);
#endif


	//////////////////////////////////////////////////////////////////////////
	//checking first_branch_iterator
	stl::string first_branch_data[]={U("1"), U("4"), U("5")};
	Tree::first_branch_iterator fbbeg = mtree3.first_branch_begin();
	Tree::first_branch_iterator fbbeg2 = mtree3.first_branch_begin();
	Tree::first_branch_iterator fbend = mtree3.first_branch_end();
	i=0;

	/*
	  first_branch_iterator& first_branch_iterrator::operator++();
	*/
	for(; fbbeg != fbend; ++fbbeg, ++i)
	{
		bool res = (*fbbeg == first_branch_data[i]);
		TEST_CHECK(res);
	}//for

	/*
	  first_branch_iterator& first_branch_iterator::operator--();
	*/
	--fbbeg;
	--i;
	for(; fbbeg != fbbeg2; --fbbeg, --i)
	{
		bool res = (*fbbeg == first_branch_data[i]);
		TEST_CHECK(res);
	}//for


	stl::string first_branch_data2[]={ U("7"), U("8") };
	fbbeg = mtree1.first_branch_begin(i7);
	fbbeg2 = mtree1.first_branch_begin(i7);
	fbend = mtree1.first_branch_end(i7);



	//	first_branch_iterator first_branch_iterator::operator++(int);
	for(i=0; fbbeg != fbend; fbbeg++, i++)
	{
		bool res = (*fbbeg == first_branch_data2[i]);
		TEST_CHECK(res);
	}//for

	fbbeg--;
	i--;

	//	first_branch_iterator first_branch_iterator::operator--(int);
	for(; fbbeg != fbbeg2; fbbeg--, i--)
	{
		bool res = (*fbbeg == first_branch_data2[i]);
		TEST_CHECK(res);
	}//for


	stl::string first_branch_data3[]={ U("2"), U("9"), U("10"), U("11") };
	fbbeg = mtree1.first_branch_begin(i2);
	fbbeg2 = mtree1.first_branch_begin(i2);
	fbend = mtree1.first_branch_end(i2);

	//	first_branch_iterator first_branch_iterator::operator++(int);
	for(i=0; fbbeg != fbend; ++fbbeg, ++i)
	{
		bool res = (*fbbeg == first_branch_data3[i]);
		TEST_CHECK(res);
	}//for

	--fbbeg;
	--i;

	/*
	  first_branch_iterator first_branch_iterator::operator--(int);
	*/
	for(; fbbeg != fbbeg2; --fbbeg, --i)
	{
		TEST_CHECK(*fbbeg == first_branch_data3[i]);
	}//for


	stl::string first_branch_data4[]={U("3"), U("12"), U("13") };
	fbbeg = mtree1.first_branch_begin(i3);
	fbbeg2 = mtree1.first_branch_begin(i3);
	fbend = mtree1.first_branch_end(i3);

	/*
	  first_branch_iterator first_branch_iterator::operator++(int);
	*/
	for(i=0; fbbeg != fbend; fbbeg++, i++)
	{
		TEST_CHECK(*fbbeg == first_branch_data4[i]);
	}//for

	fbbeg--;
	i--;

	/*
	  first_branch_iterator first_branch_iterator::operator--(int);
	*/
	for(; fbbeg != fbbeg2; fbbeg--, i--)
	{
		TEST_CHECK(*fbbeg == first_branch_data4[i]);
	}//for


	stl::string first_branch_data5[]={U("14")};
	fbbeg = mtree1.first_branch_begin(i14);
	fbbeg2 = mtree1.first_branch_begin(i14);
	fbend = mtree1.first_branch_end(i14);

	/*
	  first_branch_iterator first_branch_iterator::operator++(int);
	*/
	for(i=0; fbbeg != fbend; ++fbbeg, ++i)
	{
		TEST_CHECK(*fbbeg == first_branch_data5[i]);
	}//for

	--fbbeg;
	--i;

	/*
	  first_branch_iterator first_branch_iterator::operator--(int);
	*/
	for(; fbbeg != fbbeg2; --fbbeg, --i)
	{
		TEST_CHECK(*fbbeg == first_branch_data5[i]);
	}//for


	stl::string rev_rec_data1[]={U("5"),U("6"),U("4"),U("8"),U("7"),U("1"),U("11"),U("10"),U("9"),U("2"),U("13"),U("14"),U("12"),U("3")};
	Tree::postorder_iterator rribeg = mtree1.postorder_begin();
	Tree::postorder_iterator rriend = mtree1.postorder_end();
	for(i=0; rribeg != rriend; ++rribeg, ++i)
	{
		TEST_CHECK(*rribeg == rev_rec_data1[i]);
	}//for
}


// -- iterators --
void test_tree::preorder_it()
{
	stl::cout << "\n\n\t*******************************************************";
	stl::cout <<   "\n\t* TESTING HEADER: tree.hpp                            *";
	stl::cout <<   "\n\t*******************************************************";
	
	stl::cout << "\n\n\tpreorder_it--------------------------------------------";

	preorder_it<misc::tree<stl::string> >("\n\tpreorder_it<stl::string>          ");
	preorder_it<misc::tree<std::string> > ("\n\tpreorder_it<std::string>           ");
}

void test_tree::preorder_const_it()
{

	stl::cout << "\n\n\tpreorder_const_it--------------------------------------";

	preorder_const_it<misc::tree<stl::string> >("\n\tpreorder_const_it<stl::string>    ");
	preorder_const_it<misc::tree<std::string> > ("\n\tpreorder_const_it<std::string>     ");
}

void test_tree::postorder_it()
{
	stl::cout << "\n\n\tpostorder_it-------------------------------------------";

	postorder_it<misc::tree<stl::string> >("\n\tpostorder_it<stl::string>         ");
	postorder_it<misc::tree<std::string> > ("\n\tpostorder_it<std::string>          ");
}

void test_tree::postorder_const_it()
{
	stl::cout << "\n\n\tpostorder_const_it-------------------------------------";

	postorder_const_it<misc::tree<stl::string> >("\n\tpostorder_const_it<stl::string>   ");
	postorder_const_it<misc::tree<std::string> > ("\n\tpostorder_const_it<std::string>    ");
}

void test_tree::first_branch_it()
{
	stl::cout << "\n\n\tfirst_branch_it----------------------------------------";

	first_branch_it<misc::tree<stl::string> >("\n\tfirst_branch_it<stl::string>      ");
	first_branch_it<misc::tree<std::string> > ("\n\tfirst_branch_it<std::string>       ");
}

void test_tree::first_branch_const_it()
{
	stl::cout << "\n\n\tfirst_branch_const_it----------------------------------";

	first_branch_const_it<misc::tree<stl::string> >("\n\tfirst_branch_const_it<stl::string>");
	first_branch_const_it<misc::tree<std::string> > ("\n\tfirst_branch_const_it<std::string> ");
}

void test_tree::child_it()
{
	stl::cout << "\n\n\tchild_it-----------------------------------------------";

	child_it<misc::tree<stl::string> >("\n\tchild_it<stl::string>             ");
	child_it<misc::tree<std::string> > ("\n\tchild_it<std::string>              ");
}

void test_tree::child_const_it()
{
	stl::cout << "\n\n\tchild_const_it-----------------------------------------";

	child_const_it<misc::tree<stl::string> >("\n\tchild_const_it<stl::string>       ");
	child_const_it<misc::tree<std::string> > ("\n\tchild_const_it<std::string>        ");
}



// -- main class --
void test_tree::ctor()
{
	stl::cout << "\n\n\tctor---------------------------------------------------";

	ctor<misc::tree<stl::string> >("\n\tctor<stl::string>                 ");
	ctor<misc::tree<std::string> > ("\n\tctor<std::string>                  ");
}

void test_tree::dtor()
{
	stl::cout << "\n\n\tdtor---------------------------------------------------";

	dtor<misc::tree<stl::string> >("\n\tdtor<stl::string>                 ");
	dtor<misc::tree<std::string> > ("\n\tdtor<std::string>                  ");
}

void test_tree::copy_ctor()
{
	stl::cout << "\n\n\tcopy_ctor----------------------------------------------";

	copy_ctor<misc::tree<stl::string> >("\n\tcopy_ctor<stl::string>            ");
	copy_ctor<misc::tree<std::string> > ("\n\tcopy_ctor<std::string>             ");
}

void test_tree::copy_op()
{
	stl::cout << "\n\n\tcopy_op------------------------------------------------";

	copy_op<misc::tree<stl::string> >("\n\tcopy_op<stl::string>              ");
	copy_op<misc::tree<std::string> > ("\n\tcopy_op<std::string>               ");
}

void test_tree::get_it()
{
	stl::cout << "\n\n\tget_it-------------------------------------------------";

	get_it<misc::tree<stl::string> >("\n\tget_it<stl::string>               ");
	get_it<misc::tree<std::string> > ("\n\tget_it<std::string>                ");
}

void test_tree::push_back_val()
{
	stl::cout << "\n\n\tpush_back_val------------------------------------------";

	push_back_val<misc::tree<stl::string> >("\n\tpush_back_val<stl::string>        ");
	push_back_val<misc::tree<std::string> > ("\n\tpush_back_val<std::string>         ");
}

void test_tree::push_front_val()
{
	stl::cout << "\n\n\tpush_front_val-----------------------------------------";

	push_front_val<misc::tree<stl::string> >("\n\tpush_front_val<stl::string>       ");
	push_front_val<misc::tree<std::string> > ("\n\tpush_front_val<std::string>        ");
}

void test_tree::insert_sibling_before_val()
{
	stl::cout << "\n\n\tinsert_sibling_before_val------------------------------";

	insert_sibling_before_val<misc::tree<stl::string> >("\n\tinsert_sibling_before_val<misc>    ");
	insert_sibling_before_val<misc::tree<std::string> > ("\n\tinsert_sibling_before_val<std>     ");
}

void test_tree::insert_sibling_after_val()
{
	stl::cout << "\n\n\tinsert_sibling_after_val-------------------------------";

	insert_sibling_after_val<misc::tree<stl::string> >("\n\tinsert_sibling_after_val<misc>     ");
	insert_sibling_after_val<misc::tree<std::string> > ("\n\tinsert_sibling_after_val<std>      ");
}

void test_tree::push_back_child_val()
{
	stl::cout << "\n\n\tpush_back_child_val------------------------------------";

	push_back_child_val<misc::tree<stl::string> >("\n\tpush_back_child_val<stl::string>  ");
	push_back_child_val<misc::tree<std::string> > ("\n\tpush_back_child_val<std::string>   ");
}

void test_tree::push_front_child_val()
{
	stl::cout << "\n\n\tpush_front_child_val-----------------------------------";

	push_front_child_val<misc::tree<stl::string> >("\n\tpush_front_child_val<stl::string> ");
	push_front_child_val<misc::tree<std::string> > ("\n\tpush_front_child_val<std::string>  ");
}

void test_tree::push_back_tree()
{
	stl::cout << "\n\n\tpush_back_tree-----------------------------------------";

	push_back_tree<misc::tree<stl::string> >("\n\tpush_back_tree<stl::string>       ");
	push_back_tree<misc::tree<std::string> > ("\n\tpush_back_tree<std::string>        ");
}

void test_tree::push_front_tree()
{
	stl::cout << "\n\n\tpush_front_tree----------------------------------------";

	push_front_tree<misc::tree<stl::string> >("\n\tpush_front_tree<stl::string>      ");
	push_front_tree<misc::tree<std::string> > ("\n\tpush_front_tree<std::string>       ");
}

void test_tree::insert_sibling_before_tree()
{
	stl::cout << "\n\n\tinsert_sibling_before_tree-----------------------------";

	insert_sibling_before_tree<misc::tree<stl::string> >("\n\tinsert_sibling_before_tree<misc>   ");
	insert_sibling_before_tree<misc::tree<std::string> > ("\n\tinsert_sibling_before_tree<std>    ");
}

void test_tree::insert_sibling_after_tree()
{
	stl::cout << "\n\n\tinsert_sibling_after_tree------------------------------";

	insert_sibling_after_tree<misc::tree<stl::string> >("\n\tinsert_sibling_after_tree<misc>    ");
	insert_sibling_after_tree<misc::tree<std::string> > ("\n\tinsert_sibling_after_tree<std>     ");
}

void test_tree::push_back_child_tree()
{
	stl::cout << "\n\n\tpush_back_child_tree-----------------------------------";

	push_back_child_tree<misc::tree<stl::string> >("\n\tpush_back_child_tree<stl::string> ");
	push_back_child_tree<misc::tree<std::string> > ("\n\tpush_back_child_tree<std::string>  ");
}

void test_tree::push_front_child_tree()
{
	stl::cout << "\n\n\tpush_front_child_tree----------------------------------";

	push_front_child_tree<misc::tree<stl::string> >("\n\tpush_front_child_tree<stl::string>");
	push_front_child_tree<misc::tree<std::string> > ("\n\tpush_front_child_tree<std::string> ");
}

void test_tree::preorder_begin()
{
	stl::cout << "\n\n\tpreorder_begin-----------------------------------------";

	preorder_begin<misc::tree<stl::string> >("\n\tpreorder_begin<stl::string>       ");
	preorder_begin<misc::tree<std::string> > ("\n\tpreorder_begin<std::string>        ");
}

void test_tree::preorder_end()
{
	stl::cout << "\n\n\tpreorder_end-------------------------------------------";

	preorder_end<misc::tree<stl::string> >("\n\tpreorder_end<stl::string>         ");
	preorder_end<misc::tree<std::string> > ("\n\tpreorder_end<std::string>          ");
}

void test_tree::preorder_begin_it()
{
	stl::cout << "\n\n\tpreorder_begin_it--------------------------------------";

	preorder_begin_it<misc::tree<stl::string> >("\n\tpreorder_begin_it<stl::string>    ");
	preorder_begin_it<misc::tree<std::string> > ("\n\tpreorder_begin_it<std::string>     ");
}

void test_tree::preorder_end_it()
{
	stl::cout << "\n\n\tpreorder_end_it----------------------------------------";

	preorder_end_it<misc::tree<stl::string> >("\n\tpreorder_end_it<stl::string>      ");
	preorder_end_it<misc::tree<std::string> > ("\n\tpreorder_end_it<std::string>       ");
}

void test_tree::postorder_begin()
{
	stl::cout << "\n\n\tpostorder_begin----------------------------------------";

	postorder_begin<misc::tree<stl::string> >("\n\tpostorder_begin<stl::string>      ");
	postorder_begin<misc::tree<std::string> > ("\n\tpostorder_begin<std::string>       ");
}

void test_tree::postorder_end()
{
	stl::cout << "\n\n\tpostorder_end------------------------------------------";

	postorder_end<misc::tree<stl::string> >("\n\tpostorder_end<stl::string>        ");
	postorder_end<misc::tree<std::string> > ("\n\tpostorder_end<std::string>         ");
}

void test_tree::postorder_begin_it()
{
	stl::cout << "\n\n\tpostorder_begin_it-------------------------------------";

	postorder_begin_it<misc::tree<stl::string> >("\n\tpostorder_begin_it<stl::string>   ");
	postorder_begin_it<misc::tree<std::string> > ("\n\tpostorder_begin_it<std::string>    ");
}

void test_tree::postorder_end_it()
{
	stl::cout << "\n\n\tpostorder_end_it---------------------------------------";

	postorder_end_it<misc::tree<stl::string> >("\n\tpostorder_end_it<stl::string>     ");
	postorder_end_it<misc::tree<std::string> > ("\n\tpostorder_end_it<std::string>      ");
}

void test_tree::first_branch_begin()
{
	stl::cout << "\n\n\tfirst_branch_begin-------------------------------------";

	first_branch_begin<misc::tree<stl::string> >("\n\tfirst_branch_begin<stl::string>   ");
	first_branch_begin<misc::tree<std::string> > ("\n\tfirst_branch_begin<std::string>    ");
}

void test_tree::first_branch_end()
{
	stl::cout << "\n\n\tfirst_branch_end---------------------------------------";

	first_branch_end<misc::tree<stl::string> >("\n\tfirst_branch_end<stl::string>     ");
	first_branch_end<misc::tree<std::string> > ("\n\tfirst_branch_end<std::string>      ");
}

void test_tree::first_branch_begin_it()
{
	stl::cout << "\n\n\tfirst_branch_begin_it----------------------------------";

	first_branch_begin_it<misc::tree<stl::string> >("\n\tfirst_branch_begin_it<stl::string>");
	first_branch_begin_it<misc::tree<std::string> > ("\n\tfirst_branch_begin_it<std::string> ");
}

void test_tree::first_branch_end_it()
{
	stl::cout << "\n\n\tfirst_branch_end_it------------------------------------";

	first_branch_end_it<misc::tree<stl::string> >("\n\tfirst_branch_end_it<stl::string>  ");
	first_branch_end_it<misc::tree<std::string> > ("\n\tfirst_branch_end_it<std::string>   ");
}

void test_tree::child_begin()
{
	stl::cout << "\n\n\tchild_begin--------------------------------------------";

	child_begin<misc::tree<stl::string> >("\n\tchild_begin<stl::string>          ");
	child_begin<misc::tree<std::string> > ("\n\tchild_begin<std::string>           ");
}

void test_tree::child_end()
{
	stl::cout << "\n\n\tchild_end----------------------------------------------";

	child_end<misc::tree<stl::string> >("\n\tchild_end<stl::string>            ");
	child_end<misc::tree<std::string> > ("\n\tchild_end<std::string>             ");
}

void test_tree::child_begin_it()
{
	stl::cout << "\n\n\tchild_begin_it-----------------------------------------";

	child_begin_it<misc::tree<stl::string> >("\n\tchild_begin_it<stl::string>       ");
	child_begin_it<misc::tree<std::string> > ("\n\tchild_begin_it<std::string>        ");
}

void test_tree::child_end_it()
{
	stl::cout << "\n\n\tchild_end_it-------------------------------------------";

	child_end_it<misc::tree<stl::string> >("\n\tchild_end_it<stl::string>         ");
	child_end_it<misc::tree<std::string> > ("\n\tchild_end_it<std::string>          ");
}

void test_tree::siblings_begin()
{
	stl::cout << "\n\n\tsiblings_begin-----------------------------------------";

	siblings_begin<misc::tree<stl::string> >("\n\tsiblings_begin<stl::string>       ");
	siblings_begin<misc::tree<std::string> > ("\n\tsiblings_begin<std::string>        ");
}

void test_tree::siblings_end()
{
	stl::cout << "\n\n\tsiblings_end-------------------------------------------";

	siblings_end<misc::tree<stl::string> >("\n\tsiblings_end<stl::string>         ");
	siblings_end<misc::tree<std::string> > ("\n\tsiblings_end<std::string>          ");
}

void test_tree::siblings_begin_it()
{
	stl::cout << "\n\n\tsiblings_begin_it--------------------------------------";

	siblings_begin_it<misc::tree<stl::string> >("\n\tsiblings_begin_it<stl::string>    ");
	siblings_begin_it<misc::tree<std::string> > ("\n\tsiblings_begin_it<std::string>     ");
}

void test_tree::siblings_end_it()
{
	stl::cout << "\n\n\tsiblings_end_it----------------------------------------";

	siblings_end_it<misc::tree<stl::string> >("\n\tsiblings_end_it<stl::string>      ");
	siblings_end_it<misc::tree<std::string> > ("\n\tsiblings_end_it<std::string>       ");
}

void test_tree::empty()
{
	stl::cout << "\n\n\tempty--------------------------------------------------";

	empty<misc::tree<stl::string> >("\n\tempty<stl::string>                ");
	empty<misc::tree<std::string> > ("\n\tempty<std::string>                 ");
}

void test_tree::size()
{
	stl::cout << "\n\n\tsize---------------------------------------------------";

	size<misc::tree<stl::string> >("\n\tsize<stl::string>                 ");
	size<misc::tree<std::string> > ("\n\tsize<std::string>                  ");
}

void test_tree::clear()
{
	stl::cout << "\n\n\tclear--------------------------------------------------";

	clear<misc::tree<stl::string> >("\n\tclear<stl::string>                ");
	clear<misc::tree<std::string> > ("\n\tclear<std::string>                 ");
}

void test_tree::erase()
{
	stl::cout << "\n\n\terase--------------------------------------------------";

	erase<misc::tree<stl::string> >("\n\terase<stl::string>                ");
	erase<misc::tree<std::string> > ("\n\terase<std::string>                 ");
}


//////////////////////////////////////////////////////////////////////////
// template version
template<typename container>
void test_tree::preorder_it(const char* msg)
{
	//tree<string> template needed to make this work.
	typedef container Tree;	
	typedef typename Tree::value_type Tval;
	Tree tree0;
		

	/*
                    root
                     |
       1------------ 2 --------------- 3
       |             |                 |
    4 --- 7          9                12
    |     |          |                 |
  5---6   8         10            13 ----- 14
                     |
                    11

	*/

	typename Tree::iterator i1 = tree0.push_back(Tval("1"));
	typename Tree::iterator i2 = tree0.push_back(Tval("2"));
	typename Tree::iterator i3 = tree0.push_back(Tval("3"));

	typename Tree::iterator i4 = tree0.push_back_child(i1, Tval("4"));
	typename Tree::iterator i7 = tree0.push_back_child(i1, Tval("7"));

	typename Tree::iterator i5 = tree0.push_back_child(i4, Tval("5"));
	typename Tree::iterator i6 = tree0.push_back_child(i4, Tval("6"));
	typename Tree::iterator i8 = tree0.push_back_child(i7, Tval("8"));

	typename Tree::iterator i9 = tree0.push_back_child(i2, Tval("9"));
	typename Tree::iterator i10 = tree0.push_back_child(i9, Tval("10"));
	typename Tree::iterator i11 = tree0.push_back_child(i10, Tval("11"));

	typename Tree::iterator i12 = tree0.push_back_child(i3, Tval("12"));
	typename Tree::iterator i13 = tree0.push_back_child(i12, Tval("13"));
	typename Tree::iterator i14 = tree0.push_back_child(i12, Tval("14"));

	//TEST
	{
		time_printer tp(msg, m_print_time);

	}


	// tree complete
	TEST_CHECK(tree0.size() == 14);

	// checking preorder_iterator functions
	Tval ctrlVal[] =
	{
		U("1"),U("4"),U("5"),U("6"),U("7"),U("8"),U("2"),U("9"),
		U("10"),U("11"),U("3"),U("12"),U("13"),U("14")
	};

	// default ctor()
	typename Tree::preorder_iterator* poptr = new typename Tree::preorder_iterator();
	// dtor
	delete poptr;

	// default ctor, copy operator
	typename Tree::preorder_iterator pob0, poe0;

	pob0 = tree0.preorder_begin();
	poe0 = tree0.preorder_end();

	for(size_t i=0; i < tree0.size() && pob0 != poe0; pob0++, i++)//post-increment
	{
		TEST_CHECK(*pob0 == ctrlVal[i]);
	}
	
	// increment operator
	typename Tree::preorder_iterator pob2 = tree0.preorder_begin();
	typename Tree::preorder_iterator poe2 = tree0.preorder_end();
	for(size_t i=0; i < tree0.size() && pob2 != poe2; ++pob2, ++i)//pre-increment
	{
		TEST_CHECK(*pob2 == ctrlVal[i]);
	}

	typename Tree::preorder_iterator pob3 = tree0.preorder_begin();
	typename Tree::preorder_iterator poe3 = tree0.preorder_end();
	for(size_t i=0; i < tree0.size() && !(pob3 == poe3); ++pob3, ++i)//equal operator
	{
		TEST_CHECK(*pob3 == ctrlVal[i]);
	}


	// decrement operator
	typename Tree::preorder_iterator pob4 = tree0.preorder_begin();
	typename Tree::preorder_iterator poe4 = tree0.preorder_end();
	//poe4--;
	--poe4;
	for(int i=tree0.size()-1; i >= 0 && poe4 != pob4; pob4--, i--)//post-decrement
	{
		TEST_CHECK(*poe4 == ctrlVal[i]);
	}

	typename Tree::preorder_iterator pob5 = tree0.preorder_begin();
	typename Tree::preorder_iterator poe5 = tree0.preorder_end();
	--poe5;
	for(int i=tree0.size()-1; i >=0 && !(poe5 == pob5); --poe5, --i)//pre-decrement
	{
		TEST_CHECK(*poe5 == ctrlVal[i]);
		TEST_CHECK(*(poe5.operator->()) == ctrlVal[i]);
	}

	typename Tree::preorder_iterator pob6 = tree0.preorder_begin();
	for(size_t i=0; i < tree0.size() && pob6 != tree0.preorder_end(); ++pob6, ++i)
	{
		TEST_CHECK(*pob6 == ctrlVal[i]);

		typename Tree::iterator ib6 = tree0.get_iterator(pob6);
		typename Tree::preorder_iterator pob6_2(ib6);
		TEST_CHECK(pob6_2 == pob6);
	}

	TEST_CHECK(pob6 == pob6);
	TEST_CHECK(pob6 == tree0.preorder_end());
}

template<typename container>
void test_tree::preorder_const_it(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::postorder_it(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::postorder_const_it(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::first_branch_it(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::first_branch_const_it(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::child_it(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::child_const_it(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}


// -- main class --
template<typename container>
void test_tree::ctor(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::dtor(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::copy_ctor(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::copy_op(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::get_it(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::push_back_val(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::push_front_val(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::insert_sibling_before_val(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::insert_sibling_after_val(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::push_back_child_val(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::push_front_child_val(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::push_back_tree(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::push_front_tree(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::insert_sibling_before_tree(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::insert_sibling_after_tree(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::push_back_child_tree(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::push_front_child_tree(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::preorder_begin(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::preorder_end(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::preorder_begin_it(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::preorder_end_it(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::postorder_begin(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::postorder_end(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::postorder_begin_it(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::postorder_end_it(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::first_branch_begin(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::first_branch_end(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::first_branch_begin_it(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::first_branch_end_it(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::child_begin(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::child_end(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::child_begin_it(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::child_end_it(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::siblings_begin(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::siblings_end(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::siblings_begin_it(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::siblings_end_it(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::empty(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::size(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::clear(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}

template<typename container>
void test_tree::erase(const char* msg)
{
	//TEST
	{
		time_printer tp(msg, m_print_time);

	}
}
