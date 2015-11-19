#include <stdio.h>

extern void file2();
extern void file3();
extern void file4();

int main(int argc, char** argv)
{
	printf("\nMessage from %s\n", __FILE__);
	file2();
	file3();
	file4();
	
	return 0;
}