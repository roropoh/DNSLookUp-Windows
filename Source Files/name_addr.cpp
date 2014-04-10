#include "Header.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: get_IPaddr
--
-- DATE: January 8, 2014
--
-- DESIGNER: Robin Hsieh A00657820
--
-- PROGRAMMER: Robin Hsieh A00657820
--
-- INTERFACE: char* get_IPaddr(const char* hostname)
--                const char* hostname: The host name to be searched on
--
-- RETURNS: -
--
-- NOTES:
-- This function prints off the IP when the host name is given.
------------------------------------------------------------------------------------------------------------------*/
char* get_IPaddr(const char* hostname)
{
	int        a;
	struct    hostent *hp;
	char    **p;

	WORD wVersionRequested = MAKEWORD(2,2);   
	WSADATA wsaData;
	char* ip_addr = (char*) malloc(1024);
	ip_addr[0] = '\0';

	WSAStartup(wVersionRequested, &wsaData);

	if ((hp = gethostbyname (hostname)) == NULL)     // Host name?
	{
		switch (h_errno)
		{
			WSACleanup();
		case HOST_NOT_FOUND:
			strcat(ip_addr, hostname);
			strcat(ip_addr, ": No such host\r\n");
			return ip_addr;
		case TRY_AGAIN:
			strcat(ip_addr, hostname);
			strcat(ip_addr, ": error, try again later\r\n");
			return ip_addr;
		case NO_RECOVERY:
			strcat(ip_addr, hostname);
			strcat(ip_addr, ": DNS Error\r\n");
			return ip_addr;
		case NO_ADDRESS:
			strcat(ip_addr, ": No IP Address for ");
			strcat(ip_addr, hostname);
			strcat(ip_addr, "\r\n");
			return ip_addr;
		default:
			return "Unknown Error\r\n";
		}
	}

	for (p = hp->h_addr_list; *p != 0; p++)
	{
		struct in_addr in;
		char **q;

		memcpy(&in.s_addr, *p, sizeof (in.s_addr));

		for (q = hp->h_aliases; *q != 0; q++)
		{
			strcat(ip_addr, "Aliases: ");
			strcat(ip_addr, *q);
			strcat(ip_addr, "\r\n");
		}
		strcat(ip_addr, "The IP address for the host ");
		strcat(ip_addr, hostname);
		strcat(ip_addr, " is ");
		strcat(ip_addr, inet_ntoa(in));
		strcat(ip_addr, "\r\n");
	}

	WSACleanup();

	return ip_addr;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: get_hostname
--
-- DATE: January 8, 2014
--
-- DESIGNER: Robin Hsieh A00657820
--
-- PROGRAMMER: Robin Hsieh A00657820
--
-- INTERFACE: char* get_hostname(const char* IPaddr) 
--                const char* IPaddr: The IP address to be searched on
--
-- RETURNS: -
--
-- NOTES:
-- This function prints off the host name when user inputs the IP address.
------------------------------------------------------------------------------------------------------------------*/
char* get_hostname(const char* IPaddr) 
{
	struct	hostent *hp;
	struct	in_addr my_addr, *addr_p;
	char	**p;
	char	ip_address[256];      // String for IP address
	WORD wVersionRequested = MAKEWORD(2,2);   
	WSADATA wsaData;     

	char* result = (char*) malloc(1024);
	result[0] = '\0';

	// Open up a Winsock v2.2 session
	WSAStartup(wVersionRequested, &wsaData);

	addr_p = (struct in_addr*)malloc(sizeof(struct in_addr));
	addr_p = &my_addr;

	if ((inet_addr(IPaddr)) == 0)
	{
		return "error";
	}
	addr_p->s_addr = inet_addr(IPaddr);

	hp = gethostbyaddr((char *)addr_p, PF_INET, sizeof(my_addr));

	if(hp == NULL)
		return "error, host is not available";

	WSACleanup();

	strcat(result, "The host name for the IP address ");
	strcat(result, IPaddr);
	strcat(result, " is ");
	strcat(result, hp->h_name);

	return result;
}