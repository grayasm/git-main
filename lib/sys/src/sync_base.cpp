/*
Copyright (C) 2013 Mihai Vasilian
*/


#include "sync_base.hpp"




namespace sys
{    
	sync_visitor::sync_visitor()
	{
	}
	
	sync_visitor::~sync_visitor()
	{
	}
	
	sync_base::sync_base()
#ifdef _WIN32
		: m_handle(NULL)
#else
#endif
	{
	}

	sync_base::~sync_base()
	{
	}

} // namespace
