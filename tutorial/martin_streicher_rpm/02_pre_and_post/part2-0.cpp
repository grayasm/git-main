#include <unistd.h>
#include <string.h>
#include <iostream>


using namespace std;
int main(int argc, char** argv)
{
	char data[20];
	while(true)
	{
		cout << "exit ? (stop) " ;
		cin >> data;
		if (strcmp(data, "stop") == 0)
		{
			cout << "closing ..." << endl;
			return 0;
		}
		sleep(2); //idle
	}

	return -1;
}
