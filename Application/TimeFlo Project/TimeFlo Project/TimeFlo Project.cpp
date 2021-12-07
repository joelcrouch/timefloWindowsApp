// TimeFlo Project.cpp : Defines the entry point for the application.
// Jordan Hyde 2021 
// For use as turn in for fall term 2021 CS300 timeflo project assignment.

#include "windows.h"
#include "framework.h"
#include "TimeFlo Project.h"
#include "CommCtrl.h"
#include "Resource.h"
#pragma comment(lib, "comctl32.lib")
#include "Winuser.h"
#include <ctime>
#include <fstream>
#include <string>


//IDs
#define MAX_LOADSTRING 100
#define START 1001
#define PAUSE 1002
#define STOP 1003
#define SAVE 1004
#define WORKHRS 1005
#define WORKMIN 1006 
#define WORKSEC 1007
#define BREAKHRS 1008
#define BREAKMIN 1009
#define BREAKSEC 1010
#define TIMER 1011
#define WORKBAR 1012
#define BREAKBAR 1013
#define TUTORIAL 1014
#define CLOCK 1015


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
UINT TicksRemaining = 0;						// Remaining number of 1 second timer ticks needed
BOOL BreakFlag = false;							// flag for break period, true = break period should be set next
BOOL PauseFlag = false; 						// flag for when the timer is paused, the timer must be killed in order to stop it from ticking
std::string fileName = "settings.txt";          // default name of the settings.txt file that is found in the TimeFlo project folder

