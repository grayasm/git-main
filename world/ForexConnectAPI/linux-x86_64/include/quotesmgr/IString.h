#pragma once

namespace quotesmgr
{

/** String class 

 */
class IString
{
 public:
 

    /** Sets string content
        @param str
            New string content. NULL value is possible it considered equal to ""
    
     */
    virtual void setString(const char *str) = 0;

    /** Gets string
        @return
            string pointer. Is string is empty return pointer to ""    
     */
    virtual const char *getString() const = 0;

    virtual bool empty() const = 0;

 protected:
    virtual ~IString() { }
};

} // ~namespace quotesmgr
