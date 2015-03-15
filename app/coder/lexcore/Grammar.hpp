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


#ifndef __Grammar_hpp__
#define __Grammar_hpp__




//c/c++
#include <list>
#include <map>


//other
#include "Base.hpp"
#include "IniParams.hpp"


/*
	http://dictionary.reference.com/browse/grammar
	A formal definition of the syntactic structure (the syntax) of a language.
	A grammar is normally represented as a set of production rules which specify the order of constituents 
	and their sub-constituents in a sentence (a well-formed string in the language). 
	Each rule has a left-hand side symbol naming a syntactic category (e.g. "noun-phrase" for a natural language grammar)
	and a right-hand side which is a sequence of zero or more symbols.
	Each symbol may be either a terminal symbol or a non-terminal symbol. 	
	A terminal symbol corresponds to one "lexeme" - a part of the sentence with no internal syntactic structure 
	(e.g. an identifier or an operator in a computer language). 	
	A non-terminal symbol is the left-hand side of some rule.	
	One rule is normally designated as the top-level rule which gives the structure for a whole sentence.
	A parser (a kind of recognizer) uses a grammar to parse a sentence, assigning a terminal syntactic category to each input token and
	a non-terminal category to each appropriate group of tokens, up to the level of the whole sentence. 
	Parsing is usually preceded by lexical analysis. 
	The opposite, generation, starts from the top-level rule and chooses one alternative production wherever there is a choice.
	In computing, a formal grammar, e.g. in BNF, can be used to parse a linear input stream, such as the source code of a program, 
	into a data structure that expresses the (or a) meaning of the input in a form that is easier for the computer to work with.
	A compiler compiler like yacc might be used to convert a grammar into code for the parser of a compiler.
	A grammar might also be used by a transducer, a translator or a syntax directed editor. 
*/



namespace ebnf
{

	class Grammar
	{
	public:
		typedef misc::autoptr<Grammar>	Ptr;		
		typedef lex::Base::Production	Production;
		typedef lex::Base::Productions	Productions;
		typedef lex::Base::Syntax		Syntax;		
		typedef lex::Base::Map			Map;

		
		Grammar(){};
		virtual ~Grammar(){};

		virtual const lex::IniParams& GetIniParams()const=0;
		virtual lex::Base::Ptr GetStart()=0;
		virtual lex::Base::Ptr GetTerm()=0;
		
	};


};//namespace


#endif//__Grammar_hpp__