 // 2.cpp : Defines the entry point for the application.
//
#include "framework.h"
#include "3.h"
#include "Ball.h"

#include <CommCtrl.h>
#include "atlstr.h"
#include <vector>
using namespace std;
#pragma warning(disable:4996)
#pragma comment(lib, "ComCtl32.Lib")

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
const double PI = 3.1415;
const int ID_TIMER1 = 1;
const int delta_time = 20;
int maxXCoord;
int maxYCoord;
HWND hStatus;
int isStopped = 0;
HWND hWnd;

std::vector<Ball*> balls;
int BallsCount;

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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3));

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



const wchar_t* getWC(const char* c) {
    const size_t cSize = strlen(c) + 1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs(wc, c, cSize);
    return wc;
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY3));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY3);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

void startStop() {
    if (isStopped) {
        isStopped = 0;
        SetTimer(hWnd, ID_TIMER1, delta_time, NULL);
    }
    else {
        isStopped = 1;
        KillTimer(hWnd, ID_TIMER1);
    }
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   
   


   // hStatus = CreateStatusWindow(WS_CHILD | WS_VISIBLE, L"", hWnd, 4000);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    static int x, y, size = 60, len = 10, angle = 60;
    
    static int isEdit = 0;
    static ofstream ofs;
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;

        case IDM_EDIT:
            if (isEdit == 0) {

                SetCapture(hWnd);
                isEdit = 1;
            }
            else {
                isEdit = 0;
                ReleaseCapture();
            }
            
            startStop();

            break;

        case IDM_STOP:
            startStop();
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;

    case WM_CREATE: {
        ofs.open("log");
        SetTimer(hWnd, ID_TIMER1, delta_time, NULL);

        BallsCount = 1;
        RECT rect = { 0 };
        GetClientRect(hWnd, &rect);
        maxXCoord = rect.right - rect.left - size;
        maxYCoord = rect.bottom - rect.top - size;
        for (size_t i = 0; i < BallsCount; i++) {
            int size = rand() % 40 + 10;
            Vector velocity(rand() % 5 + 1, rand() % 5 + 1);
            Vector center(rand() % maxXCoord  + 2*size, rand() % maxYCoord + 2*size + 1);
            balls.push_back( new Ball(hWnd,size, velocity, center));
        }

    }
                  break;

    case WM_LBUTTONDOWN:
        if (isEdit) {
            POINT cursorPos;
            GetCursorPos(&cursorPos);
            ScreenToClient(hWnd, &cursorPos);
            for (Ball* b : balls) {
                double distance = sqrt(pow(cursorPos.x - b->center.x, 2) +
                    pow(cursorPos.y - b->center.y, 2));
                if (distance < b->radius) {
                    MessageBox(hWnd, TEXT("Операция выполнена успешно!"), TEXT("Ошибка во входных данных"), MB_OK | MB_ICONASTERISK);

                }
            }
        }
        break;



    case WM_TIMER: {
        for (Ball* ball : balls) {
                      
            RECT rect = { 0 };
            GetClientRect(hWnd, &rect);
            maxXCoord = rect.right - rect.left -  ball->radius;
            maxYCoord = rect.bottom - rect.top -  ball->radius;

            ball->center = ball->center + ball->velocity;

            int radius = ball->radius;

            ball->checkBorders(0, 0, maxXCoord, maxYCoord);

            
          //  ball->center = ball->center + ball->velocity;
            

            for (int i = 0; i < BallsCount - 1; i++)
            {
                for (int j = i + 1; j < BallsCount; j++)
                {
                    
                    if (balls[i]->isCollision(balls[j])) {
                        while ((balls[i]->isCollision(balls[j]))) {
                            Vector p1 = balls[i]->center;
                            Vector p2 = balls[j]->center;
                            // шары удобнее всего расталкивать вдоль прямой,
                            // проходящей через их центры
                            Vector penetrationDirection = (p2 - p1).normalize();
                            // глубина проникновения - это сумма радиусов двух шаров
                            // минус расстояние между их центрами
                           // float penetrationDepth = balls[i]->radius + balls[j]->radius
                            //    - (p2 - p1).getLength();

                           
                            balls[i]->center -= penetrationDirection * 0.5;
                            balls[j]->center += penetrationDirection * 0.5;
                        }
                        ofs << "Номера: " << i << " " << j << "\nКоординаты: " << balls[i]->center << ","
                            << balls[j]->center << "Скорости до удара:" << balls[i]->velocity << "," << balls[j]->velocity;

                        Vector p1 = balls[i]->velocity * balls[i]->mass;
                        Vector p2 = balls[j]->velocity * balls[j]->mass;

                        Vector v1 =  (p2 * 2.0 + balls[i]->velocity * 
                            (balls[i]->mass - balls[j]->mass))
                            / (balls[i]->mass + balls[j]->mass);

                        Vector v2 = (p1 * 2.0 + balls[j]->velocity *
                            (balls[j]->mass - balls[i]->mass))
                            / (balls[j]->mass + balls[i]->mass);

                        balls[i]->velocity = v1;
                        balls[j]->velocity = v2;

                        ofs << "Скорости после удара: " << v1 << "," << v2 << endl;
                       
                        balls[i]->checkBorders(0, 0, maxXCoord, maxYCoord);
                        balls[j]->checkBorders(0, 0, maxXCoord, maxYCoord);
                    }
                
                }
            }
            
               
                
        }
        
       

                
            InvalidateRect(hWnd, NULL, TRUE);
            break;

    }

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        for (int i = 0; i < BallsCount; i++)
        {
            balls[i]->draw(hdc);
        }
        EndPaint(hWnd, &ps);
        break;
    }

    case WM_DESTROY:
        ofs.close();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
