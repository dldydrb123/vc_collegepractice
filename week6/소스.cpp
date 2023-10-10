#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>
POINT point = { 50, 50 }; // 초기 점 위치
POINT startPoint = { 0 }; // 진짜 씨발 내가 논리적으로 생각해낸걸 chatgpt가 거의 유사하게 짰는데 문법적으로 이상한 부분을 내가 고치지 못해서 10시부터 아침 6시까지 이지@랄을 했다는게 믿기지가 않다
POINT endPoint = { 0 };
POINT startPoint1 = { 0 };
POINT endPoint1 = { 0 };
int isMouseLButtonPressed = 0;
int RightButtonActived = 0;
RECT dragRect;

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    RECT rc2;
    POINT it, rb;
    GetClientRect(hwnd, &rc2);
    it.x = rc2.left; it.y = rc2.top-100; rb.x = rc2.right; rb.y = rc2.bottom;
    ClientToScreen(hwnd, &it); 
    ClientToScreen(hwnd, &rb);
    rc2.left = it.x; rc2.top = it.y; rc2.right = rb.x; rc2.bottom = rb.y;
    ClipCursor(&rc2);

    switch (uMsg)
    {
    case WM_LBUTTONDOWN:
    {
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        isMouseLButtonPressed = 1;
    }
    break;

    case WM_RBUTTONDOWN:
    {
        // 마우스 오른쪽 버튼 클릭 이벤트 처리
        POINTS pt = MAKEPOINTS(lParam);
        POINT clientPoint = { pt.x, pt.y };
        ScreenToClient(hwnd, &clientPoint);

        // 클라이언트 좌표를 기반으로 어떤 객체를 클릭했는지 확인하는 코드를 추가합니다.
        // 이 예제에서는 현재 하나의 사각형만 처리하도록 가정합니다.

        // 선택된 사각형을 드래그할 때 필요한 정보를 저장합니다.
        if (PtInRect(&dragRect, clientPoint)) {
            RightButtonActived = 1;
            startPoint1 = endPoint1 = clientPoint; // 시작 및 끝 포인트를 현재 마우스 위치로 설정합니다.
        }
    }
    break;

    case WM_MOUSEMOVE:
    {
        // 마우스 이동 중
        if (isMouseLButtonPressed)
        {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);

            // WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
            InvalidateRect(hwnd, NULL, TRUE);
        }
        if (RightButtonActived)
        {
            endPoint1.x = LOWORD(lParam);
            endPoint1.y = HIWORD(lParam);

            // 현재 마우스 위치와 시작 클릭 위치 사이의 거리를 계산합니다.
            int deltaX = endPoint1.x - startPoint1.x;
            int deltaY = endPoint1.y - startPoint1.y;

            // 선택된 사각형을 이동합니다.
            OffsetRect(&dragRect, deltaX, deltaY);

            startPoint1 = endPoint1; // 현재 마우스 위치를 새로운 시작점으로 설정합니다.

            // 화면 다시 그리기
            InvalidateRect(hwnd, NULL, TRUE);
        }
    }
    break;

    case WM_LBUTTONUP:
    {
        endPoint.x = LOWORD(lParam);
        endPoint.y = HIWORD(lParam);

        isMouseLButtonPressed = 0;
    }
    break;

    case WM_RBUTTONUP:
    {
        RightButtonActived = 0;
    }
    break;
    
    case WM_KEYDOWN:
    {
        // 방향키 입력 처리
        int step = 5; // 이동 거리
        if (wParam == VK_LEFT) {
            point.x -= step; // 왼쪽으로 이동
        }
        else if (wParam == VK_RIGHT) {
            point.x += step; // 오른쪽으로 이동
        }
        else if (wParam == VK_UP) {
            point.y -= step; // 위로 이동
        }
        else if (wParam == VK_DOWN) {
            point.y += step; // 아래로 이동
        }

        // WM_PAINT 메시지를 유발하여 점을 다시 그립니다.
        InvalidateRect(hwnd, NULL, TRUE);
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = GetDC(hwnd);
        // 점 그리기
        HBRUSH hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255)); // 흰색 브러시 생성
        FillRect(hdc, &ps.rcPaint, hWhiteBrush); // 클라이언트 영역을 흰색으로 채움
        DeleteObject(hWhiteBrush); // 브러시 삭제

        Ellipse(hdc, point.x - 5, point.y - 5, point.x + 5, point.y + 5);

        EndPaint(hwnd, &ps);

        

        if (isMouseLButtonPressed)
        {
            RECT rect;
            GetClientRect(hwnd, &rect);
            FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));

            // 드래그 중인 상자 그리기    
            dragRect.left = min(startPoint.x, endPoint.x);
            dragRect.top = min(startPoint.y, endPoint.y);
            dragRect.right = max(startPoint.x, endPoint.x);
            dragRect.bottom = max(startPoint.y, endPoint.y);

            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // 핑크 브러시 생성
            FillRect(hdc, &dragRect, hBrush); // 핑크색 상자 그리기
            DeleteObject(hBrush);
        }

        // 우클릭으로 드래그하는 사각형 그리기
        if (RightButtonActived)
        {
            RECT rect;
            GetClientRect(hwnd, &rect);
            FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));

            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // 핑크 브러시 생성
            FillRect(hdc, &dragRect, hBrush); // 핑크색 상자 그리기
            DeleteObject(hBrush);
        }

        ReleaseDC(hwnd, hdc);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return S_OK;
}

#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
    /* 윈도우 클래스 선언.*/
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));   // 모두 0으로 초기화.

    // 윈도우 클래스 값 설정
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("Computer Software");
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;

    // 윈도우 클래스 등록.
    if (RegisterClass(&wc) == 0)
    {
        MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
        exit(-1);   //예외
    }

    // Window viewport 영역 조정
    RECT rect = { 150, 100, 800, 600 };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    // 윈도우 생성
    HWND hwnd = CreateWindow(
        wc.lpszClassName,
        TEXT("202107054 이용규 5주차 과제"),
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, // 크기 조정 및 버튼 비활성화
        0, 0,
        800, 600, // 고정된 창 크기
        NULL, NULL,
        hInstance,
        NULL
    );

    // 오류 검사.
    if (hwnd == NULL)
    {
        MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
        exit(-1);
    }

    // 창 보이기.
    ShowWindow(hwnd, SW_SHOW); // 창 띄우고
    UpdateWindow(hwnd); // 업데이트해야 보임. 한 쌍으로 쓴다고 보면 됨.

    // 메시지 처리 루프.
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        // 메시지 처리.
        if (GetMessage(&msg, NULL, 0, 0))
        {
            // 메시지 해석해줘.
            TranslateMessage(&msg);
            // 메시지를 처리해야할 곳에 전달해줘.
            DispatchMessage(&msg);
        }
    }

    //종료 메시지 보내기 
    return (int)msg.wParam;
}