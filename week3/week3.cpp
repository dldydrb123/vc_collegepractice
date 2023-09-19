#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

int main(void)
{
	string s2;

	while (1)
	{
		int key;
		
		key = _getch();

		s2 += to_string(key);
		cout << s2 << "\n";
		
	}

	return 0;
}