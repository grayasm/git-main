/*
Copyright (C) 2012 Mihai Vasilian
*/





#ifndef __autoptr_hpp__
#define __autoptr_hpp__



//c
#include <stdlib.h>
//c++
//stl
#include "exception.hpp"



namespace stl
{
    template<typename T>
    class autoptr
    {
    public:
        autoptr()
        {
            m_data = 0;
            m_count = 0;
        }

        autoptr(T* data)
        {
            if(data != 0)
            {
                m_data = data;
                m_count = new long(1);
            }
            else
            {
                m_data = 0;
                m_count = 0;
            }
        }

        ~autoptr()
        {
            if(m_data != 0)
            {
                if(*m_count == 1)
                {
                    delete m_data;
                    m_data = 0;

                    delete m_count;
                    m_count = 0;
                }
                else
                {
                    --*m_count;
                }
            }
        }

        autoptr(const autoptr<T>& ap)
        {
            if(ap.m_data == 0)
            {
                m_data = 0;
                m_count = 0;
            }
            else
            {
                m_data = ap.m_data;
                m_count = ap.m_count;
                ++*m_count;
            }
        }

        autoptr<T>& operator=(const autoptr<T>& ap)
        {
            if(this != &ap)
            {
                T* temp_data = 0;
                long* temp_count = 0;

                if(ap.m_data == 0)
                {
                    m_data = 0;
                    m_count = 0;
                }
                else
                {
                    temp_data = ap.m_data;
                    temp_count = ap.m_count;
                    ++*temp_count;
                }  //  else

                if(m_data != 0)
                {
                    if(*m_count == 1)
                    {
                        delete m_data;
                        m_data = 0;
                        delete m_count;
                        m_count = 0;
                    }
                    else
                    {
                        --*m_count;
                    }
                }

                m_data = temp_data;
                m_count = temp_count;
            }//if

            return *this ;
        }

        autoptr<T>& operator=(T* data)
        {
            if(m_data != 0)
            {
                if(*m_count == 1)
                {
                    delete m_data;
                    m_data = 0;
                    delete m_count;
                    m_count = 0;
                }
                else
                {
                    --*m_count;
                }
            }

            if(data == 0)
            {
                m_data = 0;
                m_count = 0;
            }
            else
            {
                m_data = data;
                m_count = new long(1);
            }

            return *this ;
        }

        bool IsNull() const
        {
            return m_data == 0;
        }

        bool IsNotNull() const
        {
            return !IsNull();
        }


        const T& operator*()const
        {
            if(m_data == 0)
                throw stl::exception("NULL pointer");

            return *m_data;
        }

        T& operator*()
        {            
            if(m_data == 0)
                throw stl::exception("NULL pointer");

            return *m_data;
        }


        const T* operator->()const
        {
            return m_data ;
        }

        T* operator->()
        {
            return m_data ;
        }


        /*
          The Safe bool idiom: http://www.artima.com/cppsource/safebool.html
          The compiler invokes this operator although it shouldn't. Ex:
          header: algorithm
          if(!(_Left < _Right)) invokes (bool) _Left < (bool) _Right
          which for 2 valid autoptr is: if(!(true < true)) -> if(true)

          operator bool() const
          {
          return m_data!=0 ;
          }
        */


        //ap<bz_abstr>=ap<derived>
        template<typename T2>
        autoptr(const autoptr<T2>& ap2)
        {
            if(ap2.m_data==0)
            {
                m_data=0 ;
                m_count=0 ;
            }
            else
            {
                m_data = static_cast<T*>(ap2.m_data);
                m_count=ap2.m_count ;
                ++*m_count ;
            }
        }

        template<typename T2>
        autoptr(T2* data)
        {
            if(data==0)
            {
                m_data=0 ;
                m_count=0;
            }
            else
            {
                m_data = static_cast<T*>(data);
                m_count=new long(1L) ;
            }
        }



        template<typename T2> friend class autoptr;

    private:
        T* m_data ;
        long* m_count ;
    };


} // namespace


#endif


