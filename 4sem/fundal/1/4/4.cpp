 // 4.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "4.h"
#include "Figure.h"
#pragma warning(disable:4996)

#define MAX_LOADSTRING 100

#define RADIUS_FOR_CORNER_MOVE 10

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
bool drawByClick = 0;
Figure* figureUnderEdit = NULL;
std::vector<Figure*> figures;
HWND hListBox;
const int ID_LIST = 9999;
Figure* figure = NULL;
bool isMove = 0;
bool isDeform = 0;
int oldX;
int oldY;
POINT* pointUnderEdit;

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
    LoadStringW(hInstance, IDC_MY4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY4));

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

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY4);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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

            case IDM_DRAW_BY_CLICK:
                drawByClick = drawByClick == 0 ? 1 : 0;
                break;

            case IDM_RANDOM: {
                
                RECT rect = { 0 };
                GetClientRect(hWnd, &rect);
                int maxXCoord = rect.right - rect.left;
                int maxYCoord = rect.bottom - rect.top;
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);
                for (int j = 0; j < 3; ++j) {
                    Figure* f = new Figure(hWnd);
                    int rx = rand() % maxXCoord / 2 + maxXCoord / 10;
                    int ry = rand() % maxYCoord / 2 +  maxYCoord / 10;
                    
                    POINT p[] = { {rx,ry} , {rx + rx / 2, ry},{rx + rx / 2 , ry + ry / 2} ,
                    {rx, ry + ry / 2} };
                       

                    f->addPoint(POINT(p[0]));
                    f->addPoint(POINT(p[1]));
                    f->addPoint(POINT(p[2]));
                    f->addPoint(POINT(p[3]));
                    f->draw(hdc);
                   
                    figures.push_back(f);
                }
                EndPaint(hWnd, &ps);
                hListBox = CreateWindow(_T("listbox"), NULL,
                    WS_CHILD | WS_VISIBLE | LBS_STANDARD |
                    LBS_WANTKEYBOARDINPUT,
                    30, 30, 200, 100,
                    hWnd, (HMENU)ID_LIST, hInst, NULL);
                for (int i = 0; i < figures.size(); ++i) {
                    wchar_t num[sizeof(i)];
                    _swprintf(num, L"%d", i);
                    
                    SendMessageW(hListBox, LB_ADDSTRING, 0,
                        (WPARAM) num );
                    SendMessageW(hListBox, LB_SETITEMDATA, i, (WPARAM)i);
                    
                }
                InvalidateRect(hWnd, NULL, TRUE);
               
                break;
            }

            case ID_LIST: {
                switch (LOWORD(wParam)){
                    case ID_LIST: {

                        switch (HIWORD(wParam)){

                            case LBN_SELCHANGE: {
                                int n = (int)SendMessage(hListBox,
                                    LB_GETCURSEL, 0, 0L);
                                if (n != LB_ERR) {
                                    InvalidateRect(hWnd, NULL, TRUE);
                                    PAINTSTRUCT ps;
                                    HDC hdc = BeginPaint(hWnd, &ps);
                                    figures[n]->draw(hdc);
                                    figure = figures[n];
                                    EndPaint(hWnd, &ps);
                            

                                }
                        
                            }
                        }
                    }
                }
                break;
            }

            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_LBUTTONDOWN: {
        if (drawByClick) {
            POINT cursorPos;
            GetCursorPos(&cursorPos);
            ScreenToClient(hWnd, &cursorPos);
            if (!figureUnderEdit) {
                Figure* f = new Figure(hWnd);
                figures.push_back(f);
                figureUnderEdit = f;
            }

            figureUnderEdit->addPoint(cursorPos);

            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        else if (figure) {
            POINT cursorPos;
            GetCursorPos(&cursorPos);
            ScreenToClient(hWnd, &cursorPos);
            for (int i = 0; i < figure->points.size(); ++i) {
                double distance = sqrt(pow(cursorPos.x - figure->points[i].x, 2) +
                    pow(cursorPos.y - figure->points[i].y, 2));
                
                if (distance < RADIUS_FOR_CORNER_MOVE) {
                    pointUnderEdit = &figure->points[i];
                    isDeform = 1;
                    oldX = cursorPos.x;
                    oldY = cursorPos.y;
                    break;
                }

                   
               

            }

            if (!isDeform && cursorPos.x > figure->points[0].x&& cursorPos.x < figure->points[1].x &&
                 cursorPos.y < figure->points[3].y&& cursorPos.y > figure->points[0].y) {
            
            isMove = 1;
            oldX = cursorPos.x;
            oldY = cursorPos.y;
        } 
        }

        break;
    }

    case WM_MOUSEMOVE: {
        if (figure) {
            POINT cursorPos;
            GetCursorPos(&cursorPos);
            ScreenToClient(hWnd, &cursorPos);

            RECT rect = { 0 };
            GetClientRect(hWnd, &rect);
            int maxXCoord = rect.right - rect.left;
            int maxYCoord = rect.bottom - rect.top;

            for (int i = 0; i < figure->points.size(); ++i) {
               
                    if (figure->points[i].x > maxXCoord) {
                        figure->move(maxXCoord-figure->points[i].x , 0);
                    }

                    if (figure->points[i].y > maxYCoord) {
                        figure->move(0, maxYCoord - figure->points[i].y );
                    }

                    if (figure->points[i].x < 0) {
                        figure->move(-figure->points[i].x,
                            0);
                    }

                    if (figure->points[i].y < 0) {
                        figure->move(0,
                            -figure->points[i].y);
                    }
                    
                }
            
            
            if (figure && isMove) {   
                figure->move(cursorPos.x - oldX, cursorPos.y - oldY);
            }
            else if (isDeform) {
                pointUnderEdit->x += cursorPos.x - oldX;
                pointUnderEdit->y += cursorPos.y - oldY;  
            }
            oldX = cursorPos.x;
            oldY = cursorPos.y;
            InvalidateRect(hWnd, NULL, TRUE);
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            figure->draw(hdc);
            EndPaint(hWnd, &ps);
        }
        break;
    }

    case WM_LBUTTONUP:
        isMove = 0;
        isDeform = 0;
        break;


    case WM_RBUTTONDOWN: {
        figureUnderEdit = NULL;
    }


    case WM_PAINT:
        {

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            for (Figure *f : figures) {
                f->draw(hdc);
            }
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
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
