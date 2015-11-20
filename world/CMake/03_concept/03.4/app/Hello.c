#include <stdio.h>

extern void file1();

int main(int argc, char** argv)
{
	printf("\nMessage from %s\n", __FILE__);
	file1();

	return 0;
}