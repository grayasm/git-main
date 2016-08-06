/*
 * int1 example
 *
 *      X/Open Message Catalog Handling
 *      http://www.gnu.org/software/libc/manual/html_node/Message-catalogs-a-la-X_002fOpen.html
 *
 *      Cap 10.1 / pg 241
 *      "The three functions catopen, catgets and catclose provide a simple
 *      mechanism for retrieving numbered strings from a plain text file."
 *
 *      see int1.txt for messages/text file format
 *      see Makefile int1 target for how to compile int1.txt into catalog format
 *      see below link for catopen, catgets, catclose
 *      http://www.gnu.org/software/libc/manual/html_node/The-catgets-Functions.html
 *
 */

#include <nl_types.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	printf("\n\tOpen catalog: %s.msg", argv[0]);
	char catpath[250];
	strcpy(catpath, argv[0]);
	strcat(catpath, ".msg");


	nl_catd catd = catopen(catpath, 0);
	if(catd == (nl_catd)-1)
	{
		printf("\nCannot open catalog\n");
		return 1;
	}

	// normaly in all sets will be the same language (here is an exception
	// to test displaying from different languages)

	for(int set=1; set <= 3; ++set)
	{
		for(int id=1; id <= 3; ++id)
		{
			const char* msg = catgets(catd, set, id, "#unknown translation");
			printf("\n\tset:%d id:%d text=%s", set, id, msg);
		}
	}

	int ret = catclose(catd);
	printf("\n\tCatalog closed %s\n\n", (ret == 0 ? "OK" : "with error!"));
	return 0;
}
