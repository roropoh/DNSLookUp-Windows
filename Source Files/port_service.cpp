#include "Header.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: port_to_service
--
-- DATE: January 8, 2014
--
-- DESIGNER: Robin Hsieh A00657820
--
-- PROGRAMMER: Robin Hsieh A00657820
--
-- INTERFACE: char* port_to_service(const char* port, const char* protocol)
--                const char* port: The port number to be searched on
--                const char* protocol: The protocol set by the user
--
-- RETURNS: -
--
-- NOTES:
-- This function prints off the service name when user inputs the port number and the protocol.
------------------------------------------------------------------------------------------------------------------*/
char* port_to_service(const char* port, const char* protocol)
{
	struct servent *sv;
	int s_port;
	char* result = (char*) malloc(MAX_PATH);
	result[0] = '\0';

	WORD wVersionRequested = MAKEWORD(2,2);   
	WSADATA wsaData;                          

	// Open up a Winsock v2.2 session
	WSAStartup(wVersionRequested, &wsaData);

	s_port = atoi(port);

	sv = getservbyport (htons(s_port), protocol);

	if(protocol != "tcp" || protocol != "udp")
	{
		WSACleanup();
		return "error, protocol is invalid";
	}
	if (sv == NULL)
	{
		return "port number is invalid";
	} 

	WSACleanup();

	strcat(result, "The service for port #");
	strcat(result, port);
	strcat(result, " is ");
	strcat(result, sv->s_name);

	return result;
}