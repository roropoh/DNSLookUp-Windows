/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Source.cpp - An application that will resolve host name to IP address, and vice versa.
--                           As well as resolving service name to port number, vice versa while 
--                              providing the protocol.
--
-- PROGRAM: Assignment 1.exe
--
-- FUNCTIONS:
--     void draw_text_title(HDC hdc, int cxChar, int cyChar) ;
--     char* get_IPaddr(const char* hostname) ;
--     char* get_hostname(const char* IPaddr) ;
--     char* port_to_service(const char* port, const char* protocol) ;
--     char* service_to_port(const char* port, const char* protocol) ;
--
-- DATE: January 8, 2014
--
-- DESIGNER: Robin Hsieh A00657820
--
-- PROGRAMMER: Robin Hsieh A00657820
--
-- NOTES:
-- The program will take in the user input for host name and resolve it to an IP address. As well as if
-- the user provides the IP address, it will resolve the host name.
-- Another functionality of this program is the resolve the service name from/to port number when user
-- provides the protocol.
--
-- Remember to add "WS2_32.Lib" to the project source list.
----------------------------------------------------------------------------------------------------------------------*/

#include "Header.h"
#define STRICT
#define WIN32_LEAN_AND_MEAN


TCHAR szAppName[] = TEXT ("ASSIGNMENT1") ;
HWND        inputField;
HWND        convertButton;
HWND        convertButton2;
HWND        protocol_inputField;
HWND        service_inputField;
HWND		resultBox;


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: WinMain
--
-- DATE: January 8, 2014
--
-- DESIGNER: Robin Hsieh A00657820
--
-- PROGRAMMER: Robin Hsieh A00657820
--
-- INTERFACE: int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
--                HINSTANCE hInst: Handle to the current instance of the program.
--                HINSTANCE hPrevInstance: Handle to the previous instance of the program.
--                LPSTR lspszCmdParam: Command line for the application.
--                int nCmdShow: Control for how the window should be shown.
--
-- RETURNS: Returns the exit value upon exit.
--
-- NOTES:
-- This function is the entry point for a graphical Windows-based application.
------------------------------------------------------------------------------------------------------------------*/
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
					PSTR szCmdLine, int iCmdShow)
{
	HWND     hwnd ;
	MSG      msg ;
	WNDCLASS wndclass ;

	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc   = WndProc ;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = hInstance ;
	wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.lpszMenuName  = szAppName ;
	wndclass.lpszClassName = szAppName ;

	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL, TEXT ("This program requires Windows NT!"),
			szAppName, MB_ICONERROR) ;
		return 0 ;
	}

	hwnd = CreateWindow (szAppName, TEXT ("Robin Hsieh Assignment 1: Winsock 2 API"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600,
		NULL, NULL, hInstance, NULL) ;

	ShowWindow (hwnd, iCmdShow) ;
	UpdateWindow (hwnd) ;

	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg) ;
		DispatchMessage (&msg) ;
	}
	return msg.wParam ;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: WndProc
