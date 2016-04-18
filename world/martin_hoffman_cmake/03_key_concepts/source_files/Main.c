#include <stdio.h>

extern void file1();
extern void file2();
extern void file3();

int main(int argc, char** argv)
{
	printf("\nMessage from %s\n", __FILE__);
	file1();
	file2();
	file3();
	
	return 0;
}