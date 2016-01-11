#ifdef DLL2_EXPORTS
#define DLL2_API __declspec(dllexport)
#else
#define DLL2_API __declspec(dllimport)
#endif


class DLL2_API Dll2
{
public:
	Dll2();
	~Dll2();
	int func2(int l, int r);
};