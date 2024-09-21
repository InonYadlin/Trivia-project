#pragma once

#include <WinSock2.h>
#include <Windows.h>

class WSAInitializer
{
public:
	/** Constructor */
	WSAInitializer();

	/** Destructor */
	~WSAInitializer();
};