// Forward declarations of functions included in this code module:
ATOM                WindowClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL				TimerStart(HWND hWnd);
VOID 				TickHandler(HWND hWnd);
BOOL				NotifyUser(HWND hWnd);
BOOL                LoadFile(HWND hWnd);
BOOL                WriteFile(HWND hWnd);

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
    LoadStringW(hInstance, IDC_TIMEFLOPROJECT, szWindowClass, MAX_LOADSTRING);
    WindowClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TIMEFLOPROJECT));

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
//  FUNCTION: WindowClass()
//
//  PURPOSE: Registers the window class.
//
ATOM WindowClass (HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TIMEFLOPROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TIMEFLOPROJECT);
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
	
   InitCommonControls();

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   
   //Start Button Contained within 
   
	   HWND hwndStartButton = CreateWindow(L"BUTTON", L"START", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_PUSHBUTTON, 200,500,60,20,hWnd,(HMENU) START,(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),NULL);


   //Pause Button Contained Within
  
	   HWND hwndPauseButton = CreateWindow( L"BUTTON",L"PAUSE", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_PUSHBUTTON,400,500, 60,20, hWnd,(HMENU) PAUSE, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),NULL);
  

   //Stop Button Contained Within
  
	   HWND hwndStopButton = CreateWindow(L"BUTTON", L"STOP", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_PUSHBUTTON ,600,500,60, 20, hWnd, (HMENU) STOP,(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),NULL);
  

   //Trackbars and labels contained within
	   HWND hWndWTLabelEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("static"), TEXT("Work Period, Drag while active to affect remaining time"), WS_CHILD | WS_VISIBLE, 10, 20, 500, 20, hWnd, NULL, NULL, NULL);
	   HWND hwndWorkTrack = CreateWindowEx(WS_EX_WINDOWEDGE, TRACKBAR_CLASS, L"Work Period" , WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_ENABLESELRANGE | TBS_HORZ , 10, 60, 500, 50, hWnd, (HMENU)WORKBAR, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	   HWND hWndBTLabelEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("static"), TEXT("Break Period, Drag while active to affect remaining time"), WS_CHILD | WS_VISIBLE, 10, 120, 500, 20, hWnd, NULL, NULL, NULL);
	   HWND hwndBreakTrack = CreateWindowEx(WS_EX_WINDOWEDGE, TRACKBAR_CLASS, L"Break Period" , WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_ENABLESELRANGE | TBS_HORZ , 10, 160, 500, 50, hWnd, (HMENU)BREAKBAR, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
   

   //Edit Boxes and labels contained within
   {
	   HWND hWndWHLabelEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("static"), TEXT("H"), WS_CHILD | WS_VISIBLE, 600, 20, 40, 20, hWnd, NULL, NULL, NULL);
	   HWND hwndWorkHEdit = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER | WS_BORDER, 600, 60, 40, 20, hWnd, (HMENU)WORKHRS , hInst, NULL);
	   HWND hWndWMLabelEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("static"), TEXT("M"), WS_CHILD | WS_VISIBLE, 660, 20, 40, 20, hWnd, NULL, NULL, NULL);
	   HWND hwndWorkMEdit = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER | WS_BORDER, 660, 60, 40, 20, hWnd, (HMENU)WORKMIN, hInst, NULL);
	   HWND hWndWSLabelEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("static"), TEXT("S"), WS_CHILD | WS_VISIBLE, 720, 20, 40, 20, hWnd, NULL, NULL, NULL);
	   HWND hwndWorkSEdit = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER | WS_BORDER, 720, 60, 40, 20, hWnd, (HMENU)WORKSEC, hInst, NULL);

	   HWND hWndBHLabelEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("static"), TEXT("H"), WS_CHILD | WS_VISIBLE, 600, 140, 40, 20, hWnd, NULL, NULL, NULL);
	   HWND hwndBreakHEdit = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER | WS_BORDER, 600, 160, 40, 20, hWnd, (HMENU)BREAKHRS, hInst, NULL);
	   HWND hWndBMLabelEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("static"), TEXT("M"), WS_CHILD | WS_VISIBLE, 660, 140, 40, 20, hWnd, NULL, NULL, NULL);
	   HWND hwndBreakMEdit = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER | WS_BORDER, 660, 160, 40, 20, hWnd, (HMENU)BREAKMIN, hInst, NULL);
	   HWND hWndBSLabelEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("static"), TEXT("S"), WS_CHILD | WS_VISIBLE, 720, 140, 40, 20, hWnd, NULL, NULL, NULL);
	   HWND hwndBreakSEdit = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER | WS_BORDER, 720, 160, 40, 20, hWnd, (HMENU)BREAKSEC, hInst, NULL);
   }
	//Adds a text with the name Pomodoro Time at the top left corner
   CreateWindow(TEXT("STATIC"), TEXT("POMODORO TIMER"), WS_VISIBLE | WS_CHILD, 0, 0, 150, 20,hWnd, NULL, NULL, NULL);

   //Adds a button to display a quick tutorial on how to use the program
   CreateWindow(TEXT("BUTTON"), TEXT("HOW TO USE"), WS_CHILD| WS_VISIBLE, 160, 0, 160, 20, hWnd, (HMENU)TUTORIAL, NULL, NULL);

   CreateWindow(TEXT("STATIC"), TEXT("00:00:00"), SS_CENTER | WS_CHILD | WS_VISIBLE, 450, 250, 100, 20, hWnd, (HMENU)CLOCK, NULL, NULL);

   if (!hWnd)
   {
      return FALSE;
   }
   if(!LoadFile(hWnd))
   { 
	   // create a popup to signal failed load
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
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {		//ensure messages are being processed in proper order
		case WM_HSCROLL:
		{ 
			switch(LOWORD(wParam))	//default case may be neccessary
			{ 
			case TB_THUMBTRACK:
				int wmId = GetDlgCtrlID((HWND)lParam);
				switch (wmId)
				{
				case WORKBAR:
					if (BreakFlag) TicksRemaining = HIWORD(wParam);
					if (TicksRemaining <= 0) NotifyUser(hWnd);
					break;
				case BREAKBAR:
					if (!BreakFlag) TicksRemaining = HIWORD(wParam);
					if (TicksRemaining <= 0) NotifyUser(hWnd);
					break;
				}
			
			}
	}
	case WM_TIMER:
	{
		int wmId = LOWORD(wParam);
		switch (wmId) //default case may be necessary
		{
		case TIMER:
			TickHandler(hWnd);
			break;
		}
	
	}

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
			{
			case STOP: //STOP
				KillTimer(hWnd, TIMER);
				TicksRemaining = 0; //stop should clear the running timer
				break;

			case PAUSE: // PAUSE
				KillTimer(hWnd, TIMER);
				PauseFlag = true;
				break;

			case START: // START
				if (PauseFlag || TimerStart(hWnd))
				{
					SetTimer(hWnd, TIMER, 1000, NULL); //set the 1 second timer with no call back
					PauseFlag = false; //the pause flag cannot be true when the timer is running
				}
				break;
				
            case IDM_ABOUT: // About dialog box, placed by IDE in project initialization
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case TUTORIAL:
				MessageBox(hWnd, (LPCWSTR)L"H: hours M: minutes S: seconds\nSimply type the desired times into the input boxes under the H,M,S labels and press START!\nSimply press PAUSE during a session and resume anytime by pressing START.", (LPCWSTR)L"HOW TO USE" ,MB_ICONINFORMATION);
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_DESTROY: // case for when the program is exited unexpectedly, or the X button is clicked
		
		if (!WriteFile(hWnd)) // saves settings to file
		{
			// create a popup if this fails
		}
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{ //probably removable, placed in file by IDE project initialization
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


// Function: TimerStart(UINT)
//
//
// Purpose: Set the number of ticks needed by retrieving the user data in the edit boxes

BOOL TimerStart(HWND hWnd)
{

//get edit box values	
	UINT wTime[3];
	UINT bTime[3]; //probably optimizable, for loop at a minimum

	wTime[0] = GetDlgItemInt(hWnd, WORKHRS, NULL, false);
	wTime[1] = GetDlgItemInt(hWnd, WORKMIN, NULL, false);
	wTime[2] = GetDlgItemInt(hWnd, WORKSEC, NULL, false);
	bTime[0] = GetDlgItemInt(hWnd, BREAKHRS, NULL, false);
	bTime[1] = GetDlgItemInt(hWnd, BREAKMIN, NULL, false);
	bTime[2] = GetDlgItemInt(hWnd, BREAKSEC, NULL, false);

	// 

	if (BreakFlag)
	{
		//if the break is next, set the break timer
		TicksRemaining = ((bTime[0] * 60) + bTime[1]) * 60 + bTime[2];
		BreakFlag = false;
		SendDlgItemMessage(hWnd, BREAKBAR, TBM_SETRANGE, TRUE, MAKELPARAM(0, TicksRemaining));
	}
	else
	{
		//otherwise set the work timer
		TicksRemaining = ((wTime[0] * 60) + wTime[1]) * 60 + wTime[2];
		BreakFlag = true;
		SendDlgItemMessage(hWnd, WORKBAR, TBM_SETRANGE, TRUE, MAKELPARAM(0, TicksRemaining));
	}
	//if ticks did not get set to a positive value, the function returns false. this should prevent unintended timer values from being set. 
	if (TicksRemaining > 0) return true;
	else return false;
}

//Function: TickHandler(HWND)
//
//
//Purpose: Called on every timer tick to decrease number of ticks remaining

VOID TickHandler(HWND hWnd)
{
	//decrease the number of remaining ticks
	TicksRemaining--;
	//update the clock timer
	UINT MinutesRemaining = (TicksRemaining / 60);
	UINT HoursRemaining = (MinutesRemaining / 60);
	tm* time = new tm();
	time->tm_hour = HoursRemaining;
	time->tm_min = MinutesRemaining % 60;
	time->tm_sec = TicksRemaining % 60;
	size_t strsize = 40;
	char* ClockString = new char[strsize];
	std::strftime(ClockString, strsize, "%T", time);
	wchar_t* wClockString = new wchar_t[strsize];
	mbstowcs_s(NULL, wClockString, strsize, ClockString, strsize);

	SetWindowText(GetDlgItem(hWnd, CLOCK), (LPCWSTR)wClockString);

	
	//SetWindowText(GetDlgItem(hWnd, CLOCK), );


	//StringCbPrintf(ClockText, HoursRemaining + " : " + MinutesRemaining % 60 + " : " TicksRemaining % 60 );
	
	switch (BreakFlag)
	{
	case true: //if the work period is running, change the work bar
		SendDlgItemMessage(hWnd, WORKBAR, TBM_SETPOS, TRUE, TicksRemaining);
		break;
	case false: //if the break period is running, change the break bar
		SendDlgItemMessage(hWnd, BREAKBAR, TBM_SETPOS, TRUE, TicksRemaining);
		break;

	}
	if (TicksRemaining == 0) { //if there are no more ticks, we have finished counting and should notify the user
		switch (NotifyUser(hWnd))
		{
			case true://if the user chose to go again, then go again
				TimerStart(hWnd);
				break;
			case false:
				break;
		}
	}
	return;
}


//Function: Notify User(HWND)
//
//
//Purpose: Called by the tick handler when the timer runs out, notifies the user using a foreground window
BOOL NotifyUser(HWND hWnd)
{ //This function should be retooled in the event the standard windows notification pattern is implemented
	switch (BreakFlag)
	{
	case true://if the work period is finishing, notify the user to take a break
		Beep(523, 500);
		MessageBox(hWnd,  L"Your Work Period Has Completed, Take A Break!", L"Work Period Complete!", MB_OK | MB_SETFOREGROUND | MB_ICONSTOP);
		return true;
	case false://otherwise, notify the user the break has finished
		Beep(523, 500);
		int query = MessageBox(hWnd,  L"Your Break Period Has Completed, Would You Like To Go Again?", L"Break Period Complete!", MB_YESNO | MB_SETFOREGROUND | MB_ICONSTOP);
		switch (query)//return based on the user's selection in the message box
		{ //the wndproc function still decides whether this means a new timer value is set or not.
			case IDYES:
				return true;
			case IDNO:
				return false;
		}
	}
	
	return false;
}


//Function: LoadFile(HWND)
//
//
//Purpose: When a window is instantiated, check to see if there are timer settings saved in a file
//         otherwise, set values to 0.
BOOL LoadFile(HWND hWnd)
{
	UINT wTime[3] {0,0,0};
	UINT bTime[3] {0,0,0};

	std::ifstream input;
	input.open(fileName);
	if (!input)
	{
		SetDlgItemInt(hWnd, WORKHRS, wTime[0], false);
		SetDlgItemInt(hWnd, WORKMIN, wTime[1], false);
		SetDlgItemInt(hWnd, WORKSEC, wTime[2], false);
		SetDlgItemInt(hWnd, BREAKHRS, bTime[0], false);
		SetDlgItemInt(hWnd, BREAKMIN, bTime[1], false);
		SetDlgItemInt(hWnd, BREAKSEC, bTime[2], false);	
		return false;
	}

	input >> wTime[0];
	input.ignore(10, '|');
	input >> wTime[1];
	input.ignore(10, '|');
	input >> wTime[2];
	input.ignore(10, '|');
	input >> bTime[0];
	input.ignore(10, '|');
	input >> bTime[1];
	input.ignore(10, '|');
	input >> bTime[2];	

	SetDlgItemInt(hWnd, WORKHRS, wTime[0], false);
	SetDlgItemInt(hWnd, WORKMIN, wTime[1], false);
	SetDlgItemInt(hWnd, WORKSEC, wTime[2], false);
	SetDlgItemInt(hWnd, BREAKHRS, bTime[0], false);
	SetDlgItemInt(hWnd, BREAKMIN, bTime[1], false);
	SetDlgItemInt(hWnd, BREAKSEC, bTime[2], false);

	input.close();

	return true;
}

//Function: WriteFile(HWND)
//
//
//Purpose: When program is terminated, save timer settings to 'settings.txt'
BOOL WriteFile(HWND hWnd)
{
	UINT wTime[3];
	UINT bTime[3];
	std::ofstream output;

	output.open(fileName);

	if (!output)
		return false;

	wTime[0] = GetDlgItemInt(hWnd, WORKHRS, NULL, false);
	wTime[1] = GetDlgItemInt(hWnd, WORKMIN, NULL, false);
	wTime[2] = GetDlgItemInt(hWnd, WORKSEC, NULL, false);
	bTime[0] = GetDlgItemInt(hWnd, BREAKHRS, NULL, false);
	bTime[1] = GetDlgItemInt(hWnd, BREAKMIN, NULL, false);
	bTime[2] = GetDlgItemInt(hWnd, BREAKSEC, NULL, false);

	output << wTime[0] << "|" << wTime[1] << "|" << wTime[2] << "|"
		   << bTime[0] << "|" << bTime[1] << "|" << bTime[2];

	output.close();

	return true;
}
