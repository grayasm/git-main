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




#ifndef __Lexer_hpp__
#define __Lexer_hpp__


//std
#include <map>

//lib
#include "stream.hpp"

//local
#include "Base.hpp"
#include "IniParams.hpp"


namespace lex
{
	
	class Lexer
	{
	public:		
		typedef lex::Base::Tree Tree;
		typedef Tree::first_branch_iterator Fbit;
		typedef Tree::iterator It;
		typedef Tree::child_iterator ChildIt;
		typedef lex::Base::Reports	Reports;


		static Lexer& Inst();
		static void Destroy();

		void Initialize(const Base::Ptr& start, const lex::Base::Ptr& term, const IniParams& params);
		void CheckFile(lex::InputFile& in, lex::Base::Syntax& syntax, Reports& reports);
		bool CheckStart(lex::InputFile& in, unsigned int c, lex::Base::Productions& prods, lex::Report& rep);
		bool CheckTree(lex::InputFile& in, unsigned int c, Tree& tree, lex::Base::Productions& prods, lex::Token& token, lex::Report& rep);			
		bool CheckBranches(lex::InputFile& in, unsigned int c, Tree& tree, Fbit beg, Fbit end, lex::Base::Productions& prods, lex::Token& token, lex::Report& rep);		

		void Recover(lex::InputFile& in, unsigned int& c, Base::Ptr term);
		void SolveAmbiguity(lex::Base::Productions& prods);
		void AddProduction(lex::Base::Syntax& syntax, const lex::Base::Productions& prod);		


	private:
		Lexer();
		~Lexer();
		static Lexer* m_inst;

		Lexer(const Lexer&);
		Lexer& operator=(const Lexer&);


	private:		
		lex::Base::Ptr m_start;
		lex::Base::Ptr m_term;
		lex::IniParams m_iniparams;		
	};



};//namespace lex







#endif//__Lexer_hpp__



