#include <windows.h>
#include <string>
#include <nsis_api.h>



extern "C"
void __declspec(dllexport) TestFn(HWND hwndParent, int string_size, char *variables, stack_t **stacktop)
{
    // save stack_t pointer
    EXDLL_INIT();

    char param1[MAX_STRLEN], param2[MAX_STRLEN];
    popstring(param1);
    popstring(param2);

    std::string str("TestFn $0=");
    str += param1;
    str += " $1=";
    str += param2;
    MessageBox(hwndParent, str.c_str(), "TestFn", MB_OK);

    // return code
    pushstring("0");
}

BOOL WINAPI DllMain(HINSTANCE hInst, ULONG ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}
