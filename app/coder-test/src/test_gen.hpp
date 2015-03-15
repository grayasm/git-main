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


#ifndef __test_gen_hpp__
#define __test_gen_hpp__


#include "lexer_inc.hpp"
#include "DefaultGrammar.hpp"


class test_gen
{
public:
	test_gen(){};
	//virtual
	virtual ~test_gen(){};
	virtual char* GetText()=0;
	virtual void SetGrammar(ebnf::DefaultGrammar::Ptr& grammar)=0;
	virtual void SetSyntax(lex::Base::Syntax& ref)=0;
	virtual void SetReports(lex::Base::Reports& reps)=0;


protected:
	void run(const char* test, bool log=false);

private:
	//	
	void WriteFile(const std::string& fpath, char* text);
	bool CheckSyntax(const lex::Base::Syntax& res, const lex::Base::Syntax& sref);
	bool CheckReports(const lex::Base::Reports& res, const lex::Base::Reports& rref);

private:
	//create path to reference / resulted syntax file
	misc::string MakePath(const misc::string& fpath, const misc::string& append);	
};//class






#endif//__test_gen_hpp__


