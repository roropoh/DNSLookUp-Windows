#include "Header.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: service_to_port
--
-- DATE: January 8, 2014
--
-- DESIGNER: Robin Hsieh A00657820
--
-- PROGRAMMER: Robin Hsieh A00657820
--
-- INTERFACE: char* service_to_port(const char* service, const char* protocol)
--                const char* service: The service name to be searched on
--                const char* protocol: The protocol set by the user
--
-- RETURNS: -
--
-- NOTES:
-- This function prints off the port number when user inputs the service name and the protocol.
------------------------------------------------------------------------------------------------------------------*/
char* service_to_port(const char* service, const char* protocol)
{
	struct servent *sv;
	WORD wVersionRequested = MAKEWORD(2,2);   
	WSADATA wsaData;
	char* result = (char*) malloc(MAX_PATH);
	char* temp = (char*) malloc(10);
	result[0] = '\0';

	// Open up a Winsock v2.2 session
	WSAStartup(wVersionRequested, &wsaData);

	sv = getservbyname (service, protocol);
	if(protocol != "tcp" || protocol != "udp")
	{
		WSACleanup();
		return "error, protocol is invalid";
	}
	if (sv == NULL)
	{
		WSACleanup();
		return "error, service name invalid";
	} 




	itoa(ntohs(sv->s_port), temp, 10);
	strcat(result, "The port number for ");
	strcat(result, service);
	strcat(result, " is: ");
	strcat(result, temp);

	return result;
}