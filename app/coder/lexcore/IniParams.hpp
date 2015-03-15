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




#ifndef __IniParams_hpp__
#define __IniParams_hpp__


namespace lex
{
	class IniParams
	{
	public:
		IniParams();
		~IniParams();

		/*
		http://en.wikipedia.org/wiki/GLR_parser
		Briefly, the GLR algorithm works in a manner similar to the LR parser algorithm, except that, given a particular grammar,
		a GLR parser will process all possible interpretations of a given input in a breadth-first search. 
		On the front-end, a GLR parser generator converts an input grammar into parser tables, in a manner similar to an LR generator.
		However, where LR parse tables allow for only one state transition (given a state and an input token),
		GLR parse tables allow for multiple transitions. In effect, GLR allows for shift/reduce and reduce/reduce conflicts.
		When a conflicting transition is encountered, the parse stack is forked into two or more parallel parse stacks, 
		where the state corresponding to each possible transition is at the top. 
		Then, the next input token is read and used to determine the next transition(s) for each of the "top" states – and further forking can occur. 
		If any given top state and input token do not result in at least one transition, then that "path" through the parse tables is invalid and can be discarded.
		A crucial optimization allows sharing of common prefixes and suffixes of these stacks, which constrains the overall search space 
		and memory usage required to parse input text. The complex structures that arise from this improvement make the search graph a directed acyclic graph 
		(with additional restrictions on the "depths" of various nodes), rather than a tree.
		*/		
		void SetGLR(bool enable);
		bool GetGLR()const;

		//! enables error reporting
		void SetError(bool enable);
		bool GetError()const;

	private:
		bool m_bGLR;
		bool m_bErrorReport;
	};

};//namespace

#endif//__IniParams_hpp__

