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


#include "Alias.hpp"
#include "Lexer.hpp"
#include "stdio.hpp"//access in Debug.hpp


namespace lex
{
	Alias::~Alias()
	{
	};

	Alias::Alias(const Tree::Ptr& ptree)
		: Base()
	{
		Init();

		m_tree = ptree;
	};
	
	Alias::Alias(const Alias& tc)
		: Base()
	{
		Init();

		*this=tc;
	};


	Alias& Alias::operator=(const Alias& tc)
	{
		if(this!=&tc)
		{
			m_tree = tc.m_tree;
			m_flags = tc.m_flags;
			m_error = tc.m_error;
			m_attribute = tc.m_attribute;
		}
		return *this;
	};


	bool Alias::check( lex::InputFile& in, unsigned int c, Productions& prods, Token& token, lex::Report& rep )
	{
		Productions p2_loc;
		p2_loc.push_back(Production());
		Token t_loc = token;
		bool brep = false;
		FPOS_DECL(in);

		
		bool res = lex::Lexer::Inst().CheckTree(in, c, *m_tree, p2_loc, t_loc, rep);

		if(res)
		{
			select(prods, token, p2_loc, t_loc);			
		}
		else
		{			
			brep = rep.report(m_error, in.tellg(), in.row(), in.col());
			FPOS_CMP(in);
		}

		LF_DUMP("Alias", res, c, in, brep, m_error, t_loc, *prods.begin());
		
		return res;
	}//check



	void Alias::Set(unsigned long flags)
	{
		m_flags = flags;
	};


	unsigned long Alias::Get()const
	{
		return m_flags;
	};

	Base::Ptr Alias::Clone()const
	{
		Alias::Ptr copy = new Alias(NULL);
		*copy=*this;
		return copy;
	};

	void Alias::SetError(const lex::Error& er)
	{
		m_error = er;
	};

	void Alias::SetAttr(int attribute)
	{
		m_attribute = attribute;
	};

	void Alias::Init()
	{
		m_tree = NULL;
		m_flags = Base::F_NOBIT;
		//m_error;
		m_attribute = 0;
	};


	void Alias::select(Productions& prods, Token& token, Productions& p2_loc, Token& t_loc)
	{
		if(m_flags & Base::F_BRKSTR)
		{						
			if(!t_loc.GetToken().empty()) 
			{
				t_loc.SetAttr(m_attribute);
				(*p2_loc.begin()).push_back(t_loc);
			}			

			token.Clear();

			Production& p0_loc = *p2_loc.begin();
			Production& prod = *prods.begin();
			std::copy(p0_loc.begin(), p0_loc.end(), std::back_inserter(prod));
		}
		else
		{
			if( !(*p2_loc.begin()).empty() )
				throw misc::exception("not expected.");

			token = t_loc;

			//ambiguous attribute for this composed rule (e.g. r & alias)
			//it may not be relevant to set attribute here, but at higher level

		}
	};


};//namespace lex




lex::Base::Ptr operator & (lex::Base::Ptr rLeft, lex::Base::Ptr rRight)
{
	lex::Base::Ptr left = rLeft->Clone();
	lex::Base::Ptr right = rRight->Clone();

	unsigned long flags = left->Get();
	flags &= ~lex::Base::F_BRKSTR;
	left->Set(flags);

	flags = right->Get();
	flags &= ~lex::Base::F_BRKSTR;
	right->Set(flags);


	lex::Base::Tree::Ptr tree = new lex::Base::Tree();
	lex::Base::Tree::iterator pos = tree->push_back(left);
	tree->push_back_child(pos, right);
	
	lex::Base::Ptr alias = new lex::Alias(tree);
	alias->Set(flags);

	return alias;	
};

lex::Base::Ptr operator | (lex::Base::Ptr rLeft, lex::Base::Ptr rRight)
{
	lex::Base::Ptr left = rLeft->Clone();
	lex::Base::Ptr right = rRight->Clone();

	unsigned long flags = left->Get();
	flags &= ~lex::Base::F_BRKSTR;
	left->Set(flags);

	flags = right->Get();
	flags &= ~lex::Base::F_BRKSTR;
	right->Set(flags);


	lex::Base::Tree::Ptr tree = new lex::Base::Tree();
	tree->push_back(left);
	tree->push_back(right);
	
	lex::Base::Ptr alias = new lex::Alias(tree);
	alias->Set(flags);

	return alias;
};





lex::Base::Ptr operator && (lex::Base::Ptr rLeft, lex::Base::Ptr rRight)
{
	lex::Base::Ptr left = rLeft->Clone();
	lex::Base::Ptr right = rRight->Clone();

	unsigned long flags = left->Get();
	flags |= lex::Base::F_BRKSTR;
	left->Set(flags);

	flags = right->Get();
	flags |= lex::Base::F_BRKSTR;
	right->Set(flags);


	lex::Base::Tree::Ptr tree = new lex::Base::Tree();
	lex::Base::Tree::iterator pos = tree->push_back(left);
	tree->push_back_child(pos, right);
	
	lex::Alias::Ptr alias = new lex::Alias(tree);
	alias->Set(flags);

	return alias;
};

lex::Base::Ptr operator || (lex::Base::Ptr rLeft, lex::Base::Ptr rRight)
{
	lex::Base::Ptr left = rLeft->Clone();
	lex::Base::Ptr right = rRight->Clone();

	unsigned long flags = left->Get();
	flags |= lex::Base::F_BRKSTR;
	left->Set(flags);

	flags = right->Get();
	flags |= lex::Base::F_BRKSTR;
	right->Set(flags);


	lex::Base::Tree::Ptr tree = new lex::Base::Tree();
	tree->push_back(left);
	tree->push_back(right);
	
	lex::Base::Ptr alias = new lex::Alias(tree);
	alias->Set(flags);

	return alias;
};





