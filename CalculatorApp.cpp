#define UNICODE
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>


LRESULT CALLBACK wProc(HWND, UINT, WPARAM, LPARAM);
void addMenus(HWND);
void addControls(HWND);
#define FILE_MENU_NEW 20
#define FILE_MENU_OPEN 21
#define FILE_MENU_EXIT 22
#define GENERATE_BUTTON 4
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX  6
#define SEVEN 7
#define EIGHT 8
#define NINE 9
#define ADD 10
#define SUBTRACT 11
#define MULTIPLY 12
#define DIVIDE 13
#define CLEAR 14
#define DELETE 15
#define EQUALS 24
int nums[2], func, result, entryNum, operNum;
wchar_t *numStrings[100], currDisp[10], operButton[10],operators[100], numPressed[2];
bool eq = FALSE;

HWND hName, hAge, hOut, hDisp, hNums[10];
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
   CreateWindowW(L"myWindowClass", L"Calculator", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);
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
            case CLEAR:
               SetWindowTextW(hDisp, nullptr);
               GetWindowText(hDisp, currDisp, 10);
               break;
            case FILE_MENU_EXIT:
               DestroyWindow(hWnd);
               break;
            case FILE_MENU_NEW:
               MessageBeep(MB_ICONINFORMATION);
               break;
            case FILE_MENU_OPEN:
               break;
            case ONE:
            case TWO:
            case THREE:
            case FOUR:
            case FIVE:
            case SIX:
            case SEVEN:
            case EIGHT:
            case NINE:
               //This section takes input from a user and updates the display 
               GetWindowText(hNums[wp - 1], numPressed, 10); //Get button text, store into variable wchar_t array
               if (eq)
               {
                  SetWindowText(hDisp, nullptr); //Clear display
                  eq = 0;
               }
               GetWindowText(hDisp, currDisp, 10); //Get current display text
               wcscat(currDisp, numPressed); //Append button text to display text
               SetWindowText(hDisp, currDisp); //Update display
               break;

            case MULTIPLY:
            case DIVIDE:
            case ADD:
            case SUBTRACT:
               func = wp;
               GetWindowText(hNums[wp - 1], operButton, 10);
               operators[operNum] = *operButton;
               operNum++;
               wcscat(currDisp, operButton); //Append operator to current display
               SetWindowText(hDisp, currDisp); //Update display, should include operator
               eq = FALSE; //lets number cases know not to clear the display
               break;

            case EQUALS:
               eq = 1; //Lets number cases know that there is only a result on the display
               GetWindowText(hDisp, currDisp, 10); //Get current display text
               wchar_t *buffer;
               wchar_t* token = std::wcstok(currDisp, operators, &buffer);
               numStrings[entryNum] = token;
               entryNum++;
               while (token) 
               {
                  std::wcout << token << '\n';
                  token = std::wcstok(nullptr, operators, &buffer);
                  if (token)
                  {
                     numStrings[entryNum] = token;
                     entryNum++;
                  }                  
               }
               entryNum--;
               nums[0] = std::stoi(numStrings[entryNum-1]); //Converting numStrings elements to integers
               nums[1] = std::stoi(numStrings[entryNum]);
               entryNum++;
               if (func == MULTIPLY)
               {
                  result = nums[0] * nums[1];
               }
               else if (func == DIVIDE)
               {
                  result = nums[0] / nums[1];
               }
               else if (func == ADD)
               {
                  result = nums[0] + nums[1];
               }
               else
                  result = nums[0] - nums[1];

               wchar_t resultant[10];
               _itow_s(result, resultant, 10);
               SetWindowTextW(hDisp, resultant);
               numStrings[entryNum] = resultant;
               GetWindowText(hDisp, currDisp, 10);
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

   AppendMenu(hsubMenu, MF_STRING, NULL, L"sub menu item");

   AppendMenu(hfileMenu, MF_STRING, FILE_MENU_NEW, L"New");
   AppendMenu(hfileMenu, MF_POPUP, (UINT)hsubMenu, L"Edit Window");
   AppendMenu(hfileMenu, MF_SEPARATOR, NULL, NULL);
   AppendMenu(hfileMenu, MF_STRING, FILE_MENU_EXIT, L"Exit");
   AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hfileMenu, L"File");
   AppendMenu(hMenu, MF_STRING, NULL, L"Help");
   SetMenu(hWnd, hMenu);
}
void addControls(HWND Hwnd)
{
   //Creating dispay
   hDisp = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT, 50, 10, 400, 50, Hwnd, NULL, NULL, NULL);

   //Creating numeric buttons
   hNums[0] = CreateWindowW(L"Button", L"1", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 75, 75, 75, Hwnd, (HMENU)ONE, NULL, NULL);
   hNums[1] = CreateWindowW(L"Button", L"2", WS_VISIBLE | WS_CHILD | WS_BORDER, 50 + 85, 75, 75, 75, Hwnd, (HMENU)TWO, NULL, NULL);
   hNums[2] = CreateWindowW(L"Button", L"3", WS_VISIBLE | WS_CHILD | WS_BORDER, 50 + 85 + 85, 75, 75, 75, Hwnd, (HMENU)THREE, NULL, NULL);

   hNums[3] = CreateWindowW(L"Button", L"4", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 75 + 85, 75, 75, Hwnd, (HMENU)FOUR, NULL, NULL);
   hNums[4] = CreateWindowW(L"Button", L"5", WS_VISIBLE | WS_CHILD | WS_BORDER, 50 + 85, 75 + 85, 75, 75, Hwnd, (HMENU)FIVE, NULL, NULL);
   hNums[5] = CreateWindowW(L"Button", L"6", WS_VISIBLE | WS_CHILD | WS_BORDER, 50 + 85 + 85, 75 + 85, 75, 75, Hwnd, (HMENU)SIX, NULL, NULL);

   hNums[6] = CreateWindowW(L"Button", L"7", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 75 + 2 * 85, 75, 75, Hwnd, (HMENU)SEVEN, NULL, NULL);
   hNums[7] = CreateWindowW(L"Button", L"8", WS_VISIBLE | WS_CHILD | WS_BORDER, 50 + 85, 75 + 2 * 85, 75, 75, Hwnd, (HMENU)EIGHT, NULL, NULL);
   hNums[8] = CreateWindowW(L"Button", L"9", WS_VISIBLE | WS_CHILD | WS_BORDER, 50 + 85 + 85, 75 + 2 * 85, 75, 75, Hwnd, (HMENU)NINE, NULL, NULL);

   //Creating arithmetic buttons
   hNums[9] = CreateWindowW(L"Button", L"+", WS_VISIBLE | WS_CHILD | WS_BORDER, 310, 160, 75, 75, Hwnd, (HMENU)ADD, NULL, NULL);
   hNums[10]= CreateWindowW(L"Button", L"-", WS_VISIBLE | WS_CHILD | WS_BORDER, 310 + 80, 160, 75, 75, Hwnd, (HMENU)SUBTRACT, NULL, NULL);
   hNums[11] = CreateWindowW(L"Button", L"X", WS_VISIBLE | WS_CHILD | WS_BORDER, 310 + 80, 160 + 80, 75, 75, Hwnd, (HMENU)MULTIPLY, NULL, NULL);
   hNums[12] = CreateWindowW(L"Button", L"/", WS_VISIBLE | WS_CHILD | WS_BORDER, 310, 160 + 80, 75, 75, Hwnd, (HMENU)DIVIDE, NULL, NULL);

   //Creating clear and del buttons
   hNums[13] = CreateWindowW(L"Button", L"Clear", WS_VISIBLE | WS_CHILD | WS_BORDER, 310, 80, 75, 75, Hwnd, (HMENU)CLEAR, NULL, NULL);
   hNums[14] = CreateWindowW(L"Button", L"Del", WS_VISIBLE | WS_CHILD | WS_BORDER, 310+80, 80, 75, 75, Hwnd, (HMENU)DELETE, NULL, NULL);

   //Creating equals button
   CreateWindowW(L"Button", L"=", WS_VISIBLE | WS_CHILD | WS_BORDER, 310, 320, 150, 75, Hwnd, HMENU(EQUALS), NULL, NULL);


}