#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <WinSock2.h>
#include "LoginRequestHandler.h"
#include "Communicator.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"

#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);

class Server
{
public:
	/** Behaves as a constructor */
	static Server& getInstance(IDatabase* db)
	{
		static Server instance(db);
		return instance;
	}

	/** Delete copy constructor and assignment operator for singleton */
	Server(Server const&) = delete;
	void operator=(Server const&) = delete;

	/** Function opens listening thread for connecting with clients */
	void run() const;

private:
	/** Constructor */
	Server(IDatabase* db);

	IDatabase* m_database;
};