#ifndef __file2_hpp__
#define __file2_hpp__

#include <lib1/file1.hpp>

class File2 : public File1
{
public:
	File2();
	~File2();
	int get2() const
	{
		return File1::get() - 10;
	}
};
#endif // __file2_hpp__
