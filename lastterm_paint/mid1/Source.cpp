#include "Source.h"

void DrawRect(HWND hWnd, HDC hdc, int left, int top, int right, int bottom)
{
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // 핑크 브러시 생성
    RECT rect = { left, top, right, bottom }; // RECT 타입의 변수를 생성하고 값을 설정
    FillRect(hdc, &rect, hBrush); // 핑크색 사각형 그리기
    DeleteObject(hBrush); // 브러시 삭제
}

void DrawCircle(HWND hWnd, HDC hdc, int radius, POINT center)
{
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
    Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);
    SelectObject(hdc, hBrush);

    DeleteObject(hBrush); // 브러시 삭제
}

void DrawBonobono(HWND hwnd, HDC hdc, int blink)
{
    RECT rc;
    // 배경을 그립니다.
    if (blink)
    {
        HBRUSH bBrush = CreateSolidBrush(RGB(0, 0, 0)); // 배경색 지정
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 240, 200)); // 배경색 지정
        FillRect(hdc, &rc, hBrush);
        DeleteObject(hBrush);
        HBRUSH hEllipseBrush = CreateSolidBrush(RGB(127, 200, 255));
        HBRUSH ddllipseBrush = CreateSolidBrush(RGB(255, 150, 255));//분홍색
        HBRUSH xxllipseBrush = CreateSolidBrush(RGB(255, 255, 255));//하얀색
        SelectObject(hdc, hEllipseBrush); // 파랑색 브러시 선택
        Ellipse(hdc, 250, 100, 550, 400);// 얼굴
        SelectObject(hdc, ddllipseBrush); // 파랑색 브러시 선택
        Ellipse(hdc, 377, 244, 424, 322);
        SelectObject(hdc, xxllipseBrush); // 흰색 브러시 선택
        Ellipse(hdc, 353, 245, 400, 292); //왼쪽 입가
        Ellipse(hdc, 400, 245, 447, 292);
        SelectObject(hdc, bBrush);
        Ellipse(hdc, 275, 225, 284, 242); //눈
        Ellipse(hdc, 525, 225, 534, 242);
        SelectObject(hdc, xxllipseBrush);
        Ellipse(hdc, 278, 228, 281, 236); //왼쪽 안눈
        Ellipse(hdc, 528, 227, 531, 236); //오른쪽 안 눈
        SelectObject(hdc, bBrush);
        Ellipse(hdc, 383, 234, 417, 272); //코
        MoveToEx(hdc, 340, 285, NULL);
        LineTo(hdc, 368, 272);
        MoveToEx(hdc, 340, 255, NULL);
        LineTo(hdc, 380, 262);
        MoveToEx(hdc, 430, 275, NULL);
        LineTo(hdc, 468, 282); //오른쪽아래 수염
        MoveToEx(hdc, 470, 255, NULL);
        LineTo(hdc, 420, 272);
    }
    else
    {
        HDC hdc = GetDC(hwnd);
        RECT rect;
        GetClientRect(hwnd, &rect);
        HBRUSH bBrush = CreateSolidBrush(RGB(0, 0, 0)); // 배경색 지정
        HBRUSH hEllipseBrush = CreateSolidBrush(RGB(127, 200, 255));
        HBRUSH ddllipseBrush = CreateSolidBrush(RGB(255, 150, 255));//분홍색
        HBRUSH xxllipseBrush = CreateSolidBrush(RGB(255, 255, 255));//하얀색
        SelectObject(hdc, hEllipseBrush); // 파랑색 브러시 선택
        Ellipse(hdc, 250, 100, 550, 400);// 얼굴
        SelectObject(hdc, ddllipseBrush); // 파랑색 브러시 선택
        Ellipse(hdc, 377, 244, 424, 322);
        SelectObject(hdc, xxllipseBrush); // 흰색 브러시 선택
        Ellipse(hdc, 353, 245, 400, 292); //왼쪽 입가
        Ellipse(hdc, 400, 245, 447, 292);
        MoveToEx(hdc, 275, 225, NULL);
        LineTo(hdc, 290, 245); //눈
        MoveToEx(hdc, 514, 245, NULL);
        LineTo(hdc, 529, 225);
        MoveToEx(hdc, 290, 245, NULL);
        LineTo(hdc, 275, 265); //눈
        MoveToEx(hdc, 514, 245, NULL);
        LineTo(hdc, 529, 265);
        SelectObject(hdc, bBrush);
        Ellipse(hdc, 383, 234, 417, 272); //코
        MoveToEx(hdc, 340, 285, NULL);
        LineTo(hdc, 368, 272);
        MoveToEx(hdc, 340, 255, NULL);
        LineTo(hdc, 380, 262);
        MoveToEx(hdc, 430, 275, NULL);
        LineTo(hdc, 468, 282); //오른쪽아래 수염
        MoveToEx(hdc, 470, 255, NULL);
        LineTo(hdc, 420, 272);

        ReleaseDC(hwnd, hdc);
    }
}

