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



#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <assert.h>

#include "InputFile.hpp"
#include "Lexer.hpp"

#include "EbnfGrammar.hpp"

#include "LexerInput.hpp"
#include "LexerOutput.hpp"

//libk1
#include "filename.hpp"



#ifdef WIN32
int main()
#else//Linux
int main(int argc, char** argv)
#endif
{
	

#ifdef WIN32	
	std::string fileName("file");
#else//Linux
	argc;
	misc::filename fn(argv[0]);
	fn.set_file_name("file");
	std::string fileName(fn.get_path().c_str());
#endif
		
	lex::Base::Syntax syntax;
	ebnf::Grammar::Ptr grammar = new ebnf::EbnfGrammar();
	lex::LexerInput greader(fileName, grammar);
	greader >> syntax;

	//write grammar
	lex::LexerOutput gwriter("grammar.log");
	gwriter << syntax;

	return 0;
}//main










