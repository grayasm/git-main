#pragma once

namespace quotesmgr
{

class IString;
/** Strings Loader class allow to load strings resources by id
    Basic usage:
    ...
        const std::string * errorStr = stringLoader->loadString(12);
        ...
        stringLoader->releaseString(errorStr);
    ...

 */
class IStringsLoader
{
 public:
     /** loads string by id
        @param resourceId
            string resource identifier 
     
        @param outStr
            [out] loaded string

         @return
            load result. true - strins is loaded succesfully. Otherwise false.
      */
     virtual bool loadString(int resourceId, IString *outStr) const = 0;

};

} // ~namespace quotesmgr