--
-- DATE: January 8, 2014
--
-- DESIGNER: Robin Hsieh A00657820
--
-- PROGRAMMER: Robin Hsieh A00657820
--
-- INTERFACE: LRESULT CALLBACK WndProc (HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
--                HWND hwnd: Handle to the window
--                UINT Message: The message
--                WPARAM wParam: Parameter
--                LPARAM lParam: Parameter
--
-- RETURNS: 
--
-- NOTES:
-- This function that handles the different type of window messages.
------------------------------------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HMENU        hMenu ;
	static RECT rect;
	static int   cxChar, cyChar ;
	HDC          hdc ;
	PAINTSTRUCT  ps ;

	static TCHAR szBuffer[50] ;

	static char szInput[MAX_PATH] = "";
	static char szProtocolInput[MAX_PATH] = "";
	static char szServiceInput[MAX_PATH] = "";
	static char szPortInput[MAX_PATH] = "";

	char *result = (char*) malloc(260);

	switch (message)
	{

	case WM_COMMAND:
		hMenu = GetMenu (hwnd) ;
		hdc = GetDC (hwnd) ;
		SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT)) ;

		//if(HIWORD(lParam) == HIWORD(convertButton))

		switch(LOWORD(wParam))
		{
		case ID_CONVERT_BUTTON:
			if(GetWindowText(GetDlgItem(hwnd, IDC_TEXT), szInput, 1000) == 0)
			{
				return 0;
			}

			if (isdigit(*szInput))    // Dotted IP?
			{
				result = get_hostname(szInput);
				SetWindowText(resultBox, result);
			}
			else
			{
				result = get_IPaddr(szInput);
				SetWindowText(resultBox, result);
			}
			return 0;

		case ID_CONVERT_BUTTON2:
			GetWindowText(GetDlgItem(hwnd, IDC_PROTOCOL_INPUTFIELD), szProtocolInput, MAX_PATH);
			GetWindowText(GetDlgItem(hwnd, IDC_SERVICE_INPUTFIELD), szPortInput, MAX_PATH);
			GetWindowText(GetDlgItem(hwnd, IDC_SERVICE_INPUTFIELD), szServiceInput, MAX_PATH);

			if (isdigit(*szPortInput))
			{
				result = port_to_service(szPortInput, szProtocolInput);
				SetWindowText(resultBox, result);
			}
			else
			{
				SetWindowText(resultBox, service_to_port(szServiceInput, szProtocolInput));
			}

			return 0;
		}

		ReleaseDC (hwnd, hdc) ;
		ValidateRect (hwnd, &rect) ;

		switch (LOWORD (wParam))
		{               
		case IDM_APP_HELP:
			MessageBox (hwnd, TEXT ("How to use: \nType in IP Address or Host name, \nand this program will convert it for you."),
				szAppName, MB_ICONEXCLAMATION | MB_OK) ;
			return 0 ;

		case IDM_APP_ABOUT:
			MessageBox (hwnd, TEXT ("DNS Conversions\n")
				TEXT ("Robin Hsieh, A00657820"),
				szAppName, MB_ICONINFORMATION | MB_OK) ;
			return 0 ;
		}
		WSACleanup();
		break ;

	case WM_CREATE:
		cxChar = LOWORD (GetDialogBaseUnits ()) ;
		cyChar = HIWORD (GetDialogBaseUnits ()) ;
		hdc = GetDC (hwnd) ;

		inputField = CreateWindow(TEXT("EDIT"), 0, WS_BORDER|WS_CHILD|WS_VISIBLE, cxChar, cyChar*2, 70 * cxChar, cyChar * 4 / 3 , hwnd, (HMENU)IDC_TEXT, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		convertButton = CreateWindow(TEXT("BUTTON"), TEXT("Convert"), WS_BORDER|WS_CHILD|WS_VISIBLE, cxChar, cyChar * 4, 20 * cxChar, 7 * cyChar / 4, hwnd, (HMENU)ID_CONVERT_BUTTON, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		protocol_inputField = CreateWindow(TEXT("EDIT"), 0, WS_BORDER|WS_CHILD|WS_VISIBLE, cxChar, cyChar* 13, 20 * cxChar, cyChar * 4 / 3 , hwnd, (HMENU)IDC_PROTOCOL_INPUTFIELD, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		service_inputField = CreateWindow(TEXT("EDIT"), 0, WS_BORDER|WS_CHILD|WS_VISIBLE, cxChar, cyChar* 10, 20 * cxChar, cyChar * 4 / 3 , hwnd, (HMENU)IDC_SERVICE_INPUTFIELD, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		convertButton2 = CreateWindow(TEXT("BUTTON"), TEXT("Convert"), WS_BORDER|WS_CHILD|WS_VISIBLE, cxChar, cyChar * 15, 20 * cxChar, 7 * cyChar / 4, hwnd, (HMENU)ID_CONVERT_BUTTON2, ((LPCREATESTRUCT)lParam)->hInstance, 0);

		resultBox  = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), NULL,
			WS_CHILD | WS_VISIBLE | ES_READONLY | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL, cxChar * 24, 
			4 * cyChar, 375, 450, hwnd, NULL, NULL, NULL);

		break;

	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps) ;
		SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT)) ;
		SetBkMode (hdc, TRANSPARENT) ;

		// Drawing the text for all the titles
		draw_text_title(hdc, cxChar, cyChar);

		ReleaseDC(hwnd, hdc);
		EndPaint (hwnd, &ps) ;
		break ;

	case WM_DESTROY:
		PostQuitMessage (0) ;
		return 0 ;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: draw_text_title
--
-- DATE: January 8, 2014
--
-- DESIGNER: Robin Hsieh A00657820
--
-- PROGRAMMER: Robin Hsieh A00657820
--
-- INTERFACE: void draw_text_title(HDC hdc, int cxChar, int cyChar)
--                HDC hdc: hdc
--                int cxChar: The x-coordinate to be printed.
--                int cyChar: The y-coordinate to be printed.
--
-- RETURNS: -
--
-- NOTES:
-- This function draws the titles in the window.
------------------------------------------------------------------------------------------------------------------*/
void draw_text_title(HDC hdc, int cxChar, int cyChar)
{
	CHAR* ip_host_title = "IP Address/Host Name";
	CHAR* service_port_title = "Service Name/Port #";
	CHAR* protocol_title = "Protocol";
	TextOut(hdc, cxChar, cyChar, ip_host_title, strlen(ip_host_title));
	TextOut(hdc, cxChar, cyChar * 9, service_port_title, strlen(service_port_title));
	TextOut(hdc, cxChar, cyChar * 12, protocol_title, strlen(protocol_title));
}
