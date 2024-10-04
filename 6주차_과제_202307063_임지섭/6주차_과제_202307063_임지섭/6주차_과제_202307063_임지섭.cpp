// 6주차_과제_202307063_임지섭.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "6주차_과제_202307063_임지섭.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY6202307063, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY6202307063));

    MSG msg;

    // 기본 메시지 루프입니다:
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
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY6202307063));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY6202307063);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

bool darw = false;
int x, y, g_x, g_y, g_drawType=0;
int g_backgroud = 0;

HDC hdc;
HPEN myPen, osPen;
HBRUSH myBrush, osBrush;
HWND eraser;
HICON er_img;
RECT area;

#define eraser_id 999

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    x = LOWORD(lParam);
    y = HIWORD(lParam);

    switch (message)
    {
    case WM_CREATE:

        eraser = 
            CreateWindow(L"button", L"지우기", WS_CHILD | WS_VISIBLE | BS_ICON, 20, 20, 40, 40, hWnd, (HMENU)eraser_id, hInst, NULL);
        
        er_img = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));

        SendMessageW(eraser, BM_SETIMAGE, IMAGE_ICON, (LPARAM)er_img);
        break;

    case WM_LBUTTONDOWN:

        if(g_backgroud==0){
            myBrush = CreateSolidBrush(RGB(255, 255, 255));
        }
        else if (g_backgroud == 1) {
            myBrush = CreateSolidBrush(RGB(255, 0, 255));
        }
        else if (g_backgroud == 2) {
            myBrush = CreateSolidBrush(RGB(0, 0, 255));
        }
       
        myPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));

        if (x < area.left+10 || y < area.top+10) {
            darw = false;
        }
        else if (x > area.right-10 || y > area.bottom-10) {
            darw = false;
        }
        else {
            darw = true;
        }
        

        hdc = GetDC(hWnd);

        osBrush = (HBRUSH)SelectObject(hdc, myBrush);
        osPen = (HPEN)SelectObject(hdc, myPen);

        g_x = x;
        g_y = y;

        if ((0 == g_drawType) && darw) {
            MoveToEx(hdc, g_x, g_y, NULL);
        }

        break;

    case WM_MOUSEMOVE:

        if (x < area.left + 10)  {
            darw = false;
        }
        else if (y < area.top + 10) {
            darw = false;
        }
        else if (x > area.right - 10) {
            darw = false;
        }
        else if (y > area.bottom - 10) {
            darw = false;
        }
       

        if (darw) {
            
            if (3 == g_drawType) {
                MoveToEx(hdc, g_x, g_y, NULL);
                LineTo(hdc, x, y);
                g_x = x;
                g_y = y;
            }

        }
        break;

    case WM_LBUTTONUP:
        if ((0 == g_drawType) && darw) {
            LineTo(hdc, x, y);
        }
        else if ((1 == g_drawType) && darw) {
            Rectangle(hdc, g_x, g_y, x, y);
        }
        else if ((2 == g_drawType) && darw) {
            Ellipse(hdc, g_x, g_y, x, y);
        }

        darw = false;

        DeleteObject(myBrush);
        DeleteObject(myPen);
        ReleaseDC(hWnd, hdc);
        break;

    case WM_SIZE:
        GetClientRect(hWnd, &area);

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {

            ///지우기 기능
        case eraser_id:
            InvalidateRect(hWnd,NULL,TRUE);
            break;

            /// 선 그리기
        case ID_32771:
            g_drawType = 0;
            break;

            ///사각형 그리기
        case ID_32772:
            g_drawType = 1;
            break;

            ///타원 그리기
        case ID_32773:
            g_drawType = 2;
            break;

            ///자유선 그리기
        case ID_32774:
            g_drawType = 3;
            break;

            ///면색 흰색
        case ID_32775:
            g_backgroud = 0;
            break;

            ///면색 보라색
        case ID_32776:
            g_backgroud = 1;
            break;

            ///면색 파란색
        case ID_32777:
            g_backgroud = 2;
            break;

        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;



    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

        Rectangle(hdc, area.left + 5, area.top + 5, area.right - 5, area.bottom - 5);
        

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:

        DestroyWindow(eraser);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
// 정보 대화 상자의 메시지 처리기입니다.
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
