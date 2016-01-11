#ifdef DLL1_EXPORTS
#define DLL1_API __declspec(dllexport)
#else
#define DLL1_API __declspec(dllimport)
#endif


class DLL1_API Dll1
{
public:
	Dll1();
	~Dll1();
	int func1(int l, int r);
};