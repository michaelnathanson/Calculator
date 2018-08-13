#define UNICODE
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>



LRESULT CALLBACK wProc(HWND, UINT, WPARAM, LPARAM);
void addMenus(HWND);
void addControls(HWND);
#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define GENERATE_BUTTON 4


HWND hName, hAge, hOut;
HMENU hMenu;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevinst, LPSTR args, int ncmdshow)
{
   WNDCLASS wc = { 0 };
   wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
   wc.hCursor = LoadCursor(NULL, IDC_ARROW);
   wc.hInstance = hInst;
   wc.lpszClassName = L"myWindowClass";
   wc.lpfnWndProc = wProc;

   if (!RegisterClassW(&wc))
   {
      return -1;
   }
   CreateWindowW(L"myWindowClass", L"Michael's Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);
   MSG msg = { 0 };
   while (GetMessage(&msg, NULL, NULL, NULL))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }

   return 0;
}
LRESULT CALLBACK wProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
   switch (msg)
   {
      case WM_COMMAND:
         switch (wp)
         {
            case FILE_MENU_EXIT:
               DestroyWindow(hWnd);
               break;
            case FILE_MENU_NEW:
               MessageBeep(MB_ICONINFORMATION);
               break;
            case FILE_MENU_OPEN:
               break;
            case GENERATE_BUTTON:
               wchar_t name[30], age[10], out[50];
               GetWindowText(hName, name, 30);
               GetWindowText(hAge, age, 10);
               wcscpy(out, name);
               wcscat(out, L" is ");
               wcscat(out, age);
               wcscat(out, L" years old.");
               SetWindowText(hOut, out);
               break;
         }
         break;
      case WM_CREATE:
         addMenus(hWnd);
         addControls(hWnd);
         break;
      case WM_DESTROY:
         PostQuitMessage(0);
         break;
      default:
         return DefWindowProcW(hWnd, msg, wp, lp);
   }
}
void addMenus(HWND hWnd)
{
   hMenu = CreateMenu();
   HMENU hfileMenu = CreateMenu();
   HMENU hsubMenu = CreateMenu();

   AppendMenu(hsubMenu, MF_STRING,NULL , L"sub menu item");

   AppendMenu(hfileMenu, MF_STRING, FILE_MENU_NEW, L"New");
   AppendMenu(hfileMenu, MF_POPUP, (UINT) hsubMenu, L"Edit Window");
   AppendMenu(hfileMenu, MF_SEPARATOR, NULL, NULL);
   AppendMenu(hfileMenu, MF_STRING, FILE_MENU_EXIT, L"Exit");
   AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hfileMenu, L"File");
   AppendMenu(hMenu, MF_STRING, NULL, L"Help");
   SetMenu(hWnd, hMenu);
}
void addControls(HWND Hwnd)
{
   CreateWindowW(L"Static", L"Name: ", WS_VISIBLE | WS_CHILD, 100, 50, 98, 38, Hwnd, NULL, NULL, NULL);
   hName =  CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 50, 98, 38, Hwnd, NULL, NULL, NULL);

   CreateWindowW(L"Static", L"Age:  ", WS_VISIBLE | WS_CHILD, 100, 90, 98, 38, Hwnd, NULL, NULL, NULL);
   hAge =  CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 90, 98, 38, Hwnd, NULL, NULL, NULL);

   CreateWindowW(L"Button", L"Generate", WS_VISIBLE | WS_CHILD, 150, 140, 98, 38, Hwnd, (HMENU)GENERATE_BUTTON, NULL, NULL);
   hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 200, 300, 200, Hwnd, NULL, NULL, NULL);




}