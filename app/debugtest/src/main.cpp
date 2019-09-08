
#include "file.hpp"
#include "stream.hpp"

int files = 0;
void scancb(const stl::string& filepath, bool& abort)
{
    if (++files > 55)
        abort = true;

    stl::cout << filepath.c_str() << std::endl;
}

int main(int argc, char *argv[])
{
    sys::file f;
    f.scandir(
        "d:\\GitHub\\git-main\\",
        sys::file::S_TRAVERSE |
        //sys::file::S_DOT_DIRS |
        //sys::file::S_HIDDEN_FILE |
        sys::file::S_HIDDEN_DIR,
        -1,
        scancb
        );
}

