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

    SetTimer(hwnd, 1, 30, NULL);  // Start the timer with 60 frames per second (1000ms / 60fps = 16ms per frame)

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


    static bool elevatorEmpty = true;
    static std::vector<int> firstFloorPeople;
    static std::vector<int> secondFloorPeople;
    static std::vector<int> thirdFloorPeople;
    static std::vector<int> fourthFloorPeople;
    static std::vector<int> inElevator;
    static std::vector<int> Calls;
    static int goTo = 4;

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
                isButton1Clicked = true;
                firstFloorPeople.push_back(2);
                Calls.push_back(1);
            }
                break;
            case 2: {
                isButton2Clicked = true;
                firstFloorPeople.push_back(3);
                Calls.push_back(2);
            }
                break;
            case 3: {
                isButton3Clicked = true;
                firstFloorPeople.push_back(4);
                Calls.push_back(3);
            }
                break;
            case 4: {
                isButton4Clicked = true;
                secondFloorPeople.push_back(1);
                Calls.push_back(4);
            }
                break;
            case 5: {
                isButton5Clicked = true;
                secondFloorPeople.push_back(3);
                Calls.push_back(5);
            }
                break;
            case 6: {
                isButton6Clicked = true;
                secondFloorPeople.push_back(4);
                Calls.push_back(6);
            }
                break;
            case 7: {
                isButton7Clicked = true;
                thirdFloorPeople.push_back(1);
                Calls.push_back(7);
            }
                break;
            case 8: {
                isButton8Clicked = true;
                thirdFloorPeople.push_back(2);
                Calls.push_back(8);
            }
                break;
            case 9: {
                isButton9Clicked = true;
                thirdFloorPeople.push_back(4);
                Calls.push_back(9);
            }
                break;
            case 10: {
                isButton10Clicked = true;
                fourthFloorPeople.push_back(1);
                Calls.push_back(10);
            }
                break;
            case 11: {
                isButton11Clicked = true;
                fourthFloorPeople.push_back(2);
                Calls.push_back(11);
            }
                break;
            case 12: {
                isButton12Clicked = true;
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

        graphics.DrawRectangle(&pen, 640, 40, 260, 700); // zewn
        graphics.DrawRectangle(&pen, 650, a - 150, 240, 150); // środek
        graphics.DrawLine(&pen, 900, 200, 1490, 200);
        graphics.DrawLine(&pen, 50, 350, 640, 350);
        graphics.DrawLine(&pen, 900, 500, 1490, 500);
        graphics.DrawLine(&pen, 50, 650, 640, 650);

        // Set the font and brush for drawing text
        Gdiplus::Font font(L"Arial", 10);
        Gdiplus::SolidBrush brush(Gdiplus::Color::Black);


        for (int i = 0; i < firstFloorPeople.size(); ++i)
        {
            Gdiplus::PointF point(20.0f * i, 110.0f);
            wchar_t text[2];
            swprintf_s(text, L"%d", firstFloorPeople[i]);
            graphics.DrawString(text, -1, &font, point, &brush);
        }

        for (int i = 0; i < secondFloorPeople.size(); ++i)
        {
            Gdiplus::PointF point(20.0f * i, 80.0f);
            wchar_t text[2];
            swprintf_s(text, L"%d", secondFloorPeople[i]);
            graphics.DrawString(text, -1, &font, point, &brush);
        }

        for (int i = 0; i < thirdFloorPeople.size(); ++i)
        {
            Gdiplus::PointF point(20.0f * i, 50.0f);
            wchar_t text[2];
            swprintf_s(text, L"%d", thirdFloorPeople[i]);
            graphics.DrawString(text, -1, &font, point, &brush);
        }

        for (int i = 0; i < fourthFloorPeople.size(); ++i)
        {
            Gdiplus::PointF point(20.0f * i, 20.0f);
            wchar_t text[2];
            swprintf_s(text, L"%d", fourthFloorPeople[i]);
            graphics.DrawString(text, -1, &font, point, &brush);
        }

        for (int i = 0; i < Calls.size(); ++i)
        {
            Gdiplus::PointF point(20.0f * i, 200.0f);
            wchar_t text[3];
            swprintf_s(text, L"%d", Calls[i]);
            graphics.DrawString(text, -1, &font, point, &brush);
        }

        for (int i = 0; i < inElevator.size(); ++i)
        {
            Gdiplus::PointF point(20.0f * i, 300.0f);
            wchar_t text[2];
            swprintf_s(text, L"%d", inElevator[i]);
            graphics.DrawString(text, -1, &font, point, &brush);
        }
        

        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_TIMER: // NA RAZIE NIE MASZ USTAWIONEGO GO TO
        if (a == afloor1)
        {
            if (inElevator.size() != 0) // wyrzucamy obecnych w windzie chcących wyjść na 1 piętrze
            {
                for (int i = 0; i < inElevator.size(); i++)
                {
                    if (inElevator[i] == 1)
                    {
                        inElevator.erase(inElevator.begin() + i);
                        i = 0;
                    }  
                }
            }
                if (firstFloorPeople.size() != 0) // ważne, że to if, a nie else if; jeżeli są jacyś ludzie czekający na 1 piętrze, to ich wszystkich zabieramy (najpierw pakujemy ich do windy, a potem usuwamy całą kolejkę 4 piętra)
                {
                    for (int i = 0; i < firstFloorPeople.size(); i++) // wrzucamy wszystkich ludzi czekających na 1 piętrze do windy, tu przerzucamy całość, bo to najniższe piętro, na środkowych piętrach trzeba to będzie pilnować
                    {
                        inElevator.push_back(firstFloorPeople[i]);
                    }
                    firstFloorPeople.clear(); // usuwamy ludzi z pierwszego piętra
                    for (int i = 0; i < Calls.size(); i++) // z zawołań usuwamy te z pierwszego piętra
                    {
                        if (Calls[i] == 1 || Calls[i] == 2 || Calls[i] == 3)
                        {
                            Calls.erase(Calls.begin() + i);
                            i = 0;
                        }
                    }
                    if (goTo == 1) // TO WYMAGANIE MOŻLIWE, ŻE TRZEBA BĘDZIE USUNĄĆ (ZOSTAWIĆ JEGO ZAWARTOŚĆ, ALE BEZ TEGO IFA GOTO==1
                    {
                        if (Calls.size() != 0)
                        {
                            if (Calls[0] == 1 || Calls[0] == 2 || Calls[0] == 3)
                                goTo = 1;
                            else if (Calls[0] == 4 || Calls[0] == 5 || Calls[0] == 6)
                                goTo = 2;
                            else if (Calls[0] == 7 || Calls[0] == 8 || Calls[0] == 9)
                                goTo = 3;
                            else if (Calls[0] == 10 || Calls[0] == 11 || Calls[0] == 12)
                                goTo = 4;
                        }
                    }
                    for (int i = 0; i < inElevator.size(); i++) // sprawdzamy, czy ktoś z windzie chce jechać wyżej, niż goTo. Jak tak, to ustawiamy nowe goTo
                    {
                        if (inElevator[i] > goTo) goTo = inElevator[i];
                    }
                
            }
            else break;
        }
        else if (a == afloor2)
        {
            if (inElevator.size() != 0) // wyrzucamy obecnych w windzie chcących wyjść na 2 piętrze
            {
                for (int i = 0; i < inElevator.size(); i++)
                {
                    if (inElevator[i] == 2)
                    {
                        inElevator.erase(inElevator.begin() + i);
                        i = 0;
                    }
                        
                }
            }
            if (goTo == 2) // teraz musi się ustalić nowe goTo
            {
                if (Calls.size() != 0) // po pierwsze czy ktoś zawołał. Jak tak: na goTonastawiamy tego, który zawołał. Potem, jeżeli goTo>2 sprawdzamy, czy jest w windzie ktoś, kto chce jechać jeszcze wyżej
                {
                    if (Calls[0] == 1 || Calls[0] == 2 || Calls[0] == 3)
                        goTo = 1;
                    else if (Calls[0] == 4 || Calls[0] == 5 || Calls[0] == 6)
                        goTo = 2;
                    else if (Calls[0] == 7 || Calls[0] == 8 || Calls[0] == 9)
                        goTo = 3;
                    else if (Calls[0] == 10 || Calls[0] == 11 || Calls[0] == 12)
                        goTo = 4;

                    if (goTo > 2)
                        for (int i = 0; i < inElevator.size(); i++)
                        {
                            if (inElevator[i] > goTo) goTo = inElevator[i];
                        }
                }
                else if (inElevator.size() != 0) // jeżeli nikt nie zawołał, to wybieramy pierwszą osobę z windy jako goTo, a jeżeli będzie to liczba większa, niż 2, to sprawdzamy, czy jest ktoś kto chce jechać jeszcze wyżej i nastawiamy goTo na to
                {
                    inElevator[0] = goTo;
                    if (goTo > 2)
                    {
                        for (int i = 0; i < inElevator.size(); i++)
                        {
                            if (inElevator[i] > goTo) goTo = inElevator[i];
                        }
                    }
                }
            }
            if (secondFloorPeople.size() != 0)
            {
                if (goTo == 1) // gdy goTo to 1 - wrzucamy ludzi z 2 piętra chcących jechać na 1 piętro do windy - usuwamy ich z secondFloorPeople, usuwamy ich z Calls i dodajemy do windy
                {
                    for (int i = 0; i < secondFloorPeople.size(); i++)
                    {
                        if (secondFloorPeople[i] == 1)
                        {
                            secondFloorPeople.erase(secondFloorPeople.begin() + i);
                            inElevator.push_back(1);
                            i = 0;
                        }

                    }
                    for (int i = 0; i < Calls.size(); i++)
                        if (Calls[i] == 4)
                        {
                            Calls.erase(Calls.begin() + i);
                            i = 0;
                        }  
                }
                else if (goTo > 2) // gdy go to to 3 lub 4 - wrzucamy ludzi z 2 piętra chcących jechać na 3 i 4 do windy - usuwamy ich z secondFloorPeople, usuwamy ich z Calls i dodajemy do windy;
                {
                    for (int i = 0; i < secondFloorPeople.size(); i++) // przy dodawaniu ludzi uwzględniamy jeszcze, że jeżeli ktoś chce jechać na 4, a goTo to 3, to ustswiamy goTo na 4
                    {
                        if (secondFloorPeople[i] == 3 || secondFloorPeople[i] == 4) 
                        {
                            if (secondFloorPeople[i] == 4 && goTo == 3) goTo == 4;
                            inElevator.push_back(secondFloorPeople[i]);
                            secondFloorPeople.erase(secondFloorPeople.begin() + i);
                            i = 0;
                        }
                    }
                    for (int i = 0; i < Calls.size(); i++)
                        if (Calls[i] == 5 || Calls[i] == 6)
                        {
                            Calls.erase(Calls.begin() + i);
                            i = 0;
                        }
                }
            }
        }
        else if (a == afloor3)
        {
            if (inElevator.size() != 0) // wyrzucamy obecnych w windzie chcących wyjść na 3 piętrze
            {
                for (int i = 0; i < inElevator.size(); i++)
                {
                    if (inElevator[i] == 3)
                    {
                        inElevator.erase(inElevator.begin() + i);
                        i = 0;
                    }
                }
            }
            if (goTo == 3) // teraz musi się ustalić nowe goTo
            {
                if (Calls.size() != 0) // po pierwsze czy ktoś zawołał. Jak tak: na goTonastawiamy tego, który zawołał. Potem, jeżeli goTo>2 sprawdzamy, czy jest w windzie ktoś, kto chce jechać jeszcze wyżej
                {
                    if (Calls[0] == 1 || Calls[0] == 2 || Calls[0] == 3)
                        goTo = 1;
                    else if (Calls[0] == 4 || Calls[0] == 5 || Calls[0] == 6)
                        goTo = 2;
                    else if (Calls[0] == 7 || Calls[0] == 8 || Calls[0] == 9)
                        goTo = 3;
                    else if (Calls[0] == 10 || Calls[0] == 11 || Calls[0] == 12)
                        goTo = 4;

                    if (goTo < 3) // jeżeli goTo < 3, to jeżeli w windzie jest ktoś, kto chce jechać jeszcze niżej (czyli jak go to to 2, a w windzie jest ktoś, kto chce jechać na 1), to ustawiamy nowe goTo na 1;
                        for (int i = 0; i < inElevator.size(); i++)
                        {
                            if (inElevator[i] < goTo) goTo = inElevator[i];
                        }
                }
                else if (inElevator.size() != 0) // jeżeli nikt nie zawołał, to wybieramy pierwszą osobę z windy jako goTo, a jeżeli będzie to liczba większa, niż 2, to sprawdzamy, czy jest ktoś kto chce jechać jeszcze wyżej i nastawiamy goTo na to
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
                if (goTo == 4) // gdy goTo to 1 - wrzucamy ludzi z 2 piętra chcących jechać na 1 piętro do windy - usuwamy ich z secondFloorPeople, usuwamy ich z Calls i dodajemy do windy
                {
                    for (int i = 0; i < thirdFloorPeople.size(); i++)
                    {
                        if (thirdFloorPeople[i] == 4)
                        {
                            thirdFloorPeople.erase(thirdFloorPeople.begin() + i);
                            inElevator.push_back(4);
                            i = 0;
                        }

                    }
                    for (int i = 0; i < Calls.size(); i++)
                        if (Calls[i] == 9)
                        {
                            Calls.erase(Calls.begin() + i);
                            i = 0;
                        }
                }
                else if (goTo < 3) // gdy go to to 3 lub 4 - wrzucamy ludzi z 2 piętra chcących jechać na 3 i 4 do windy - usuwamy ich z secondFloorPeople, usuwamy ich z Calls i dodajemy do windy;
                {
                    for (int i = 0; i < thirdFloorPeople.size(); i++) // przy dodawaniu ludzi uwzględniamy jeszcze, że jeżeli ktoś chce jechać na 4, a goTo to 3, to ustswiamy goTo na 4
                    {
                        if (thirdFloorPeople[i] == 1 || thirdFloorPeople[i] == 2)
                        {
                            if (thirdFloorPeople[i] == 1 && goTo == 2) goTo == 1;
                            inElevator.push_back(thirdFloorPeople[i]);
                            thirdFloorPeople.erase(thirdFloorPeople.begin() + i);
                            i = 0;
                        }
                    }
                    for (int i = 0; i < Calls.size(); i++)
                        if (Calls[i] == 7 || Calls[i] == 8)
                        {
                            Calls.erase(Calls.begin() + i);
                            i = 0;
                        }
                }
            }
        }
        if (a == afloor4)
        {
            if (inElevator.size() != 0) // wyrzucamy obecnych w windzie chcących wyjść na 1 piętrze
            {
                for (int i = 0; i < inElevator.size(); i++)
                {
                    if (inElevator[i] == 4)
                    {
                        inElevator.erase(inElevator.begin() + i);
                        i = 0;
                    }
                }
            }
            if (fourthFloorPeople.size() != 0) // ważne, że to if, a nie else if; jeżeli są jacyś ludzie czekający na 1 piętrze, to ich wszystkich zabieramy (najpierw pakujemy ich do windy, a potem usuwamy całą kolejkę 4 piętra)
            {
                for (int i = 0; i < fourthFloorPeople.size(); i++) // wrzucamy wszystkich ludzi czekających na 1 piętrze do windy, tu przerzucamy całość, bo to najniższe piętro, na środkowych piętrach trzeba to będzie pilnować
                {
                    inElevator.push_back(fourthFloorPeople[i]);
                }
                fourthFloorPeople.clear(); // usuwamy ludzi z pierwszego piętra
                for (int i = 0; i < Calls.size(); i++) // z zawołań usuwamy te z pierwszego piętra
                {
                    if (Calls[i] == 10 || Calls[i] == 11 || Calls[i] == 12)
                    {
                        Calls.erase(Calls.begin() + i);
                        i = 0;
                    } 
                }
                if (goTo == 1) // TO WYMAGANIE MOŻLIWE, ŻE TRZEBA BĘDZIE USUNĄĆ (ZOSTAWIĆ JEGO ZAWARTOŚĆ, ALE BEZ TEGO IFA GOTO==1
                {
                    if (Calls.size() != 0) 
                    {
                        if (Calls[0] == 1 || Calls[0] == 2 || Calls[0] == 3)
                            goTo = 1;
                        else if (Calls[0] == 4 || Calls[0] == 5 || Calls[0] == 6)
                            goTo = 2;
                        else if (Calls[0] == 7 || Calls[0] == 8 || Calls[0] == 9)
                            goTo = 3;
                        else if (Calls[0] == 10 || Calls[0] == 11 || Calls[0] == 12)
                            goTo = 4;
                    }
                }
                for (int i = 0; i < inElevator.size(); i++) // sprawdzamy, czy ktoś z windzie chce jechać wyżej, niż goTo. Jak tak, to ustawiamy nowe goTo
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