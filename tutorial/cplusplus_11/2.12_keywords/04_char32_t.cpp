/* Header     : core
   Signature  : char32_t
   Description: N3337, pag 25, 2.14.3 Character literals
                A character literal that begins with the letter U, such as U'z'
                is a character literal of type char32_t. The value of a char32_t
                literal containing a single c-char is equal to its ISO 10646
                code point value. A char32_t literal containing multiple c-chars
                is ill-formed.
*/


#include <stdio.h>
#include <locale.h>
#include <uchar.h>
#include <stdlib.h>


mbstate_t state;
int main(void)
{
	setlocale(LC_ALL, "en_US.utf8");
	char32_t in[] = U"zß水🍌"; // or "z\u00df\u6c34\U0001F34C"
	size_t in_sz = sizeof in / sizeof *in;

	printf("Processing %zu UTF-32 code units: [ ", in_sz);
	for(size_t n = 0; n < in_sz; ++n)
	    printf("%#x ", in[n]);
	puts("]");

	char out[MB_CUR_MAX * in_sz];
	char *p = out;
	for(size_t n = 0; n < in_sz; ++n)
	{
		size_t rc = c32rtomb(p, in[n], &state);
        if(rc == (size_t)-1)
	        break;
        p += rc;
	}

	size_t out_sz = p - out;
	printf("into %zu UTF-8 code units: [ ", out_sz);
	for(size_t x = 0; x < out_sz; ++x)
		printf("%#x ", +(unsigned char)out[x]);
    puts("]");


    printf("UTF-32 string representation: ");
    for (size_t n = 0; n < in_sz; ++n)
	    printf("%C ", in[n]);
    printf("\n");

    return 0;
}
/*
Processing 5 UTF-32 code units: [ 0x7a 0xdf 0x6c34 0x1f34c 0 ]
into 11 UTF-8 code units: [ 0x7a 0xc3 0x9f 0xe6 0xb0 0xb4 0xf0 0x9f 0x8d 0x8c 0 ]
UTF-32 string representation: z ß 水 🍌
*/
