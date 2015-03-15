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




#include "test_gen.hpp"
#include "filename.hpp"
#include "stdio.hpp"
#include "stream.hpp"




void test_gen::run(const char* test, bool log)
{
	misc::string testfile(test);
	WriteFile(testfile, GetText());

	//reference data
	ebnf::DefaultGrammar::Ptr grammar = new ebnf::DefaultGrammar();
	SetGrammar(grammar);		
	lex::Base::Syntax sref;
	lex::Base::Reports rref;
	SetSyntax(sref);	
	SetReports(rref);

	//setup log file
	misc::string test_log = MakePath(testfile, "_log").c_str();
	if(log) { LF_CREAT( test_log.c_str() ); }
	else if( access(test_log.c_str(), 0) == 0 ) { unlink( test_log.c_str() ); }

	//lexer produced data
	lex::Base::Syntax sres;
	lex::Base::Reports rres;
	lex::LexerInput lxInput(testfile, grammar);
	lxInput >> sres;
	rres = lxInput.GetReports();


	if(log) LF_RESET();




	bool bSynOk = true;
	bool bRepOk = true;


	misc::string syn_fail = MakePath(testfile, "_syn_fail");
	misc::string syn_ref = MakePath(testfile, "_syn_ref");
	misc::string rep_fail = MakePath(testfile, "_rep_fail");
	misc::string rep_ref =  MakePath(testfile, "_rep_ref");


	//SYNTAX EQUAL
	if(!CheckSyntax(sres, sref))
	{
		std::cout << testfile.c_str() << "       SYN-NOT OK" << std::endl;
		lex::LexerOutput resOut( syn_fail );
		resOut << sres;
		lex::LexerOutput refOut( syn_ref );
		refOut << sref;
		bSynOk = false;
	}	
	else
	{
		std::cout << testfile.c_str() << " SYN-OK" << std::endl;
		//lex::LexerOutput resr( MakePath(testfile, "_res") );
		//resr << sres;
	}

	//REPORTS EQUAL
	if(!CheckReports(rres, rref))
	{
		std::cout << testfile.c_str() << "       REPORTS-NOT OK" << std::endl;
		lex::LexerOutput resr( rep_fail );
		resr << rres;
		lex::LexerOutput refr( rep_ref );
		refr << rref;
		bRepOk = false;
	}	
	else
	{
		std::cout << testfile.c_str() << " REP-OK" << std::endl;
		//lex::LexerOutput resOut( MakePath(testfile, "_res") );
		//resOut << sres;
	}

	if(bSynOk && bRepOk)
	{	
		if(testfile != "test_14882_2003_annex_e")
			unlink(testfile.c_str());
	}

	if(bSynOk)
	{
		if(access(syn_fail.c_str(), 0) == 0) unlink(syn_fail.c_str());
		if(access(syn_ref.c_str(), 0) == 0) unlink(syn_ref.c_str());
	}

	if(bRepOk)
	{
		if(access(rep_fail.c_str(), 0) == 0) unlink(rep_fail.c_str());
		if(access(rep_ref.c_str(), 0) == 0) unlink(rep_ref.c_str());
	}


};




void test_gen::WriteFile(const std::string& fpath, char* text)
{
/*	FILE* f = fopen(fpath.c_str(), "w+");
	if(f == NULL) return;
	fwrite(text, sizeof(char), strlen(text), f);
	fclose(f);*/	
	misc::ofstream fout(fpath.c_str(), std::ios_base::trunc);	
	int i=0; 
	while(text[i] != '\0')
		fout << text[i++];
	fout.close();
};


bool test_gen::CheckSyntax(const lex::Base::Syntax& res, const lex::Base::Syntax& ref)
{
	if(res.size() != ref.size())//productions no. equal?
	{
		return false;
	}


	lex::Base::Syntax::const_iterator resb = res.begin(), rese = res.end();
	lex::Base::Syntax::const_iterator refb = ref.begin(), refe = ref.end();
	for(; resb != rese && refb != refe; ++resb, ++refb)
	{
		if((*resb).size() != (*refb).size())//tokens no. equal?
		{
			return false;
		}

		lex::Base::Production::const_iterator respb = (*resb).begin(), respe = (*resb).end();
		lex::Base::Production::const_iterator refpb = (*refb).begin(), refpe = (*refb).end();

		for(; respb != respe && refpb != refpe; ++respb, ++refpb)
		{
			if((*respb).GetToken() != (*refpb).GetToken() ||
				(*respb).GetAttr() != (*refpb).GetAttr()) 
			{
				return false;
			}
		}//for(tokens)
	};//for(productions)

	return true;
};

bool test_gen::CheckReports(const lex::Base::Reports& res, const lex::Base::Reports& ref)
{
	if(res.size() != ref.size())//not equal
	{
		return false;
	}


	lex::Base::Reports::const_iterator resb = res.begin(), rese = res.end();
	lex::Base::Reports::const_iterator refb = ref.begin(), refe = ref.end();
	for(; resb != rese && refb != refe; ++resb, ++refb)
	{
		const lex::Report& rep_res = *resb;
		const lex::Report& rep_ref = *refb;

		const lex::Report::ErrorList& err_res = rep_res.GetErrorList();
		const lex::Report::ErrorList& err_ref = rep_ref.GetErrorList();


		if(err_res.size() != err_ref.size())//same no of errors?
		{
			return false;
		}


		lex::Report::ErrorList::const_iterator resb = err_res.begin(), rese = err_res.end();
		lex::Report::ErrorList::const_iterator refb = err_ref.begin(), refe = err_ref.end();

		for(; resb != rese && refb != refe; ++resb, ++refb)
		{
			if((*resb).GetMsg() != (*refb).GetMsg() ||
				(*resb).GetLevel() != (*refb).GetLevel()) 
			{
				return false;
			}
		}//for(tokens)
	};//for(productions)

	return true;
};



misc::string test_gen::MakePath(const misc::string& fpath, const misc::string& append)
{
	misc::filename fres(fpath);
	misc::string filecore(fres.get_core_name());
	filecore += append;
	fres.set_core_name(filecore);
	return fres.get_path();
};
