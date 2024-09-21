#include "Server.h"

Server::Server(IDatabase* db)
{
	this->m_database = db;
}


void Server::run() const
{
	std::string input = "";

	// Getting request handler factory
	RequestHandlerFactory& handler = RequestHandlerFactory::getInstance(this->m_database);

	// Getting communicator 
	Communicator& communicator = Communicator::getInstance(handler);

	// Creating connector thread
	std::thread t_connector(&Communicator::startHandleRequests, &communicator);

	// Printing info message 
	std::cout << "[INFO] Accepting client..." << std::endl;

	// Detaching the thread
	t_connector.detach();

	while (true)
	{
		std::cin >> input;

		if (input == "EXIT")
			break;
	}
}
