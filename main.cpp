#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <string>

using namespace Gdiplus;

// Step 1: Declare a global variable for the window class name
const char* g_WindowClassName = "BlankWindowClass";

// Step 2: Declare a global variable for the window handle
HWND g_hwnd = NULL;
HWND g_hButton = NULL;

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
    int a = 200;


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

    g_hButton = CreateWindow(
        "BUTTON",
        "1",
        WS_CHILD | WS_VISIBLE,
        55,
        610,
        25,
        25,
        g_hwnd,
        NULL,
        hInstance,
        NULL
    );

    if (g_hButton == NULL)
    {
        return 0;
    }

    // Step 8: Show and update the window
    ShowWindow(g_hwnd, nCmdShow);
    UpdateWindow(g_hwnd);

    SetTimer(g_hwnd, 1, 10, NULL);  // Timer ID = 1, interval = 10 milliseconds

    // Step 9: Enter the message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    KillTimer(g_hwnd, 1);

    // Step 10: Shutdown GDI+
    GdiplusShutdown(gdiplusToken);

    // Step 11: Unregister the window class
    UnregisterClass(g_WindowClassName, hInstance);

    return static_cast<int>(msg.wParam);
}

// Step 12: Define the window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int a = 200;

    static bool isButton1Clicked = false;  // Flag variable to track Button 1 click event

    switch (uMsg)
    {
    case WM_COMMAND:
        if (lParam == (LPARAM)g_hButton)  // Check if the button was clicked
        {
            isButton1Clicked = true;  // Set the flag to true
            MessageBox(hwnd, "Button 2 was clicked!", "Button Clicked", MB_OK | MB_ICONINFORMATION);
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        Graphics graphics(hdc);
        Pen pen(Color(255, 0, 0, 0));  // Create a black pen
        Pen pen1(Color(255, 255, 255, 255));

       
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
        if (isButton1Clicked)  // Move the elevator only when Button 1 is clicked
        {
            // Update the elevator coordinates
            a += 1;

            // Redraw the window
            InvalidateRect(hwnd, NULL, TRUE);
            UpdateWindow(hwnd);
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}