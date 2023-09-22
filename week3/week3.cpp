#include <iostream>
#include <conio.h>
#include <string>
#include <chrono>
#include <Windows.h>

using namespace std;

int main(void)
{
    int input, code;
    string s2;
    while (1)
    {

        input = _getch();
        if (input == 224)
        {
            input = _getch();
        }
        s2 += to_string(input);

        if (input == 27)
        {
            break;
        }
        if (s2 == "807797")
        {
            cout << "아도겐! =o" << "\n";
            s2.clear();
        }

        if (s2 == "777777")
        {
            cout << "전진! =o" << "\n";
            s2.clear();
        }

        if (s2 == "777775")
        {
            cout << "발사 =o" << "\n";
            s2.clear();
        }
        // 0.7초(700ms) 이상 경과하면 초기화, 문제를 잘못 인지하여 짜증난다 깃 오류로 그만큼 또 시간을 써버렸다, 배웠으니까 오히려 좋다는 마음으로해야지
        Sleep(300);
    }

    return 0;
}
