#include "WSAInitializer.h"
#include <exception>


WSAInitializer::WSAInitializer()
{
	WSADATA wsa_data = { };
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
		throw std::exception("WSAStartup Failed");
}


WSAInitializer::~WSAInitializer()
{
	// Using a try statement to avoid exceptions in destructor
	try
	{
		WSACleanup();
	}
	catch (...) {}
}