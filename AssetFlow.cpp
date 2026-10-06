// AssetFlow.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "AssetFlow.h"

#define MAX_LOADSTRING 100

// Control IDs
#define ID_SEARCH_BAR 101
#define ID_BTN_INDICATORS 102
#define ID_BTN_AAPL 103
#define ID_BTN_NVDA 104
#define ID_BTN_MSFT 105
#define ID_BTN_TSLA 106
#define ID_BTN_SETTINGS 107

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Global Control Handles
HWND hSearchEdit, hBtnIndicators, hBtnAapl, hBtnNvda, hBtnMsft, hBtnTsla, hBtnSettings;
HFONT hFontLarge, hFontNormal, hFontBold;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ASSETFLOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASSETFLOW));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

//  FUNCTION: MyRegisterClass()
//  PURPOSE: Registers the window class.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASSETFLOW));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Light background theme
    wcex.lpszMenuName = nullptr;                    // Removed classic top menu for clean layout
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//  FUNCTION: InitInstance(HINSTANCE, int)
//  PURPOSE: Saves instance handle and creates main window
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, L"AssetFlow", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 1000, 650, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//  PURPOSE: Processes messages for the main window.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // Fix: Replaced CLEAN_TEXT_QUALITY with universally supported ANTIALIASED_QUALITY
        hFontLarge = CreateFont(22, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, L"Segoe UI");
        hFontBold = CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, L"Segoe UI");
        hFontNormal = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, L"Segoe UI");

        // Top Search Bar
        hSearchEdit = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            350, 20, 300, 25, hWnd, (HMENU)ID_SEARCH_BAR, hInst, nullptr);
        SendMessage(hSearchEdit, WM_SETFONT, (WPARAM)hFontNormal, TRUE);

        // Fix: Used the direct constant value (0x1501) for EM_SETCUEBANNER to prevent missing identifier errors
        SendMessage(hSearchEdit, 0x1501, FALSE, (LPARAM)L"Search stocks, ETFs, etc.");

        // Top Right Indicators Button
        hBtnIndicators = CreateWindowW(L"BUTTON", L"Indicators", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            880, 20, 90, 25, hWnd, (HMENU)ID_BTN_INDICATORS, hInst, nullptr);
        SendMessage(hBtnIndicators, WM_SETFONT, (WPARAM)hFontNormal, TRUE);

        // Left Side Watchlist Item Buttons
        hBtnAapl = CreateWindowW(L"BUTTON", L"AAPL", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            20, 110, 60, 35, hWnd, (HMENU)ID_BTN_AAPL, hInst, nullptr);
        SendMessage(hBtnAapl, WM_SETFONT, (WPARAM)hFontNormal, TRUE);

        hBtnNvda = CreateWindowW(L"BUTTON", L"NVDA", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            20, 160, 60, 35, hWnd, (HMENU)ID_BTN_NVDA, hInst, nullptr);
        SendMessage(hBtnNvda, WM_SETFONT, (WPARAM)hFontNormal, TRUE);

        hBtnMsft = CreateWindowW(L"BUTTON", L"MSFT", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            20, 210, 60, 35, hWnd, (HMENU)ID_BTN_MSFT, hInst, nullptr);
        SendMessage(hBtnMsft, WM_SETFONT, (WPARAM)hFontNormal, TRUE);

        hBtnTsla = CreateWindowW(L"BUTTON", L"TSLA", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            20, 260, 60, 35, hWnd, (HMENU)ID_BTN_TSLA, hInst, nullptr);
        SendMessage(hBtnTsla, WM_SETFONT, (WPARAM)hFontNormal, TRUE);

        // Bottom Left Settings Button
        hBtnSettings = CreateWindowW(L"BUTTON", L"Settings", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            15, 560, 70, 25, hWnd, (HMENU)ID_BTN_SETTINGS, hInst, nullptr);
        SendMessage(hBtnSettings, WM_SETFONT, (WPARAM)hFontNormal, TRUE);
    }
    break;


    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // Set text backgrounds to transparent so they match the light theme background window
        SetBkMode(hdc, TRANSPARENT);

        // 1. Draw Left Sidebar Panel Background (Light Gray Box)
        RECT sidebarRect = { 0, 0, 180, 2000 };
        HBRUSH hSidebarBrush = CreateSolidBrush(RGB(240, 240, 242));
        FillRect(hdc, &sidebarRect, hSidebarBrush);
        DeleteObject(hSidebarBrush);

        // 2. Draw "STOCKVIEWER" Header Text
        SetTextColor(hdc, RGB(0, 0, 0));
        SelectObject(hdc, hFontLarge);
        TextOutW(hdc, 15, 20, L"ASSETFLOW", 11);

        // 3. Draw "WATCHLIST" Sub-Header Text
        SelectObject(hdc, hFontBold);
        TextOutW(hdc, 15, 75, L"WATCHLIST", 9);

        // 4. Draw Center "PRICE CHART" Visual Placeholder Text
        SelectObject(hdc, hFontLarge);
        RECT clientRect;
        GetClientRect(hWnd, &clientRect);
        // Draw it centered dynamically inside the remaining right pane space
        RECT chartTextRect = { 180, 0, clientRect.right, clientRect.bottom };
        DrawTextW(hdc, L"PRICE CHART", -1, &chartTextRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

        EndPaint(hWnd, &ps);
    }
    break;

    case WM_SIZE:
    {
        // Optional: Dynamically adjust positions of elements here during window resize
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);

        MoveWindow(hBtnIndicators, width - 110, 20, 90, 25, TRUE);
        MoveWindow(hBtnSettings, 15, height - 40, 70, 25, TRUE);
    }
    break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections or button clicks:
        switch (wmId)
        {
        case ID_BTN_AAPL:
            MessageBoxW(hWnd, L"AAPL clicked!", L"Notification", MB_OK);
            break;
        case ID_BTN_NVDA:
            MessageBoxW(hWnd, L"NVDA clicked!", L"Notification", MB_OK);
            break;
        case ID_BTN_MSFT:
            MessageBoxW(hWnd, L"MSFT clicked!", L"Notification", MB_OK);
            break;
        case ID_BTN_TSLA:
            MessageBoxW(hWnd, L"TSLA clicked!", L"Notification", MB_OK);
            break;
        case ID_BTN_INDICATORS:
            MessageBoxW(hWnd, L"Indicators clicked!", L"Notification", MB_OK);
            break;
        case ID_BTN_SETTINGS:
            MessageBoxW(hWnd, L"Settings clicked!", L"Notification", MB_OK);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;

    case WM_DESTROY:
        // Clean up created font objects to prevent resource leaks
        DeleteObject(hFontLarge);
        DeleteObject(hFontBold);
        DeleteObject(hFontNormal);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
