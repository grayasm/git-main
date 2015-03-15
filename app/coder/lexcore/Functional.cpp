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



#include "Functional.hpp"



lex::Base::Ptr  LEX(lex::Base::Ptr rule, int attribute, const misc::string& error, int level)
{
	lex::Error er;
	er.SetMsg(error);
	er.SetLevel(level);
	lex::Base::Ptr new_rule = rule->Clone();
	if(error != "" && level != 0)
	{
		new_rule->SetError(er);		
	}
	new_rule->SetAttr(attribute);
	return new_rule;	
};



