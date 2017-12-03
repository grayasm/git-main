#include <stdio.h>

main()
{
	char *msg = "a message for you"; // 17 + 0
	msg[14] = 'm';
	msg[15] = 'e';
	msg[16] = '\0';

	printf("%s\n", msg);
}
