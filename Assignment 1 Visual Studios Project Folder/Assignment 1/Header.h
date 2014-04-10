#ifndef HEADER_H
#define HEADER_H

#include <winsock2.h>
#include <Windows.h>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <cstdio>

#include "resource.h"
#pragma comment(lib, "ws2_32.lib") 
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS

#define ID_CONVERT_BUTTON		1001
#define ID_CONVERT_BUTTON2		1002
#define IDC_TEXT				1003
#define IDC_PROTOCOL_INPUTFIELD 1004
#define IDC_SERVICE_INPUTFIELD	1005

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
void draw_text_title(HDC hdc, int cxChar, int cyChar) ;
char* get_IPaddr(const char* hostname) ;
char* get_hostname(const char* IPaddr) ;
char* port_to_service(const char* port, const char* protocol) ;
char* service_to_port(const char* port, const char* protocol) ;

#endif