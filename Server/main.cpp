#pragma comment (lib, "ws2_32.lib")

#include "Server.h"
#include "WSAInitializer.h"
#include "JsonResponsePacketSerializer.h"
#include "jsonRequestPacketDeserializer.h"
#include "SqliteDB.h"

int main()
{
	try
	{
		// Print info message
		std::cout << "[INFO] Starting..." << std::endl;

		// Initialize wsa
		WSAInitializer wsa_init;

		// Initialize database
		SqliteDataBase* db = &SqliteDataBase::getInstance();

		// Create server structure and run it
		Server::getInstance(db).run();
	}

	catch (const std::exception& e)
	{
		std::cout << "Exception was thrown in function: " << e.what() << std::endl;
	}

	catch (...)
	{
		std::cout << "Unknown exception in main !" << std::endl;
	}
}