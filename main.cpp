#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <vector>
#include<algorithm>

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


    std::vector<ButtonData> buttons; // wektor guzików
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

    SetTimer(hwnd, 1, 1/16, NULL);  // Start the timer with 60 frames per second (1000ms / 60fps = 16ms per frame)

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
    static int a = 650;
    static bool toGo1 = false;
    static bool toGo2 = false;
    static bool toGo3 = false;
    static bool toGo4 = false;

    static int toDelete = 0;
    static int deleted1 = 0;
    static int deleted2 = 0;
    static int deleted3 = 0;
    static int deleted4 = 0;

    static bool elevatorEmpty = true;
    static std::vector<int> firstFloorPeople;
    static std::vector<int> secondFloorPeople;
    static std::vector<int> thirdFloorPeople;
    static std::vector<int> fourthFloorPeople;
    static std::vector<int> inElevator;
    static std::vector<int> Calls;
    static int goTo = 1;


    int count1 = 0;
    int count2 = 0;
    int count3 = 0;

    static int afloor1 = 650;
    static int afloor2 = 500;
    static int afloor3 = 350; 
    static int afloor4 = 200;

    HWND hButton1 = reinterpret_cast<HWND>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    switch (uMsg)
    {
    case WM_COMMAND:
        if (HIWORD(wParam) == BN_CLICKED)  // Check if button was clicked
        {
            switch (LOWORD(wParam))
            {
            case 1: {
                firstFloorPeople.push_back(2);
                Calls.push_back(1);
            }
                break;
            case 2: {
                firstFloorPeople.push_back(3);
                Calls.push_back(2);
            }
                break;
            case 3: {
                firstFloorPeople.push_back(4);
                Calls.push_back(3);
            }
                break;
            case 4: {
                secondFloorPeople.push_back(1);
                Calls.push_back(4);
            }
                break;
            case 5: {
                secondFloorPeople.push_back(3);
                Calls.push_back(5);
            }
                break;
            case 6: {
                secondFloorPeople.push_back(4);
                Calls.push_back(6);
            }
                break;
            case 7: {
                thirdFloorPeople.push_back(1);
                Calls.push_back(7);
            }
                break;
            case 8: {
                thirdFloorPeople.push_back(2);
                Calls.push_back(8);
            }
                break;
            case 9: {
                thirdFloorPeople.push_back(4);
                Calls.push_back(9);
            }
                break;
            case 10: {
                fourthFloorPeople.push_back(1);
                Calls.push_back(10);
            }
                break;
            case 11: {
                fourthFloorPeople.push_back(2);
                Calls.push_back(11);
            }
                break;
            case 12: {
                fourthFloorPeople.push_back(3);
                Calls.push_back(12);
            }
                break;
            }
        }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        Graphics graphics(hdc);
        Pen pen(Color(255, 0, 0, 0));

        graphics.DrawRectangle(&pen, 640, 40, 260, 700); 
        graphics.DrawRectangle(&pen, 650, a - 150, 240, 150);
        graphics.DrawLine(&pen, 900, 200, 1490, 200);
        graphics.DrawLine(&pen, 50, 350, 640, 350);
        graphics.DrawLine(&pen, 900, 500, 1490, 500);
        graphics.DrawLine(&pen, 50, 650, 640, 650);


        Gdiplus::Font font(L"Arial", 20);
        Gdiplus::SolidBrush brush(Gdiplus::Color::Black);
        Gdiplus::Font font1(L"Arial", 10);
        Gdiplus::Font font2(L"Arial", 15);


        for (int i = 0; i < firstFloorPeople.size(); ++i)
        {
            Gdiplus::PointF point(30.0f * i + 100, 600.0f);
            wchar_t text[2];
            swprintf_s(text, L"%d", firstFloorPeople[i]);
            graphics.DrawString(text, -1, &font, point, &brush);
        }

        for (int i = 0; i < secondFloorPeople.size(); ++i)
        {
            Gdiplus::PointF point(30.0f * i + 930, 450.0f);
            wchar_t text[2];
            swprintf_s(text, L"%d", secondFloorPeople[i]);
            graphics.DrawString(text, -1, &font, point, &brush);
        }

        for (int i = 0; i < thirdFloorPeople.size(); ++i)
        {
            Gdiplus::PointF point(30.0f * i + 100, 300.0f);
            wchar_t text[2];
            swprintf_s(text, L"%d", thirdFloorPeople[i]);
            graphics.DrawString(text, -1, &font, point, &brush);
        }

        for (int i = 0; i < fourthFloorPeople.size(); ++i)
        {
            Gdiplus::PointF point(30.0f * i + 930, 150.0f);
            wchar_t text[2];
            swprintf_s(text, L"%d", fourthFloorPeople[i]);
            graphics.DrawString(text, -1, &font, point, &brush);
        }

        for (int i = 0; i < inElevator.size(); ++i)
        {
            Gdiplus::PointF point(20.0f * i + 650, a - 50.0f );
            wchar_t text[2];
            swprintf_s(text, L"%d", inElevator[i]);
            graphics.DrawString(text, -1, &font, point, &brush);
        }


        graphics.DrawRectangle(&pen, 645, 665, 250, 60);

        graphics.DrawString(L"MASA PASAŻERÓW: ", -1, &font1, PointF(700.0f, 670.0f), &brush);

        Gdiplus::PointF point1(750.0f, 690.0f);
        wchar_t text1[4];
        swprintf_s(text1, L"%d", inElevator.size()*70);
        graphics.DrawString(text1, -1, &font2, point1, &brush);



        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_TIMER:
        if (a == afloor1)
        { 
            if (inElevator.size() != 0)
            {
                inElevator.erase(std::remove(inElevator.begin(), inElevator.end(), 1), inElevator.end());
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
            if (firstFloorPeople.size() != 0) 
                {
                
                    for (int i = 0; i < firstFloorPeople.size() && inElevator.size() < 8; i++)
                    {
                        toDelete += 1;
                        inElevator.push_back(firstFloorPeople[i]);
                        if (firstFloorPeople[i] == 2) deleted2 += 1;
                        if (firstFloorPeople[i] == 3) deleted3 += 1;
                        if (firstFloorPeople[i] == 4) deleted4 += 1;
                    }
                    firstFloorPeople.erase(firstFloorPeople.begin(), firstFloorPeople.begin() + toDelete);
                    toDelete = 0;
                    Calls.erase(std::remove_if(Calls.begin(), Calls.end(),
                        [&count1](int value) {
                            if (value == 1 && count1 < deleted2) {
                                ++count1;
                                return true;
                            }
                            return false;
                        }),
                        Calls.end());
                    count1 = 0;
                    deleted2 = 0;
                    Calls.erase(std::remove_if(Calls.begin(), Calls.end(),
                        [&count2](int value) {
                            if (value == 2 && count2 < deleted3) {
                                ++count2;
                                return true;
                            }
                            return false;
                        }),
                        Calls.end());
                    count2 = 0;
                    deleted3 = 0;
                    Calls.erase(std::remove_if(Calls.begin(), Calls.end(),
                        [&count3](int value) {
                            if (value == 3 && count3 < deleted4) {
                                ++count3;
                                return true;
                            }
                            return false;
                        }),
                        Calls.end());
                    count3 = 0;
                    deleted4 = 0;
                    if (goTo == 1)
                    {
                        if (Calls.size() != 0)
                        {
                            if (firstFloorPeople.size() != 0)
                            {
                                if (Calls[0] == 4 || Calls[0] == 5 || Calls[0] == 6)
                                    goTo = 2;
                                else if (Calls[0] == 7 || Calls[0] == 8 || Calls[0] == 9)
                                    goTo = 3;
                                else if (Calls[0] == 10 || Calls[0] == 11 || Calls[0] == 12)
                                    goTo = 4;
                            }
                            else if (firstFloorPeople.size() == 0) {
                                if (Calls[0] == 4 || Calls[0] == 5 || Calls[0] == 6 || Calls[0] == 1)
                                    goTo = 2;
                                else if (Calls[0] == 7 || Calls[0] == 8 || Calls[0] == 9 || Calls[0] == 2)
                                    goTo = 3;
                                else if (Calls[0] == 10 || Calls[0] == 11 || Calls[0] == 12 || Calls[0] == 3)
                                    goTo = 4;
                            }
                        }
                    }
                    for (int i = 0; i < inElevator.size(); i++) 
                    {
                        if (inElevator[i] > goTo) goTo = inElevator[i];
                    }
                
            }
            else if (firstFloorPeople.size() == 0)
            {
                if (goTo == 1)
                {
                    if (Calls.size() != 0)
                    {
                        if (Calls[0] == 4 || Calls[0] == 5 || Calls[0] == 6 || Calls[0] == 1)
                            goTo = 2;
                        else if (Calls[0] == 7 || Calls[0] == 8 || Calls[0] == 9 || Calls[0] == 2)
                            goTo = 3;
                        else if (Calls[0] == 10 || Calls[0] == 11 || Calls[0] == 12 || Calls[0] == 3)
                            goTo = 4;
                    }
                }
                for (int i = 0; i < inElevator.size(); i++) 
                {
                    if (inElevator[i] > goTo) goTo = inElevator[i];
                }
            }
        }
        else if (a == afloor2)
        {
            if (inElevator.size() != 0) 
            {
                inElevator.erase(std::remove(inElevator.begin(), inElevator.end(), 2), inElevator.end());
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
            if (goTo == 2) 
            {
                if (Calls.size() != 0)
                {
                    if (Calls[0] == 1 || Calls[0] == 2 || Calls[0] == 3 || Calls[0] == 4)
                        goTo = 1;
                    else if (Calls[0] == 7 || Calls[0] == 8 || Calls[0] == 9 || Calls[0] == 5)
                        goTo = 3;
                    else if (Calls[0] == 10 || Calls[0] == 11 || Calls[0] == 12 || Calls[0] == 6)
                        goTo = 4;

                    if (goTo == 3)
                        for (int i = 0; i < inElevator.size(); i++)
                        {
                            if (inElevator[i] == 4) goTo = 4;
                        }
                }
                else if (Calls.size() == 0)
                {
                    if (inElevator.size() != 0)
                    {
                        inElevator[0] = goTo;
                    }
                    if (goTo == 3)
                    {
                        for (int i = 0; i < inElevator.size(); i++)
                        {
                            if (inElevator[i] = 4) goTo = 4;
                        }
                    }
                }
            }
            if (secondFloorPeople.size() != 0)
            {
                if (goTo == 1)
                {
                    for (int i = 0; i < secondFloorPeople.size() && inElevator.size() < 8; i++)
                    {
                        if (secondFloorPeople[i] == 1)
                        {
                            toDelete += 1;
                            inElevator.push_back(1);
                        }
                    }
                    secondFloorPeople.erase(std::remove_if(secondFloorPeople.begin(), secondFloorPeople.end(),
                        [&count1](int value) {
                            if (value == 1 && count1 < toDelete) {
                                ++count1;
                                return true;
                            }
                            return false;
                        }),
                        secondFloorPeople.end());
                    count1 = 0;
                    Calls.erase(std::remove_if(Calls.begin(), Calls.end(),
                        [&count1](int value) {
                            if (value == 4 && count1 < toDelete) {
                                ++count1;
                                return true;
                            }
                            return false;
                        }),
                        Calls.end());
                    count1 = 0;
                    toDelete = 0;
                }
                else if (goTo > 2) 
                {
                    deleted3 = 0;
                    deleted4 = 0;
                    for (int i = 0; i < secondFloorPeople.size() && inElevator.size() < 8; i++) 
                    {
                        if (secondFloorPeople[i] == 3 || secondFloorPeople[i] == 4) 
                        {
                            if (secondFloorPeople[i] == 4 && goTo == 3) goTo = 4;
                            inElevator.push_back(secondFloorPeople[i]);
                            if (secondFloorPeople[i] == 3) deleted3 += 1;
                            if (secondFloorPeople[i] == 4) deleted4 += 1;
                        }
                    }
                    secondFloorPeople.erase(std::remove_if(secondFloorPeople.begin(), secondFloorPeople.end(),
                        [&count2](int value) {
                            if (value == 3 && count2 < deleted3) {
                                ++count2;
                                return true;
                            }
                            return false;
                        }),
                        secondFloorPeople.end());
                    count2 = 0;
                    secondFloorPeople.erase(std::remove_if(secondFloorPeople.begin(), secondFloorPeople.end(),
                        [&count2](int value) {
                            if (value == 4 && count2 < deleted4) {
                                ++count2;
                                return true;
                            }
                            return false;
                        }),
                        secondFloorPeople.end());
                    count2 = 0;
                    Calls.erase(std::remove_if(Calls.begin(), Calls.end(),
                        [&count3](int value) {
                            if (value == 5 && count3 < deleted3) {
                                ++count3;
                                return true;
                            }
                            return false;
                        }),
                        Calls.end());
                    count3 = 0;
                    Calls.erase(std::remove_if(Calls.begin(), Calls.end(),
                        [&count1](int value) {
                            if (value == 6 && count1 < deleted4) {
                                ++count1;
                                return true;
                            }
                            return false;
                        }),
                        Calls.end());
                    count1 = 0;
                    deleted3 = 0;
                    deleted4 = 0;
                }
            }
        }
        else if (a == afloor3)
        {
            if (inElevator.size() != 0) 
            {
                inElevator.erase(std::remove(inElevator.begin(), inElevator.end(), 3), inElevator.end());
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
            if (goTo == 3)
            {
                if (Calls.size() != 0)
                {
                    if (Calls[0] == 1 || Calls[0] == 2 || Calls[0] == 3 || Calls[0] == 7)
                        goTo = 1;
                    else if (Calls[0] == 4 || Calls[0] == 5 || Calls[0] == 6 || Calls[0] == 8)
                        goTo = 2;
                    else if (Calls[0] == 10 || Calls[0] == 11 || Calls[0] == 12 || Calls[0] == 9)
                        goTo = 4;

                    if (goTo < 3)
                        for (int i = 0; i < inElevator.size(); i++)
                        {
                            if (inElevator[i] < goTo) goTo = inElevator[i];
                        }
                }
                else if (inElevator.size() != 0)
                {
                    inElevator[0] = goTo;
                    if (goTo < 3)
                    {
                        for (int i = 0; i < inElevator.size(); i++)
                        {
                            if (inElevator[i] < goTo) goTo = inElevator[i];
                        }
                    }
                }
            }
            if (thirdFloorPeople.size() != 0)
            {
                if (goTo == 4) 
                {
                    for (int i = 0; i < thirdFloorPeople.size() && inElevator.size() < 8; i++)
                    {
                        if (thirdFloorPeople[i] == 4)
                        {
                            toDelete += 1;
                            inElevator.push_back(4);
                        }
                    }
                    thirdFloorPeople.erase(std::remove_if(thirdFloorPeople.begin(), thirdFloorPeople.end(),
                        [&count1](int value) {
                            if (value == 4 && count1 < toDelete) {
                                ++count1;
                                return true;
                            }
                            return false;
                        }),
                        thirdFloorPeople.end());
                    count1 = 0;
                    Calls.erase(std::remove_if(Calls.begin(), Calls.end(),
                        [&count1](int value) {
                            if (value == 9 && count1 < toDelete) {
                                ++count1;
                                return true;
                            }
                            return false;
                        }),
                        Calls.end());
                    count1 = 0;
                    toDelete = 0;
                }
                else if (goTo < 3) 
                {
                    deleted1 = 0;
                    deleted2 = 0;
                    for (int i = 0; i < thirdFloorPeople.size() && inElevator.size() < 8; i++) 
                    {
                        if (thirdFloorPeople[i] == 1 || thirdFloorPeople[i] == 2)
                        {
                            if (thirdFloorPeople[i] == 1 && goTo == 2) goTo = 1;
                            inElevator.push_back(thirdFloorPeople[i]);
                            if (thirdFloorPeople[i] == 1) deleted1 += 1;
                            if (thirdFloorPeople[i] == 2) deleted2 += 1;
                        }
                    }
                    thirdFloorPeople.erase(std::remove_if(thirdFloorPeople.begin(), thirdFloorPeople.end(),
                        [&count2](int value) {
                            if (value == 1 && count2 < deleted1) {
                                ++count2;
                                return true;
                            }
                            return false;
                        }),
                        thirdFloorPeople.end());
                    count2 = 0;
                    thirdFloorPeople.erase(std::remove_if(thirdFloorPeople.begin(), thirdFloorPeople.end(),
                        [&count2](int value) {
                            if (value == 2 && count2 < deleted2) {
                                ++count2;
                                return true;
                            }
                            return false;
                        }),
                        thirdFloorPeople.end());
                    count2 = 0;
                    Calls.erase(std::remove_if(Calls.begin(), Calls.end(),
                        [&count3](int value) {
                            if (value == 7 && count3 < deleted1) {
                                ++count3;
                                return true;
                            }
                            return false;
                        }),
                        Calls.end());
                    count3 = 0;
                    Calls.erase(std::remove_if(Calls.begin(), Calls.end(),
                        [&count1](int value) {
                            if (value == 8 && count1 < deleted2) {
                                ++count1;
                                return true;
                            }
                            return false;
                        }),
                        Calls.end());
                    count1 = 0;
                    deleted3 = 0;
                    deleted4 = 0;
                }
            }
        }
        if (a == afloor4)
        {
            if (inElevator.size() != 0)
            {
                inElevator.erase(std::remove(inElevator.begin(), inElevator.end(), 4), inElevator.end());
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
            if (fourthFloorPeople.size() != 0)
            {
                for (int i = 0; i < fourthFloorPeople.size() && inElevator.size() < 8; i++)
                {
                    toDelete += 1;
                    inElevator.push_back(fourthFloorPeople[i]);
                    if (fourthFloorPeople[i] == 1) deleted1 += 1;
                    if (fourthFloorPeople[i] == 2) deleted2 += 1;
                    if (fourthFloorPeople[i] == 3) deleted3 += 1;

                }
                fourthFloorPeople.erase(fourthFloorPeople.begin(), fourthFloorPeople.begin() + toDelete);
                toDelete = 0;
                Calls.erase(std::remove_if(Calls.begin(), Calls.end(),
                    [&count1](int value) {
                        if (value == 10 && count1 < deleted1) {
                            ++count1;
                            return true;
                        }
                        return false;
                    }),
                    Calls.end());
                count1 = 0;
                deleted1 = 0;
                Calls.erase(std::remove_if(Calls.begin(), Calls.end(),
                    [&count2](int value) {
                        if (value == 11 && count2 < deleted2) {
                            ++count2;
                            return true;
                        }
                        return false;
                    }),
                    Calls.end());
                count2 = 0;
                deleted2 = 0;
                Calls.erase(std::remove_if(Calls.begin(), Calls.end(),
                    [&count3](int value) {
                        if (value == 12 && count3 < deleted3) {
                            ++count3;
                            return true;
                        }
                        return false;
                    }),
                    Calls.end());
                count3 = 0;
                deleted3 = 0;
                if (goTo == 4)
                {
                    if (Calls.size() != 0)
                    {
                        if (fourthFloorPeople.size() != 0)
                        {
                            if (Calls[0] == 1 || Calls[0] == 2 || Calls[0] == 3)
                                goTo = 1;
                            else if (Calls[0] == 4 || Calls[0] == 5 || Calls[0] == 6)
                                goTo = 2;
                            else if (Calls[0] == 10 || Calls[0] == 11 || Calls[0] == 12)
                                goTo = 3;
                        }
                        else if (fourthFloorPeople.size() == 0) {
                            if (Calls[0] == 1 || Calls[0] == 2 || Calls[0] == 3 || Calls[0] == 10)
                                goTo = 1;
                            else if (Calls[0] == 4 || Calls[0] == 5 || Calls[0] == 6 || Calls[0] == 11)
                                goTo = 2;
                            else if (Calls[0] == 7 || Calls[0] == 8 || Calls[0] == 9 || Calls[0] == 12)
                                goTo = 4;
                        }
                    }
                }
                for (int i = 0; i < inElevator.size(); i++)
                {
                    if (inElevator[i] < goTo) goTo = inElevator[i];
                }
            } 
            else if (fourthFloorPeople.size() == 0)
            {
                if (goTo == 4)
                {
                    if (Calls.size() != 0)
                    {
                            if (Calls[0] == 1 || Calls[0] == 2 || Calls[0] == 3 || Calls[0] == 10)
                                goTo = 1;
                            else if (Calls[0] == 4 || Calls[0] == 5 || Calls[0] == 6 || Calls[0] == 11)
                                goTo = 2;
                            else if (Calls[0] == 7 || Calls[0] == 8 || Calls[0] == 9 || Calls[0] == 12)
                                goTo = 3;
                    }
                }
                for (int i = 0; i < inElevator.size(); i++) 
                {
                    if (inElevator[i] < goTo) goTo = inElevator[i];
                }
            }
        }
        if (goTo == 1)
        {
            if (a < afloor1)
            { 
                a+=1;
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
        }
        if (goTo == 2)
        {
            if (a < afloor2)
            {
                a += 1;
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
            else if (a > afloor2)
            {
                a -= 1;
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
        }
        if (goTo == 3)
        {
            if (a < afloor3)
            {
                a += 1;
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
            else if (a > afloor3)
            {
                a -= 1;
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
        }
        if (goTo == 4)
        {
            if (a > afloor4)
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