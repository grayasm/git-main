#include <iostream>
#include <stdlib.h>

#include "lang.hpp"

//misc
#include "filename.hpp"



int main(int argc, char** argv)
{

    //set file name path
    misc::filename text(argv[0]);
    text.set_file_name("content.txt");


    Content c;
    c.read(text.get_path().c_str());

    printf("\nLearn German");
    printf("\nCheck German words ? (a)");
    printf("\nCheck Romani words ? (b)");
    printf("\nOption = ");

    char buf[1000]="\0";
    std::cin.getline(buf, 1000);

    if(buf[0]=='a')
        c.show_ddd(true);
    else if(buf[0]=='b')
        c.show_ddd(false);


    
	return 0;
};
