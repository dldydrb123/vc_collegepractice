#include <windows.h>
#include <cmath>

POINT starCenter = { 0 }; // 별의 중심
BOOL isStarMode = FALSE;
double starSize = 50.0; // 초기 별의 크기
BOOL isDragging = FALSE;
POINT dragStart = { 0 }; // 드래그 시작 지점

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == 4) // 별 모드 버튼이 클릭된 경우
        {
            isStarMode = TRUE;
        }
        else
        {
            isStarMode = FALSE;
            // 별 모드가 종료되면 다시 그리기
            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
        }
        break;

    case WM_LBUTTONDOWN:
        if (isStarMode)
        {
            starCenter.x = LOWORD(lParam);
            starCenter.y = HIWORD(lParam);
            isDragging = TRUE;
            dragStart = starCenter;
        }
        break;

    case WM_LBUTTONUP:
        if (isStarMode && isDragging)
        {
            isDragging = FALSE;
            int currentX = LOWORD(lParam);
            int currentY = HIWORD(lParam);
            int distance = static_cast<int>(sqrt(pow(currentX - dragStart.x, 2) + pow(currentY - dragStart.y, 2)));
            starSize = distance;
            // 드래그 후에도 별을 그리기
            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
        }
        break;

    case WM_MOUSEMOVE:
        if (isDragging)
        {
            // 드래그 중에는 별의 크기 조절
            int currentX = LOWORD(lParam);
            int currentY = HIWORD(lParam);
            int distance = static_cast<int>(sqrt(pow(currentX - dragStart.x, 2) + pow(currentY - dragStart.y, 2)));
            starSize = distance;
            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
        }
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        if (isStarMode)
        {
            // 별 그리기
            double angle = 0;
            POINT starPoints[10];

            for (int i = 0; i < 10; i++)
            {
                int offset = (i % 2 == 0) ? static_cast<int>(starSize) : static_cast<int>(starSize / 2.0);
                starPoints[i].x = starCenter.x + static_cast<int>(offset * cos(angle));
                starPoints[i].y = starCenter.y + static_cast<int>(offset * sin(angle));
                angle += 2 * 3.14159265359 / 10;
            }

            Polygon(hdc, starPoints, 10);
        }

        EndPaint(hwnd, &ps);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"DrawingWindowClass";

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        L"DrawingWindowClass",
        L"Drawing Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL,
        NULL,
        hInstance,
        NULL);

    CreateWindow(TEXT("BUTTON"), TEXT("Star Mode"), WS_VISIBLE | WS_CHILD, 10, 10, 150, 30, hwnd, (HMENU)4, NULL, NULL);

    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
