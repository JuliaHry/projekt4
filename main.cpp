#include <windows.h>
#include <gdiplus.h>
#include <string>

using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")  // Link against the GDI+ library

const char* GetWindowClassName()
{
    static const char* windowClassName = "BlankWindowClass";
    return windowClassName;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = GetWindowClassName();
    RegisterClassEx(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        GetWindowClassName(),
        "Blank Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        800,
        600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    HWND hButton1 = CreateWindow(
        "BUTTON",
        "1",
        WS_CHILD | WS_VISIBLE,
        50,
        50,
        50,
        30,
        hwnd,
        NULL,
        hInstance,
        NULL
    );

    if (hButton1 == NULL)
    {
        return 0;
    }

    HWND hButton2 = CreateWindow(
        "BUTTON",
        "2",
        WS_CHILD | WS_VISIBLE,
        120,
        50,
        50,
        30,
        hwnd,
        NULL,
        hInstance,
        NULL
    );

    if (hButton2 == NULL)
    {
        return 0;
    }

    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(hButton1));

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    SetTimer(hwnd, 1, 16, NULL);  // Start the timer with 60 frames per second (1000ms / 60fps = 16ms per frame)

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    KillTimer(hwnd, 1);  // Stop the timer

    GdiplusShutdown(gdiplusToken);

    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int a = 200;
    static bool isButton1Clicked = false;

    HWND hButton1 = reinterpret_cast<HWND>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    switch (uMsg)
    {
    case WM_COMMAND:
        if (lParam == (LPARAM)hButton1)
        {

            isButton1Clicked = true;  // Set the flag indicating Button 1 was clicked
        }
        else if (lParam == (LPARAM)GetDlgItem(hwnd, 2))  // Check if Button 2 was clicked
        {
            MessageBox(hwnd, "Button 2 was clicked!", "Button Clicked", MB_OK | MB_ICONINFORMATION);
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        Graphics graphics(hdc);
        Pen pen(Color(255, 0, 0, 0));


        graphics.DrawRectangle(&pen, 640, 40, 260, 700); // zewn
        graphics.DrawRectangle(&pen, 650, a - 150, 240, 150); // œrodek
        graphics.DrawLine(&pen, 900, 200, 1490, 200);
        graphics.DrawLine(&pen, 50, 350, 640, 350);
        graphics.DrawLine(&pen, 900, 500, 1490, 500);
        graphics.DrawLine(&pen, 50, 650, 640, 650);

        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_TIMER:
        if (isButton1Clicked && a < 650)  // Move the line only if Button 1 was clicked
        {
            a += 1;
            InvalidateRect(hwnd, NULL, TRUE);
            UpdateWindow(hwnd);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
