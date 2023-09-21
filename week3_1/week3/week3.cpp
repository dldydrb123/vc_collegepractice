#include <iostream>
#include <conio.h>
#include <string>
#include <chrono>

using namespace std;

int main(void)
{
    int input, code;
    string s2;
    chrono::steady_clock::time_point start_time;
    chrono::steady_clock::time_point current_time;
    start_time = chrono::steady_clock::now();
    while (1)
    {
        
        // 현재 시간 기록
        if (s2.empty()==0) {
            current_time = chrono::steady_clock::now();
        }

        input = _getch();
        if (input == 224)
        {
            input = _getch();
        }
        s2 += to_string(input);
        cout << s2 << endl;
        if (input == 27)
        {
            break;
        }
        if (s2 == "807797")
        {
            cout << "아도겐! =o" << "\n";
            s2.clear();
            start_time = current_time;  // 시작 시간 갱신
        }

        if (s2 == "777777")
        {
            cout << "전진! =o" << "\n";
            s2.clear();
            start_time = current_time;  // 시작 시간 갱신
        }

        if (s2 == "777775")
        {
            cout << "발사 =o" << "\n";
            s2.clear();
            start_time = current_time;  // 시작 시간 갱신
        }
        // 0.7초(700ms) 이상 경과하면 초기화
        if (chrono::duration_cast<chrono::milliseconds>(current_time - start_time).count() >= 2000)
        {
            s2.clear();

            start_time = current_time;  // 시작 시간 갱신
        }
 
    }

    return 0;
}