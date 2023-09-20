#include <iostream>
#include <conio.h>
#include <string>
#include <chrono>

using namespace std;

int main(void)
{
    int input;
    string s2;
    chrono::steady_clock::time_point start_time;
    chrono::steady_clock::time_point current_time;

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
        // 현재 시간 기록
        current_time = chrono::steady_clock::now();

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
        // 0.7초(700ms) 이상 경과하면 초기화
        if (chrono::duration_cast<chrono::milliseconds>(current_time - start_time).count() >= 700)
        {
            s2.clear();

            start_time = current_time;  // 시작 시간 갱신
        }
 
    }

    return 0;
}