// nexon_app_launcher.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <shellapi.h>
#include "nexon_app_launcher.h"
#include <boost/program_options.hpp>	// arguments

using namespace std;
//using namespace AmqpClient;
namespace opt = boost::program_options;	// arguments

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

bool cvtLPW2stdstring(std::string& s, const LPWSTR pw,
                      UINT codepage = CP_ACP)
{
    bool res = false;
    char* p = 0;
    int bsz;
    bsz = WideCharToMultiByte(codepage,
        0,
        pw,-1,
        0,0,
        0,0);
    if (bsz > 0) {
        p = new char[bsz];
        int rc = WideCharToMultiByte(codepage,
            0,
            pw,-1,
            p,bsz,
            0,0);
        if (rc != 0) {
            p[bsz-1] = 0;
            s = p;
            res = true;
        }
    }
    delete [] p;
    return res;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	/*
	LPWSTR *argv;
	int argc;

	argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	if(NULL == argv)
	{
		wprintf(L"CommandLineToArgvW failed\n");
		return 0;
	}
	else 
	{
		for(int i = 0; i < argc; i++)
		{
			printf("%d: %ws\n", i, argv[i]);

			wchar_t msg[] = L"Hello, world!";
			std::string s("\?");
			//cvtLPW2stdstring(s,msg);
			cvtLPW2stdstring(s, argv[i]);
			
			std::cout << s << std::endl;
		}
	}

	//opt::options_description desc("All options");
	//desc.add_options()
	//	("server", "server role")
	//	("client", "client role")
	//	("help", "help message");
	//	
	//opt::variables_map vm;
	//opt::store(opt::parse_command_line(argc, argv, desc), vm);
	//opt::notify(vm);

	//if (vm.count("help") || vm.size() <=0)
	//{
	//	std::cout << desc << "\n";
	//	return 1;
	//}

	*/

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    TCHAR ProcessName[1024*3];  
    wcscpy(ProcessName, L".\\nw.exe ..\\app ");
    //wcscat(ProcessName, L"--nxl --token=11111");
    wcscat(ProcessName, lpCmdLine);

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Start the child process. 
    if(!CreateProcess(NULL,   // No module name (use command line)
					ProcessName, 
					//argv[1],      // Command line,  maximum length of this string is 32,768 characters,
					NULL,           // Process handle not inheritable
					NULL,           // Thread handle not inheritable
					FALSE,          // Set handle inheritance to FALSE
					0,              // No creation flags
					NULL,           // Use parent's environment block
					NULL,           // Use parent's starting directory 
					&si,            // Pointer to STARTUPINFO structure
					&pi ))          // Pointer to PROCESS_INFORMATION structure
    {
        printf( "CreateProcess failed (%d).\n", GetLastError() );
        return 0;
    }

    // Wait until child process exits.
    //WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles. 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

	// Free memory allocated for CommandLineToArgvW arguments.
	//LocalFree(argv);

	return 0;
}


/*
//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NEXON_APP_LAUNCHER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_NEXON_APP_LAUNCHER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

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
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
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

*/
