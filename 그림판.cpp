#include <windows.h>

POINT startPoint = { 0 };
POINT endPoint = { 0 };
BOOL isDrawingEnabled = FALSE;
BOOL isRectangleMode = TRUE;
BOOL isLineMode = FALSE;
BOOL isFirstClick = TRUE;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) // 사각형 버튼이 클릭된 경우
        {
            isRectangleMode = TRUE;
            isLineMode = FALSE;
            isFirstClick = TRUE;
        }
        else if (LOWORD(wParam) == 2) // 삼각형 버튼이 클릭된 경우
        {
            isRectangleMode = FALSE;
            isLineMode = FALSE;
            isFirstClick = TRUE;
        }
        else if (LOWORD(wParam) == 3) // 직선 버튼이 클릭된 경우
        {
            isRectangleMode = FALSE;
            isLineMode = TRUE;
            isFirstClick = TRUE;
        }
        break;

    case WM_LBUTTONDOWN:
        if (isFirstClick)
        {
            startPoint.x = LOWORD(lParam);
            startPoint.y = HIWORD(lParam);
            isFirstClick = FALSE;
        }
        break;

    case WM_LBUTTONUP:
        if (!isFirstClick)
        {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            isDrawingEnabled = TRUE;
            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
            isFirstClick = TRUE;
        }
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        if (isDrawingEnabled)
        {
            if (isRectangleMode)
            {
                Rectangle(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
            }
            else if (isLineMode)
            {
                MoveToEx(hdc, startPoint.x, startPoint.y, NULL);
                LineTo(hdc, endPoint.x, endPoint.y);
            }
            else
            {
                POINT points[3] = {
                    {startPoint.x, endPoint.y},
                    {endPoint.x, endPoint.y},
                    {(startPoint.x + endPoint.x) / 2, startPoint.y} };
                Polygon(hdc, points, 3);
            }
            isDrawingEnabled = FALSE;
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
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
        NULL,
        NULL,
        hInstance,
        NULL);

    CreateWindow(TEXT("BUTTON"), TEXT("Rectangle Mode"), WS_VISIBLE | WS_CHILD, 10, 10, 150, 30, hwnd, (HMENU)1, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Triangle Mode"), WS_VISIBLE | WS_CHILD, 170, 10, 150, 30, hwnd, (HMENU)2, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Line Mode"), WS_VISIBLE | WS_CHILD, 330, 10, 150, 30, hwnd, (HMENU)3, NULL, NULL);

    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
