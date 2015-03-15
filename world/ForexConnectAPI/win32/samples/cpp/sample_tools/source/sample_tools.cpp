// sample_tools.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"


#ifdef _MANAGED
#pragma managed(push, off)
#endif

#ifdef WIN32
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    return TRUE;
}
#endif

#ifdef _MANAGED
#pragma managed(pop)
#endif

