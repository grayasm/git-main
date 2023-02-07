/*
Copyright (C) 2009 Mihai Vasilian
*/


#ifndef __exception_hpp__
#define __exception_hpp__


#include <exception>


namespace stl
{
    class exception : public std::exception
    {
    public:
        exception();                
        exception(const char* str);
        ~exception() throw();        
        const char* what() const throw();        
    private:
        char*   m_str;
    };
    
}  // namespace

#endif   /* __exception_hpp__ */
