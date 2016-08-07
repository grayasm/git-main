#include <unistd.h>
#include <string.h>
#include <iostream>


using namespace std;
int main(int argc, char** argv)
{
	char data[20];
	while(true)
	{
		cout << "v.2-1" << endl;
		cout << "exit ? (stop,quit,kill) " ;
		cin >> data;
		if (strcmp(data, "stop") == 0 ||
		    strcmp(data, "quit") == 0 ||
		    strcmp(data, "kill") == 0)
		{
			cout << "closing ..." << endl;
			return 0;
		}
		sleep(2); //idle
	}

	return -1;
}
