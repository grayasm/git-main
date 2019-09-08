
#include "file.hpp"
#include "stream.hpp"

int count = 0;
void scancb(const stl::string& filepath, bool& abort)
{
	if (count++ > 44)
		abort = true;
    stl::cout << filepath.c_str() << std::endl;
}

int main(int argc, char *argv[])
{
    sys::file f;
    f.scandir(
        "..\\",
		sys::file::S_TRAVERSE |
		sys::file::S_DOT_DIRS |
		sys::file::S_HIDDEN_DIR,
        12,
        scancb
        );
}