void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom)
{
    double xlength = 0, ylength = 0;

    xlength = right - left;
    ylength = bottom - top;

    HBRUSH hLeftEarColor = CreateSolidBrush(RGB(255, 200, 15));  // 노란색 귀
    SelectObject(hdc, hLeftEarColor);
    Ellipse(hdc, left, top, left + xlength / 3, top + ylength / 3);  // 왼쪽 귀의 높이를 높임
    DeleteObject(hLeftEarColor);

    //// 오른쪽 귀 (노란색)
    HBRUSH hRightEarColor = CreateSolidBrush(RGB(255, 200, 15));  // 노란색 귀
    SelectObject(hdc, hRightEarColor);
    Ellipse(hdc, left + xlength * 2 / 3, top, left + xlength, top + ylength / 3);  // 오른쪽 귀의 높이를 높임
    DeleteObject(hRightEarColor);

    //// 얼굴 그리기 (노란색)
    HBRUSH hFaceColor = CreateSolidBrush(RGB(255, 200, 15));  // 노란색 얼굴
    SelectObject(hdc, hFaceColor);
    Ellipse(hdc, left + xlength / 18, top + ylength / 13, left + xlength / 18 * 17, top + ylength);
    DeleteObject(hFaceColor);

    //// 눈썹 그리기 (가운데 정렬)
    SelectObject(hdc, GetStockObject(BLACK_PEN));

    // 왼쪽 눈 가로선 그리기
    MoveToEx(hdc, left + xlength * 7 / 27, top + ylength * 40 / 144, NULL);
    LineTo(hdc, left + xlength * 11 / 27, top + ylength * 40 / 144);
    MoveToEx(hdc, left + xlength * 10 / 18, top + ylength * 40 / 144, NULL);
    LineTo(hdc, left + xlength * 13 / 18, top + ylength * 40 / 144);

    // 왼쪽 눈 세로선 그리기
    MoveToEx(hdc, left + xlength * 7 / 27, top + ylength * 41 / 144, NULL);
    LineTo(hdc, left + xlength * 11 / 27, top + ylength * 41 / 144);
    MoveToEx(hdc, left + xlength * 10 / 18, top + ylength * 41 / 144, NULL);
    LineTo(hdc, left + xlength * 13 / 18, top + ylength * 41 / 144);

    // 왼쪽 눈 밑 부분 그리기
    MoveToEx(hdc, left + xlength * 7 / 27, top + ylength * 42 / 144, NULL);
    LineTo(hdc, left + xlength * 11 / 27, top + ylength * 42 / 144);
    MoveToEx(hdc, left + xlength * 10 / 18, top + ylength * 42 / 144, NULL);
    LineTo(hdc, left + xlength * 13 / 18, top + ylength * 42 / 144);

    // 눈 그리기 (검정색)
    SelectObject(hdc, GetStockObject(BLACK_BRUSH));

    // 왼쪽 눈
    Ellipse(hdc, left + xlength * 17 / 54, top + ylength * 27 / 72, left + xlength * 20 / 54, top + ylength * 31 / 72);

    // 오른쪽 눈
    Ellipse(hdc, left + xlength * 32 / 54, top + ylength * 27 / 72, left + xlength * 35 / 54, top + ylength * 31 / 72);



    // 입 그리기 (가운데 정렬, 흰색)
    HBRUSH hMouthColor = CreateSolidBrush(RGB(255, 255, 255));  // 흰색 입
    SelectObject(hdc, hMouthColor);
    int mouthLeft = left + xlength * 8 / 20;  // 입 왼쪽 부분
    int mouthRight = left + xlength / 2;  // 입 오른쪽 부분
    int mouthTop = top + ylength * 35 / 72;
    int mouthBottom = top + ylength * 42 / 72;
    Ellipse(hdc, mouthLeft, mouthTop, mouthRight, mouthBottom);

    mouthLeft = left + xlength / 2;  // 두 번째 원의 왼쪽 부분
    mouthRight = left + xlength * 12 / 20;  // 두 번째 원의 오른쪽 부분
    Ellipse(hdc, mouthLeft, mouthTop, mouthRight, mouthBottom);

    DeleteObject(hMouthColor);
}

void DrawCube(HWND hWnd, HDC hdc, int left, int top, int right, int bottom)
{
    double xlength = 0, ylength = 0;

    xlength = right - left;
    ylength = bottom - top;

    MoveToEx(hdc, left + xlength * 5 / 16, top, NULL); //1 가로
    LineTo(hdc, left + xlength, top);

    MoveToEx(hdc, left + xlength * 5 / 16, top, NULL);
    LineTo(hdc, left, top + ylength * 9 / 36);

    MoveToEx(hdc, left + xlength, top, NULL);
    LineTo(hdc, left + xlength * 11 / 16, top + ylength * 9 / 36);

    MoveToEx(hdc, left, top + ylength * 9 / 36, NULL);
    LineTo(hdc, left + xlength * 11 / 16, top + ylength * 9 / 36); //2

    MoveToEx(hdc, left, top + ylength * 9 / 36, NULL);
    LineTo(hdc, left, top + ylength);

    MoveToEx(hdc, left + xlength * 11 / 16, top + ylength * 9 / 36, NULL);
    LineTo(hdc, left + xlength * 11 / 16, top + ylength);

    MoveToEx(hdc, left, top + ylength, NULL);
    LineTo(hdc, left + xlength * 11 / 16, top + ylength); //3

    MoveToEx(hdc, left + xlength, top, NULL);
    LineTo(hdc, left + xlength, top + ylength * 11 / 16); 

    MoveToEx(hdc, left + xlength * 11 / 16, top + ylength, NULL);
    LineTo(hdc, left + xlength, top + ylength * 11 / 16);
}