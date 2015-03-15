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


#ifndef __Debug_hpp__
#define __Debug_hpp__



#include "string.hpp"
#include "stdio.hpp"
#include "stream.hpp"



/*******************************************************************************
	D_FILE_POS	- compile flag for the minimal file stream position checking.
	Normally if a rule returns false, the stream should not be advanced.	
********************************************************************************/


//FPOS_DECL
#ifdef D_FILE_POS
#define FPOS_DECL(F)	\
	size_t file_position_decl = F.tellg()
#else
#define FPOS_DECL(F)
#endif

//FPOS_SET
#ifdef D_FILE_POS
#define FPOS_SET(F)		\
	file_position_decl = F.tellg()
#else
#define FPOS_SET(F)
#endif


//FPOS_CMP
#ifdef D_FILE_POS
#define FPOS_CMP(F2)	\
	assert(file_position_decl == F2.tellg())
#else
#define FPOS_CMP(F2)
#endif



#ifdef D_FILE_POS
#define FPOS_INC(F)		\
	file_position_decl += F
#else
#define FPOS_INC(F)
#endif



#ifdef D_FILE_POS
#define FPOS_DEC(F)		\
	file_position_decl -= F
#else
#define FPOS_DEC(F)
#endif


/********************************************************************************
	D_LEX_PARSE	 - compile flag for the lexer parsing activity. 
	Lexer dumps some minimal debugging information.
*********************************************************************************/

#ifdef D_LEX_PARSE
	extern misc::string lex_parsing_dump;
#endif


#ifdef D_LEX_PARSE
#define LF_CREAT(F)														\
	lex_parsing_dump=misc::string(F);									\
	misc::ofstream lex_parsing_stream(F, std::ios_base::trunc);			\
	if( !lex_parsing_stream.is_open() ) {								\
		misc::string er("cannot open log: "); er += misc::string(F);		\
		throw misc::exception(er.c_str());								\
	}																	\
	lex_parsing_stream << "\n";											\
	lex_parsing_stream.close();											\
	if( access(F, 0) != 0 ) {											\
		misc::string er("cannot create log: "); er += misc::string(F);	\
		throw misc::exception(er.c_str());								\
	}
#else
#define LF_CREAT(F) NULL
#endif




#ifdef D_LEX_PARSE
#define LF_RESET()		\
	lex_parsing_dump=""
#else
#define LF_RESET() NULL
#endif



#ifdef D_LEX_PARSE
#define LF_DUMP(CLSNAME, RES, C, IN, BREP, ERR, TOK, PROD)											\
	{																								\
		if( !lex_parsing_dump.empty() && access(lex_parsing_dump.c_str(), 0) == 0)					\
		{																							\
			misc::ofstream lex_parsing_writer(lex_parsing_dump.c_str(), std::ios_base::app);			\
			if( lex_parsing_writer.is_open() )														\
			{																						\
				lex_parsing_writer << "\n"															\
					<< CLSNAME																		\
					<< " c='" << C << "'"															\
					<< " res= " << (RES == true ? "true" : "false")									\
					<< " fpos= " << IN.tellg()														\
					<< " row= " << IN.row()															\
					<< " col= " << IN.col()															\
					<< " err=" << "\"" << (BREP==true?ERR.GetMsg().c_str():"") << "\""				\
					<< " tok= \"" << TOK.GetToken().c_str() << "\" ";								\
																									\
				lex_parsing_writer << "PROD= \"" ;													\
				const lex::Base::Production& PROD1 = PROD;											\
				for(lex::Base::Production::const_iterator pb=PROD1.begin(); pb!=PROD1.end(); ++pb)	\
				{																					\
					const lex::Token& tok=*pb;														\
					lex_parsing_writer << tok.GetToken().c_str();									\
				}																					\
				lex_parsing_writer << "\"";															\
			}																						\
			lex_parsing_writer.close();																\
		}																							\
	}
#else
#define LF_DUMP(CLSNAME, RES, C, IN, BREP, ERR, TOK, PROD)	C;	TOK; PROD
#endif



#ifdef D_LEX_PARSE
#define LF_MSG(CLSNAME, FPOS, ROW, COL, MESSAGE)													\
	{																								\
		if( !lex_parsing_dump.empty() && access(lex_parsing_dump.c_str(), 0) == 0)					\
		{																							\
			misc::ofstream lex_parsing_writer(lex_parsing_dump.c_str(), std::ios_base::app);			\
			if( lex_parsing_writer.is_open() )														\
			{																						\
				lex_parsing_writer 	<< "\n"															\
					<< " fpos=" << FPOS																\
					<< " row=" << ROW																\
					<< " col=" << COL																\
					<< " msg=" << MESSAGE;															\
			}																						\
			lex_parsing_writer.close();																\
		}																							\
	}
#else
#define LF_MSG(CLSNAME, FPOS, ROW, COL, MESSAGE) MESSAGE
#endif




#endif//__Debug_hpp__


