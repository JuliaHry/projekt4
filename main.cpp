#include <windows.h>
#include <gdiplus.h>
#include <iostream>

using namespace Gdiplus;

// Step 1: Declare a global variable for the window class name
const char* g_WindowClassName = "BlankWindowClass";

// Step 2: Declare a global variable for the window handle
HWND g_hwnd = NULL;

// Step 3: Declare the window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Step 4: Define the entry point of the application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Step 5: Initialize GDI+
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Step 6: Register the window class
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = g_WindowClassName;
    RegisterClassEx(&wc);

    // Step 7: Create the window
    g_hwnd = CreateWindowEx(
        0,
        g_WindowClassName,
        "Blank Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1100,
        700,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (g_hwnd == NULL)
    {
        return 0;
    }

    // Step 8: Show and update the window
    ShowWindow(g_hwnd, nCmdShow);
    UpdateWindow(g_hwnd);

    // Step 9: Enter the message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Step 10: Shutdown GDI+
    GdiplusShutdown(gdiplusToken);

    // Step 11: Unregister the window class
    UnregisterClass(g_WindowClassName, hInstance);

    return static_cast<int>(msg.wParam);
}

// Step 12: Define the window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        Graphics graphics(hdc);
        Pen pen(Color(255, 0, 0, 0));  // Create a black pen
        Pen pen1(Color(255, 255, 255, 255));

        int a = 200;
       
        graphics.DrawRectangle(&pen, 640, 40, 260, 700); // zewn
        graphics.DrawLine(&pen, 900, 500, 1490, 500);
        graphics.DrawLine(&pen, 50, 350, 640, 350);
        graphics.DrawLine(&pen, 50, 650, 640, 650);
        graphics.DrawLine(&pen, 900, 200, 1490, 200);

        while (a != 650)
        {
            graphics.DrawRectangle(&pen1, 650, a-150, 240, 150);
            a++;
            graphics.DrawRectangle(&pen, 650, a-150, 240, 150); // œrodek
            
        }

        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}