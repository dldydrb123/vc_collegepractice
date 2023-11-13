#include "YuhanCG.h"

HBRUSH hFaceBrush;  // ���� �׸��µ� ����� �귯��
HBRUSH hEyeBrush;   // ���� �׸��µ� ����� �귯��
HBRUSH hEarBrush;   // �͸� �׸��µ� ����� �귯��
HBRUSH hMouthBrush; // ���� �׸��µ� ����� �귯��

static HCURSOR hCrossCursor = LoadCursor(NULL, IDC_CROSS);
static HCURSOR hArrowCursor = LoadCursor(NULL, IDC_ARROW);

POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT startPoint1 = { 0 };
POINT endPoint1 = { 0 };
BOOL isDrawingEnabled = FALSE;
BOOL isRectangleMode = TRUE;
BOOL isCircleMode = FALSE;
BOOL isBonobonoMode = FALSE;
BOOL isRyanMode = FALSE;
BOOL isCubeMode = FALSE;
BOOL CircleScale = FALSE;
BOOL isFirstClick = TRUE;
RECT dragRect;
int button = 0;
int isMouseLButtonPressed = 0;
int isMouseRButtonPressed = 0;
int blink = 1;
double xlength = 0, ylength = 0, left = 0, top = 0, right = 0, bottom = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_SETCURSOR:
    {
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hwnd, &pt);

        RECT rc;
        rc.left = 16;
        rc.top = 90;
        rc.right = 800 - 32;
        rc.bottom = 480 - 56;

        if (pt.x > rc.left && pt.x < rc.right && pt.y > rc.top && pt.y < rc.bottom)
        {
            SetCursor(hCrossCursor);
            return TRUE;
        }
        else
        {
            SetCursor(hArrowCursor);
            return TRUE;
        }
    }
    break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) // �簢�� ��ư�� Ŭ���� ���
        {
            isRectangleMode = TRUE;
            isCircleMode = FALSE;
            isBonobonoMode = FALSE;
            isRyanMode = FALSE;
            isCubeMode = FALSE;
            isFirstClick = TRUE;
            SetFocus(hwnd);
        }
        else if (LOWORD(wParam) == 2) // �� ��ư�� Ŭ���� ���
        {
            isRectangleMode = FALSE;
            isCircleMode = TRUE;
            isBonobonoMode = FALSE;
            isRyanMode = FALSE;
            isCubeMode = FALSE;
            isFirstClick = TRUE;
            SetFocus(hwnd);
        }
        else if (LOWORD(wParam) == 3) {
            isRectangleMode = FALSE;
            isCircleMode = FALSE;
            isBonobonoMode = TRUE; // "���뺸�� ���" ��ư Ŭ�� �� �ش� ��带 Ȱ��ȭ
            isRyanMode = FALSE;
            isCubeMode = FALSE;
            isFirstClick = TRUE;
            SetFocus(hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == 4) // Ryan ��ư�� Ŭ���� ���
        {
            isRectangleMode = FALSE;
            isCircleMode = FALSE;
            isBonobonoMode = FALSE;
            isRyanMode = TRUE;
            isCubeMode = FALSE;
            isFirstClick = TRUE;
            SetFocus(hwnd);
        }
        else if (LOWORD(wParam) == 5) // Cube ��ư�� Ŭ���� ���
        {
            isRectangleMode = FALSE;
            isCircleMode = FALSE;
            isBonobonoMode = FALSE;
            isRyanMode = FALSE;
            isCubeMode = TRUE;
            isFirstClick = TRUE;
            SetFocus(hwnd);
        }

        break;

    case WM_RBUTTONDOWN:
    {
        if (isRectangleMode)
        {
            // ���콺 ������ ��ư Ŭ�� �̺�Ʈ ó��
            POINTS pt = MAKEPOINTS(lParam);
            POINT clientPoint = { pt.x, pt.y };
            ScreenToClient(hwnd, &clientPoint);
            button = 1;

            // Ŭ���̾�Ʈ ��ǥ�� ������� � ��ü�� Ŭ���ߴ��� Ȯ���ϴ� �ڵ带 �߰��մϴ�.
            // �� ���������� ���� �ϳ��� �簢���� ó���ϵ��� �����մϴ�.

            // ���õ� �簢���� �巡���� �� �ʿ��� ������ �����մϴ�.
            isMouseRButtonPressed = 1;
            if (PtInRect(&dragRect, clientPoint)) {
                isDrawingEnabled = TRUE;
                startPoint1 = endPoint1 = clientPoint; // ���� �� �� ����Ʈ�� ���� ���콺 ��ġ�� �����մϴ�.
            }
            startPoint1 = endPoint1 = clientPoint; // ���� �� �� ����Ʈ�� ���� ���콺 ��ġ�� �����մϴ�.
        }
        if (isCircleMode)
        {
            // ���콺 ������ ��ư Ŭ�� �̺�Ʈ ó��
            POINTS pt = MAKEPOINTS(lParam);
            POINT clientPoint = { pt.x, pt.y };
            ScreenToClient(hwnd, &clientPoint);
            CircleScale = 1;
            isDrawingEnabled = TRUE;
            // Ŭ���̾�Ʈ ��ǥ�� ������� � ��ü�� Ŭ���ߴ��� Ȯ���ϴ� �ڵ带 �߰��մϴ�.
            // �� ���������� ���� �ϳ��� �簢���� ó���ϵ��� �����մϴ�.

            // ���õ� �簢���� �巡���� �� �ʿ��� ������ �����մϴ�.
            isMouseRButtonPressed = 1;
            startPoint1 = endPoint1 = clientPoint; // ���� �� �� ����Ʈ�� ���� ���콺 ��ġ�� �����մϴ�.
        }
    }
    break;
    case WM_LBUTTONDOWN:
        if (isFirstClick)
        {
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);

            RECT rc;
            rc.left = 16;
            rc.top = 90;
            rc.right = 800 - 32;
            rc.bottom = 480 - 56;
            button = 0;
            if (pt.x > rc.left && pt.x < rc.right && pt.y > rc.top && pt.y < rc.bottom)
            {
                startPoint.x = LOWORD(lParam);
                startPoint.y = HIWORD(lParam);
                isFirstClick = FALSE;
                isMouseLButtonPressed = 1;
            }
        }
        break;

    case WM_LBUTTONUP:
        if (!isFirstClick)
        {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            isDrawingEnabled = TRUE;
            isMouseLButtonPressed = 0;
            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
            isFirstClick = TRUE;
        }
        break;
    case WM_RBUTTONUP:
    {
        isMouseRButtonPressed = 0;
        isDrawingEnabled = TRUE;
        CircleScale = 0;
    }
    break;
    case WM_MOUSEMOVE:
    {
        // ���콺 �̵� ��
        if (isMouseLButtonPressed)
        {
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);

            RECT rc;
            rc.left = 16;
            rc.top = 90;
            rc.right = 800 - 24;
            rc.bottom = 480 - 56;
            if (pt.x > rc.left && pt.x < rc.right && pt.y > rc.top && pt.y < rc.bottom)
            {
                endPoint.x = LOWORD(lParam);
                endPoint.y = HIWORD(lParam);
            }
            // WM_PAINT �޽����� �����Ͽ� �׸� ȭ�鿡 �׸��ϴ�.
            InvalidateRect(hwnd, NULL, TRUE);
        }
        if (isMouseRButtonPressed)
        {
            endPoint1.x = LOWORD(lParam);
            endPoint1.y = HIWORD(lParam);

            // ���� ���콺 ��ġ�� ���� Ŭ�� ��ġ ������ �Ÿ��� ����մϴ�.
            int deltaX = endPoint1.x - startPoint1.x;
            int deltaY = endPoint1.y - startPoint1.y;

            // ���õ� �簢���� �̵��մϴ�.
            OffsetRect(&dragRect, deltaX, deltaY);
            button = 1;
            startPoint1 = endPoint1; // ���� ���콺 ��ġ�� ���ο� ���������� �����մϴ�.

            InvalidateRect(hwnd, NULL, TRUE);
            // ȭ�� �ٽ� �׸���

        }
    }
    case WM_KEYDOWN:
        if (wParam == VK_SPACE) {
            blink = 0;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;

    case WM_KEYUP:
        if (wParam == VK_SPACE) {
            blink = 1;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rc;

        rc.left = 16;
        rc.top = 90;
        rc.right = 800 - 24;
        rc.bottom = 480 - 56;

        HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(hdc, &rc, whiteBrush);
        DeleteObject(whiteBrush);

        GetClientRect(hwnd, &rc);

        if (isBonobonoMode) {
            // ����� �׸��ϴ�.
            DrawBonobono(hwnd, hdc, blink);
        }
        // �׸��⸦ ���� ��ǥ ���
        int left1 = 16;
        int top1 = 90;
        int right1 = rc.right - 16;
        int bottom1 = rc.bottom - 16;

        // �е��� ������ 8px�� �簢�� �׵θ� �׸���
        RECT rect1 = { left1, top1, right1, bottom1 };
        FrameRect(hdc, &rect1, (HBRUSH)GetStockObject(BLACK_BRUSH));

        int left2 = 8;
        int top2 = 8;
        int right2 = rc.right - 8;
        int bottom2 = rc.bottom - 8;

        // �е��� ������ 8px�� �簢�� �׵θ� �׸���
        RECT rect2 = { left2, top2, right2, bottom2 };
        FrameRect(hdc, &rect2, (HBRUSH)GetStockObject(BLACK_BRUSH));

        if (isRyanMode)
        {
            RECT rect;
            GetClientRect(hwnd, &rect);

            // �巡�� ���� ���� �׸���
            
            left = min(startPoint.x, endPoint.x);
            top = min(startPoint.y, endPoint.y);
            right = max(startPoint.x, endPoint.x);
            bottom = max(startPoint.y, endPoint.y);

            DrawRyan(hwnd, hdc, left, top, right, bottom);
        }
        else if (isRectangleMode && (button == 1))
        {
            RECT rect;
            GetClientRect(hwnd, &rect);

            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // ��ũ �귯�� ����
            FillRect(hdc, &dragRect, hBrush); // ��ũ�� ���� �׸���
            DeleteObject(hBrush);
        }

        ReleaseDC(hwnd, hdc);
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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    const wchar_t WINDOW_NAME[] = L"Sample Window";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(RGB(255, 240, 200)); // Background color as (255, 240, 200)
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
    LPCTSTR cursor = IDC_HAND;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,                          // Optional window styles.
        CLASS_NAME,                 // Window class
        WINDOW_NAME,                // Window text
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // Window style without sizing options

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 810, 480,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }
    int buttonWidth = 140;
    int buttonHeight = 64;
    int buttonSpacing = 12;
    int leftMargin = 24;

    // Create a box with 8-pixel margin and padding
    CreateWindow(TEXT("BUTTON"), TEXT("Box Mode"), WS_VISIBLE | WS_CHILD, leftMargin - 8, 16, buttonWidth, buttonHeight, hwnd, (HMENU)1, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Circle Mode"), WS_VISIBLE | WS_CHILD, leftMargin - 4 + buttonWidth + buttonSpacing + 1, 16, buttonWidth, buttonHeight, hwnd, (HMENU)2, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Bonobono Mode"), WS_VISIBLE | WS_CHILD, leftMargin + 2 * (buttonWidth + buttonSpacing) + 2, 16, buttonWidth, buttonHeight, hwnd, (HMENU)3, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Ryan Mode"), WS_VISIBLE | WS_CHILD, leftMargin + 3 * (buttonWidth + buttonSpacing) + 3, 16, buttonWidth, buttonHeight, hwnd, (HMENU)4, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Cube Mode"), WS_VISIBLE | WS_CHILD, leftMargin + 4 * (buttonWidth + buttonSpacing) + 4, 16, buttonWidth, buttonHeight, hwnd, (HMENU)5, NULL, NULL);
    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}