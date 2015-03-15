/*
 * Setting only one alarm request at a time.
 * It is not possible to have another alarm
 * earlier to remind you of something else.
 * The program is doing something synchronously that
 * you probably would like to be ASYNCHRONOUSLY.
 */


#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
	int seconds;
	char line[128];
	char message[64];

	while(1)
	{
		printf("Alarm> ");
		if(fgets(line, sizeof(line), stdin) == NULL) exit(0);
		if(strlen(line) <= 1) continue;

		/*
		 * Parse input line into seconds (%d) and a message
		 * (%64[^\n]), consisting of up to 64 characters
		 * separated from the seconds by whitespace
		 */

		if(sscanf(line, "%d %64[^\n]", &seconds, message) < 2)
			fprintf(stderr, "Bad command\n");
		else
		{
			sleep(seconds);
			printf("(%d) %s\n", seconds, message);
		}
	}

	return 0;
};
