#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>
POINT point = { 50, 50 }; // �ʱ� �� ��ġ
POINT startPoint = { 0 }; // ��¥ ���� ���� �������� �����س��� chatgpt�� ���� �����ϰ� ®�µ� ���������� �̻��� �κ��� ���� ��ġ�� ���ؼ� 10�ú��� ��ħ 6�ñ��� ����@���� �ߴٴ°� �ϱ����� �ʴ�
POINT endPoint = { 0 };
POINT startPoint1 = { 0 };
POINT endPoint1 = { 0 };
int isMouseLButtonPressed = 0;
int RightButtonActived = 0;
RECT dragRect;

// �������� �̺�Ʈ�� ó���ϴ� �ݹ�(Callback) �Լ�.
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
        // ���콺 ������ ��ư Ŭ�� �̺�Ʈ ó��
        POINTS pt = MAKEPOINTS(lParam);
        POINT clientPoint = { pt.x, pt.y };
        ScreenToClient(hwnd, &clientPoint);

        // Ŭ���̾�Ʈ ��ǥ�� ������� � ��ü�� Ŭ���ߴ��� Ȯ���ϴ� �ڵ带 �߰��մϴ�.
        // �� ���������� ���� �ϳ��� �簢���� ó���ϵ��� �����մϴ�.

        // ���õ� �簢���� �巡���� �� �ʿ��� ������ �����մϴ�.
        if (PtInRect(&dragRect, clientPoint)) {
            RightButtonActived = 1;
            startPoint1 = endPoint1 = clientPoint; // ���� �� �� ����Ʈ�� ���� ���콺 ��ġ�� �����մϴ�.
        }
    }
    break;

    case WM_MOUSEMOVE:
    {
        // ���콺 �̵� ��
        if (isMouseLButtonPressed)
        {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);

            // WM_PAINT �޽����� �����Ͽ� �׸� ȭ�鿡 �׸��ϴ�.
            InvalidateRect(hwnd, NULL, TRUE);
        }
        if (RightButtonActived)
        {
            endPoint1.x = LOWORD(lParam);
            endPoint1.y = HIWORD(lParam);

            // ���� ���콺 ��ġ�� ���� Ŭ�� ��ġ ������ �Ÿ��� ����մϴ�.
            int deltaX = endPoint1.x - startPoint1.x;
            int deltaY = endPoint1.y - startPoint1.y;

            // ���õ� �簢���� �̵��մϴ�.
            OffsetRect(&dragRect, deltaX, deltaY);

            startPoint1 = endPoint1; // ���� ���콺 ��ġ�� ���ο� ���������� �����մϴ�.

            // ȭ�� �ٽ� �׸���
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
        // ����Ű �Է� ó��
        int step = 5; // �̵� �Ÿ�
        if (wParam == VK_LEFT) {
            point.x -= step; // �������� �̵�
        }
        else if (wParam == VK_RIGHT) {
            point.x += step; // ���������� �̵�
        }
        else if (wParam == VK_UP) {
            point.y -= step; // ���� �̵�
        }
        else if (wParam == VK_DOWN) {
            point.y += step; // �Ʒ��� �̵�
        }

        // WM_PAINT �޽����� �����Ͽ� ���� �ٽ� �׸��ϴ�.
        InvalidateRect(hwnd, NULL, TRUE);
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = GetDC(hwnd);
        // �� �׸���
        HBRUSH hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255)); // ��� �귯�� ����
        FillRect(hdc, &ps.rcPaint, hWhiteBrush); // Ŭ���̾�Ʈ ������ ������� ä��
        DeleteObject(hWhiteBrush); // �귯�� ����

        Ellipse(hdc, point.x - 5, point.y - 5, point.x + 5, point.y + 5);

        EndPaint(hwnd, &ps);

        

        if (isMouseLButtonPressed)
        {
            RECT rect;
            GetClientRect(hwnd, &rect);
            FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));

            // �巡�� ���� ���� �׸���    
            dragRect.left = min(startPoint.x, endPoint.x);
            dragRect.top = min(startPoint.y, endPoint.y);
            dragRect.right = max(startPoint.x, endPoint.x);
            dragRect.bottom = max(startPoint.y, endPoint.y);

            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // ��ũ �귯�� ����
            FillRect(hdc, &dragRect, hBrush); // ��ũ�� ���� �׸���
            DeleteObject(hBrush);
        }

        // ��Ŭ������ �巡���ϴ� �簢�� �׸���
        if (RightButtonActived)
        {
            RECT rect;
            GetClientRect(hwnd, &rect);
            FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));

            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // ��ũ �귯�� ����
            FillRect(hdc, &dragRect, hBrush); // ��ũ�� ���� �׸���
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
    /* ������ Ŭ���� ����.*/
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));   // ��� 0���� �ʱ�ȭ.

    // ������ Ŭ���� �� ����
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("Computer Software");
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;

    // ������ Ŭ���� ���.
    if (RegisterClass(&wc) == 0)
    {
        MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
        exit(-1);   //����
    }

    // Window viewport ���� ����
    RECT rect = { 150, 100, 800, 600 };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    // ������ ����
    HWND hwnd = CreateWindow(
        wc.lpszClassName,
        TEXT("202107054 �̿�� 5���� ����"),
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, // ũ�� ���� �� ��ư ��Ȱ��ȭ
        0, 0,
        800, 600, // ������ â ũ��
        NULL, NULL,
        hInstance,
        NULL
    );

    // ���� �˻�.
    if (hwnd == NULL)
    {
        MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
        exit(-1);
    }

    // â ���̱�.
    ShowWindow(hwnd, SW_SHOW); // â ����
    UpdateWindow(hwnd); // ������Ʈ�ؾ� ����. �� ������ ���ٰ� ���� ��.

    // �޽��� ó�� ����.
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        // �޽��� ó��.
        if (GetMessage(&msg, NULL, 0, 0))
        {
            // �޽��� �ؼ�����.
            TranslateMessage(&msg);
            // �޽����� ó���ؾ��� ���� ��������.
            DispatchMessage(&msg);
        }
    }

    //���� �޽��� ������ 
    return (int)msg.wParam;
}