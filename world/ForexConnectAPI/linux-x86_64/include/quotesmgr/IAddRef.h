#pragma once

namespace quotesmgr
{

/** Common interface for objects with reference counting
    
 */
class QUOTESMGR2_API IAddRef
{
 public:
    /** Adds a reference. */
    virtual long addRef() = 0;
    /** Releases a reference. */
    virtual long release() = 0;

 protected:
     virtual ~IAddRef() { }
};


}

