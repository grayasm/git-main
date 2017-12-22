/* Header     : none (core functionality)
   Signature  : char16_t
   Description: N3337, pag 25, 2.14.3 Character literals
                A character literal that begins with the letter u, such as u'y'
                is a character literal of type char16_t.
                The value of a char16_t literal containing a single c-char is
                equal to its ISO 10646 code point value, provided that the
                code point is representable with a single 16-bit code unit.
                (That is, provided it is a basic multi-lingual plane code point)
                If the value is not representable within 16 bits, the program
                is ill-formed. A char16_t literal containing multiple c-chars
                is ill-formed.
 */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <uchar.h>


mbstate_t state;
int main()
{
	setlocale(LC_ALL, "en_US.utf8");
	char16_t in[] = u"zß水🍌"; // or "z\u00df\u6c34\U0001F34C"
	size_t in_sz = sizeof in / sizeof *in;

	printf("Processing %zu UTF-16 code units: [ ", in_sz);
	for (size_t n = 0; n < in_sz; ++n)
		printf("%#x ", in[n]);
	puts("]");

	char out[MB_CUR_MAX * in_sz];
	char *p = out;
	for (size_t n = 0; n < in_sz; ++n)
	{
		size_t rc = c16rtomb(p, in[n], &state);
		if (rc == (size_t)-1)
			break;
		p += rc;
	}

	size_t out_sz = p - out;
	printf("into %zu UTF-8 code units: [ ", out_sz);
	for (size_t n = 0; n < out_sz; ++n)
		printf("%#x ", +(unsigned char)out[n]);
	puts("]");


	printf("UTF-16 string representation: ");
	for (size_t n = 0; n < in_sz; ++n)
		printf("%C ", in[n]); // 16-bit UTF-16 code unit (unichar)
	printf("\n");

	return 0;
}
/*
Processing 6 UTF-16 code units: [ 0x7a 0xdf 0x6c34 0xd83c 0xdf4c 0 ]
into 6 UTF-8 code units: [ 0x7a 0xc3 0x9f 0xe6 0xb0 0xb4 ]
UTF-16 string representation: z ß 水
*/
