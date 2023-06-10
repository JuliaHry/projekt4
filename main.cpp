#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <vector>

using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib") 

struct ButtonData
{
    int x; 
    int y; 
    std::string text;
    int id;
};

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


    std::vector<ButtonData> buttons;
    buttons.push_back({ 50, 615, "2", 1 });
    buttons.push_back({ 50, 580, "3", 2 });
    buttons.push_back({ 50, 545, "4", 3 });
    buttons.push_back({ 1450, 465, "1", 4 });
    buttons.push_back({ 1450, 430, "3", 5 });
    buttons.push_back({ 1450, 395, "4", 6 });
    buttons.push_back({ 50, 315, "1", 7 });
    buttons.push_back({ 50, 280, "2", 8 });
    buttons.push_back({ 50, 245, "4", 9 });
    buttons.push_back({ 1450, 165, "1", 10 });
    buttons.push_back({ 1450, 130, "2", 11 });
    buttons.push_back({ 1450, 95, "3", 12 });

    for (const auto& button : buttons)
    {
        HWND hButton = CreateWindow(
            "BUTTON",
            button.text.c_str(),
            WS_CHILD | WS_VISIBLE,
            button.x,
            button.y,
            25,
            25,
            hwnd,
            reinterpret_cast<HMENU>(button.id),  
            hInstance,
            NULL
        );

        if (hButton == NULL)
        {
            return 0;
        }
    }


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
    static bool isButton2Clicked = false;
    static bool isButton3Clicked = false;
    static bool isButton4Clicked = false;
    static bool isButton5Clicked = false;
    static bool isButton6Clicked = false;
    static bool isButton7Clicked = false;
    static bool isButton8Clicked = false;
    static bool isButton9Clicked = false;
    static bool isButton10Clicked = false;
    static bool isButton11Clicked = false;
    static bool isButton12Clicked = false;
    static bool goTo1 = false;
    static bool goTo2 = false;
    static bool goTo3 = false;
    static bool goTo4 = false;

    HWND hButton1 = reinterpret_cast<HWND>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    switch (uMsg)
    {
    case WM_COMMAND:
        if (HIWORD(wParam) == BN_CLICKED)  // Check if button was clicked
        {
            switch (LOWORD(wParam))
            {
            case 1: isButton1Clicked = true;
                break;
            case 2: isButton2Clicked = true;
                break;
            case 3: isButton3Clicked = true;
                break;
            case 4: isButton4Clicked = true;
                break;
            case 5: isButton5Clicked = true;
                break;
            case 6: isButton6Clicked = true;
                break;
            case 7: isButton7Clicked = true;
                break;
            case 8: isButton8Clicked = true;
                break;
            case 9: isButton9Clicked = true;
                break;
            case 10: isButton10Clicked = true;
                break;
            case 11: isButton11Clicked = true;
                break;
            case 12: isButton12Clicked = true;
                break;
            }
        }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        Graphics graphics(hdc);
        Pen pen(Color(255, 0, 0, 0));


        graphics.DrawRectangle(&pen, 640, 40, 260, 700); // zewn
        graphics.DrawRectangle(&pen, 650, a - 150, 240, 150); // środek
        graphics.DrawLine(&pen, 900, 200, 1490, 200);
        graphics.DrawLine(&pen, 50, 350, 640, 350);
        graphics.DrawLine(&pen, 900, 500, 1490, 500);
        graphics.DrawLine(&pen, 50, 650, 640, 650);

        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_TIMER:
        if (isButton1Clicked || isButton2Clicked || isButton3Clicked)
        {
            if (a < 650)
            {
                a += 1;
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
            else
            {
                if (isButton1Clicked)
                {
                    isButton1Clicked = false;
                    goTo2 = true;
                }
                else if (isButton2Clicked)
                {
                    isButton2Clicked = false;
                    goTo3 = true;
                }
                else if (isButton3Clicked)
                {
                    isButton3Clicked = false;
                    goTo4 = true;
                } 
            }
        }
        else if (isButton4Clicked || isButton5Clicked || isButton6Clicked)
        {
            if (a < 500)
            {
                a += 1;
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
            else if (a > 500) {
                a -= 1;
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            } 
            else {
                if (isButton4Clicked)
                {
                    isButton4Clicked = false;
                    goTo1 = true;
                }
                else if (isButton5Clicked)
                {
                    isButton5Clicked = false;
                    goTo3 = true;
                }
                else if (isButton6Clicked)
                {
                    isButton6Clicked = false;
                    goTo4 = true;
                }
            }
        }
        else if (isButton7Clicked || isButton8Clicked || isButton9Clicked)
        {
            if (a < 350) {
                a += 1;
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
            else if (a > 350) {
                a -= 1;
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
            else {
                if (isButton7Clicked)
                {
                    isButton7Clicked = false;
                    goTo1 = true;
                }
                else if (isButton8Clicked)
                {
                    isButton8Clicked = false;
                    goTo2 = true;
                }
                else if (isButton9Clicked)
                {
                    isButton9Clicked = false;
                    goTo4 = true;
                }
            }
        }
        else if (isButton10Clicked || isButton11Clicked || isButton12Clicked)
        {
            if (a > 200)
            {
                a -= 1;
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
            else {
                if (isButton10Clicked)
                {
                    isButton10Clicked = false;
                    goTo1 = true;
                }
                else if (isButton11Clicked)
                {
                    isButton11Clicked = false;
                    goTo2 = true;
                }
                else if (isButton12Clicked)
                {
                    isButton12Clicked = false;
                    goTo3 = true;
                }
            }
        }
        else if (goTo1)
        {
            if (a < 650)
            {
                a += 1;
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
            else goTo1 = false;
        }
        else if (goTo2)
        {
            if (a > 500)
            {
                a -= 1;
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
            else if (a < 500)
            {
                a += 1;
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
            else goTo2 = false;
        }
        else if (goTo3)
        {
            if (a > 350)
            {
                a -= 1;
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
            else if (a < 350)
            {
                a += 1;
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
        }
        else if (goTo4)
        {
            if (a > 200)
            {
                a -= 1;
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
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