// 5주차_과제_202307063_임지섭.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "5주차_과제_202307063_임지섭.h"
#include <stdio.h>
#include <time.h>

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
    LoadStringW(hInstance, IDC_MY5202307063, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY5202307063));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY5202307063));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY5202307063);
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

RECT g_area = {0,0,0,0};
RECT w_size = { 0,0,0,0 };

///나와 상대의 변수 및 초기 좌표 설정
RECT g_me = { 0,0,0,0 };    //나의 객체, 상대의 객체
RECT g_you = { 0,0,0,0 };

///아이템 객체의 초기 정보
RECT g_item;

///
RECT g_time;

///상대의 속도 제어를 위한 전역 변수
int g_timer = 1000;
///아이템이 보여지는지 여부
int g_view = 1;

int g_you_reset=0;

int g_start = 0;

RECT timer;
int timer_right;

HWND g_button;

#define IDM_BTN_CLICK 999

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    RECT a, b, c;   ///겹침이 발생한 좌표값. <-값을 받아오는거임
    
        

    switch (message)
    {

    case WM_CREATE:
        
        g_button =
            CreateWindow(L"button", L"Game Start", WS_CHILD | WS_VISIBLE, 100, 100 , 200, 80, hWnd, (HMENU)IDM_BTN_CLICK, hInst, NULL);


            ///랜덤 시드 결정, 프로그램 실행 시 단 한번만 수행하면 됨.
            srand(time(NULL));
        
           /* SetTimer(hWnd, 1, g_timer, NULL);
            ///NULL부분은 별도의 처리용 함수가 있을경우 함수 이름을 넣으면 된다.
            ///hWnd다음의 숫자는 ID번호 이다.
            SetTimer(hWnd, 2, 1000, NULL);

            SetTimer(hWnd, 3, 1000, NULL);*/


            g_item.left = rand() % 500;
            g_item.top = rand() % 500;
            if (g_item.top < 80) {
                g_item.top = 80;
            }
            g_item.right = g_item.left + 50;
            g_item.bottom = g_item.top + 50;



        break;

    case WM_SIZE:

        
            GetClientRect(hWnd, &w_size);
            g_area.left = w_size.left + 10;
            g_area.top = w_size.top + 80;
            g_area.right = w_size.right - 10;
            g_area.bottom = w_size.bottom - 10;
            timer.bottom = g_area.top - 10;

            if (g_you_reset == 0) {
                
                g_you_reset = 1;

                timer.left = g_area.left;
                timer.top = 10;
                timer.right = g_area.right;

            }

            
            

            timer_right = (int)(timer.right / 10);
        
        break;

    case WM_TIMER:
        
             ///wParam은 SetTimer에서 지정한 ID 값을 가지고 호출된다.
            
            if (3 == wParam) {
                timer.right -= timer_right;
                if (timer.right < timer.left) {
                    g_start = 0;
                    KillTimer(hWnd, 3);
                    KillTimer(hWnd, 2);
                    KillTimer(hWnd, 1);
                    ShowWindow(g_button, SW_NORMAL);
                    InvalidateRect(hWnd, NULL, TRUE);
                    MessageBox(hWnd, L"Your Win", L"승 리", MB_OK);
                }
            }
            
            if (1 == wParam) {
                /// 상대가 나의 좌표를 보고 상대의 x 좌표를 변경하는 코드

                if (g_me.left > g_you.left) ///나는 상대의 오른쪽에 있다.
                {
                    if (IntersectRect(&c, &g_area, &g_you)) {
                        g_you.right = c.right;
                        g_you.left = g_you.right - 90;
                    }
                    g_you.left += 50;
                    g_you.right += 50;
                }
                else ///나는 상대의 왼쪽에 있다.
                {
                    if (IntersectRect(&c, &g_area, &g_you)) {
                        g_you.left = c.left;
                        g_you.right = g_you.left + 90;
                    }

                    g_you.left -= 50;
                    g_you.right -= 50;
                }

                /// 상대가 나의 좌표를 보고 상대의 x 좌표를 변경하는 코드
                if (g_me.top > g_you.top)
                {
                    if (IntersectRect(&c, &g_area, &g_you)) {
                        g_you.bottom = c.bottom;
                        g_you.top = g_you.bottom - 90;
                    }
                    g_you.top += 50;
                    g_you.bottom += 50;

                }
                else
                {
                    g_you.top -= 50;
                    g_you.bottom -= 50;
                }

                ///상대가 나를 잡았는지 확인하는 단계
                ///좌표 겹침이 발생했는가를 확인!!!!
                InvalidateRect(hWnd, NULL, TRUE);

                if (IntersectRect(&a, &g_me, &g_you)) ///Intersect -> 겹침
                {   
                    g_start = 0;
                    /// 타이머를 멈추는 API호출
                    KillTimer(hWnd, 1);
                    KillTimer(hWnd, 2);
                    KillTimer(hWnd, 3);
                    ShowWindow(g_button, SW_NORMAL);
                    MessageBox(hWnd, L"패 배", L"GAME OVER", MB_OK);
                    ///MessageBox가 떴을때 MessageBox가 모든 호출을 잡아 먹는다
                    ///그럼으로 MessageBox밑에는 실행이 되지않는다
                    /// 타이머를 멈추기 위해서는 Message박스 이전에 호출해야 된다.
                }
                ///=>상대의 좌표 값을 조정한 상태 ===> 화면 무효화를 조정!


            }
            else if (2 == wParam) {
                ///상대의 속도를 조절!
                g_timer -= 100;
                if (g_timer <= 100)
                    g_timer = 100;
                KillTimer(hWnd, 1);
                SetTimer(hWnd, 1, g_timer, NULL);
            }
        
            break;

    case WM_KEYDOWN: 
       {
        ///나의 키 입력을 통해 나의 좌표 값을 변경하는 코드
        switch (wParam)
        {
        case VK_LEFT:
        {
            g_me.left -= 50;
            g_me.right -= 50;
            IntersectRect(&b, &g_area, &g_me);
            g_me.left = b.left;
            g_me.right = b.left + 90;
        }
        break;

        case VK_RIGHT:
        {
            g_me.left += 50;
            g_me.right += 50;
            IntersectRect(&b, &g_area, &g_me);
            g_me.right = b.right;
            g_me.left = b.right - 90;
        }
        break;

        case VK_UP:
        {
            g_me.top -= 50;
            g_me.bottom -= 50;
            IntersectRect(&b, &g_area, &g_me);
            g_me.top = b.top;
            g_me.bottom = b.top + 90;
        }
        break;

        case VK_DOWN:
        {
            g_me.top += 50;
            g_me.bottom += 50;
            IntersectRect(&b, &g_area, &g_me);
            g_me.bottom = b.bottom;
            g_me.top = b.bottom - 90;
        
           
        }
        break;
           

        }

        InvalidateRect(hWnd, NULL, TRUE);

        }
       break;

       ///버튼 이벤트 ID 확인 메시지
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다: 버튼 클릭시 ID 확인 가능한 위치
            switch (wmId)
            {

           case IDM_BTN_CLICK:
               g_start = 1;
               g_timer = 1000;
               g_me.left = g_area.left;
               g_me.top = g_area.top;
               g_me.right = g_me.left + 90;
               g_me.bottom = g_me.top + 90;

               g_you.bottom = g_area.bottom;
               g_you.right = g_area.right;
               g_you.top = g_you.bottom - 90;
               g_you.left = g_you.right - 90;
               g_you_reset = 1;

               timer.left = g_area.left;
               timer.top = 10;
               timer.right = g_area.right;

               SetTimer(hWnd, 1, g_timer, NULL);
               ///NULL부분은 별도의 처리용 함수가 있을경우 함수 이름을 넣으면 된다.
               ///hWnd다음의 숫자는 ID번호 이다.
               SetTimer(hWnd, 2, 1000, NULL);

               SetTimer(hWnd, 3, 1000, NULL);
               ShowWindow(g_button, SW_HIDE);


               InvalidateRect(hWnd, NULL, TRUE);
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

            
            if (g_start == 1) {
                Rectangle(hdc, g_area.left, g_area.top, g_area.right, g_area.bottom);

                Rectangle(hdc, timer.left, timer.top, timer.right, timer.bottom);

                ///내가 이동한 좌표에 아이템이 존재하는지 확인
                if (IntersectRect(&a, &g_me, &g_item))
                {
                    /*g_view = 0;*/
                    g_item.left = rand() % 500;
                    if (g_item.left < g_area.left) {
                        g_item.left = g_area.left;
                    }

                    g_item.top = rand() % 500;
                    if (g_item.top < g_area.top) {
                        g_item.top = g_area.top;
                    }
                    g_item.right = g_item.left + 50;
                    if (g_item.right > g_area.right) {
                        g_item.right = g_area.right;
                        g_item.left = g_item.right - 50;
                    }

                    g_item.bottom = g_item.top + 50;
                    if (g_item.bottom > g_area.bottom) {
                        g_item.bottom = g_area.bottom;
                        g_item.top = g_item.bottom - 50;
                    }
                    g_timer += 100;
                }

                Rectangle(hdc, g_me.left, g_me.top, g_me.right, g_me.bottom);

                Rectangle(hdc, g_you.left, g_you.top, g_you.right, g_you.bottom);

                if (g_view == 1)
                    Rectangle(hdc, g_item.left, g_item.top, g_item.right, g_item.bottom);
            }
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        ///생성한 버튼 제거
       DestroyWindow(g_button);
        
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
