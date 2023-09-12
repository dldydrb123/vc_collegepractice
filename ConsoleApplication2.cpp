#include <iostream>
#include <stdio.h>
#include <conio.h>

using namespace std;

int main() {
	
	int code;
	int code2;
	cout << "C++202107054 이용규\n";
	while (1)
	{
		
		cout << "command>";
		while (1)
		{
			code2 = _getche();
			if(code2 == 27)
			{
				return 0;
			}
			if(code2 == 13)
			{
				cout << "\n";
				break;
			}
			code = code2;
		}
		
		switch (code)
		{
		case 'q':
			printf("qwer 화이팅\n");
			break;
		case 'w':
			cout << "과제 너무 좋다\n";
			break;
		case 'e':
			cout << "담주부턴 과제량 3배다\n";
			break;
		case 'r':
			cout << "행복합니다.\n";
			break;
		default:
			cout << "error\n";

		}
	}
}