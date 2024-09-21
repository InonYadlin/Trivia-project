#include "Communicator.h"

Communicator::Communicator(RequestHandlerFactory& handlerFactory): m_handlerFactory(handlerFactory)
{
	// Initialize Winsock
	WSADATA wsaData; 
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		// Throw exception 
		throw std::exception("WSAStartup failed");
	}

	// Create a TCP socket
	this->m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->m_serverSocket == INVALID_SOCKET)
	{
		// Throw exception
		throw std::exception("Error creating socket");
	}
	
	// Print info message
	std::cout << "[INFO] Server is up" << std::endl;
}

Communicator::~Communicator()
{
	// Print info message
	std::cout << "[INFO] Closing Server Socket" << std::endl;

	try
	{
		// Close socket
		closesocket(this->m_serverSocket);

		// Deleting clients
		for (auto client = m_clients.begin(); client != m_clients.end(); client++)
		{
			delete[] client->second;
		}
	}

	catch (...) {}
}

void Communicator::startHandleRequests()
{
	// Bind and listen to the port
	bindAndListen(PORT);

	while (true)
	{
		// Accept socket
		SOCKET client_socket = accept(this->m_serverSocket, NULL, NULL);

		// If socket is invalid
		if (client_socket == INVALID_SOCKET)
		{
			// Print info message
			std::cout << "[ERROR] Didn't connect" << std::endl;

			// Throw exception
			throw std::exception(__FUNCTION__);
		}

		// Print info message
		std::cout << "\n[INFO] [" << this->m_clients.size() + 1 << "] client connected. Server and client can speak" << std::endl;

		// Adding new client
		this->m_clients[client_socket] = (IRequestHandler*) new LoginRequestHandler(this->m_handlerFactory.getLoginManager(), this->m_handlerFactory);

		// Create thread
		std::thread clientThread(&Communicator::handleNewClient, this, client_socket);
		clientThread.detach();
	}
}

std::map<SOCKET, IRequestHandler*>& Communicator::getClients()
{
	// Returning the clients
	return this->m_clients;
}

void Communicator::handleNewClient(const SOCKET socket)
{
	while (true)
	{
		try
		{
			int code = this->getCode(socket); // get code of data
			int length = this->getLengthOfData(socket); // get legnth of data
			std::vector<unsigned char> data = this->getData(socket, length); // get data
			std::string data_s(data.begin(), data.end());

			if (code == CLIENT_EXIT)
			{
				if (data_s == "logout") // log's out the user (logout & exit)
				{
					this->printRequestType(code);
					RequestResult response = this->m_clients.find(socket)->second->handleRequest({ static_cast<RequestCode>(LOGOUT_REQUEST), std::time(nullptr), data }, socket);
				}

				closesocket(socket);
				this->m_clients.erase(socket); // remove unactive socket from the map

				std::cout << "[EXIT] Client closed socket!\n" << std::endl;
				return;
			}

			this->printRequestType(code); // print type of request to Console

			RequestInfo request = { static_cast<RequestCode>(code), std::time(nullptr), data }; // create request info

			if (this->m_clients.find(socket)->second == nullptr)
			{
				std::cout << "[ERROR] Couldn't find socket" << std::endl;
			}

			if (this->m_clients.find(socket)->second != nullptr && this->m_clients.find(socket)->second->isRequestRelevant(request))
			{
				RequestResult response = this->m_clients.find(socket)->second->handleRequest(request, socket);

				if (response.newHandler != nullptr) // update the handler only if not NULL
				{
					this->m_clients.find(socket)->second = response.newHandler;
					//current_handler = this->m_clients.find(socket)->second;

				}

				std::string response_s(response.response.begin(), response.response.end());
				if (response_s != "")
				{
					Communicator::sendData(socket, response_s); // send response
					std::cout << "[INFO] Sent response!\n" << std::endl;
				}
			}
			else // not a valid request
			{
				ErrorResponse response = { "Invalid request type!" };
				std::vector<char> error_response = JsonResponsePacketSerializer::serializeResponse(response);
				std::string error_response_s(error_response.begin(), error_response.end());
				Communicator::sendData(socket, error_response_s); // send response
			}
		}

		catch (const std::exception& e)
		{
			std::cout << "[ERROR] Couldn't send message!\n" << std::endl;
			break;
		}
	}

	closesocket(socket);
}


void Communicator::bindAndListen(const int port)
{
	// Preparing to bind socket
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = 0;

	// If socket wasn't binded properly
	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
	{
		// Throw exception
		throw std::exception("bind unsuccessful");
	}

	// Print info message
	std::cout << "[INFO] Binded on port: " << PORT << std::endl;

	// If there was an error in listening to the socket
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		// Throw exception
		throw std::exception("listen unsuccessful");
	}

	// Print info message
	std::cout << "[INFO] Listening..." << std::endl;
}

void Communicator::sendData(const SOCKET sc, const std::string message)
{
	// Convert message to c string
	const char* data = message.c_str();

	// If there was an error in sending the message
	if (send(sc, data, message.size(), 0) == INVALID_SOCKET)
	{
		// Print info message
		throw std::exception("Error while sending message to client");
	}
}

int Communicator::getCode(const SOCKET socket) const
{
	// Getting the code of the message
	char code_buffer[CODE_BUFFER_SIZE]{};
	recv(socket, (char*)&code_buffer, CODE_BUFFER_SIZE, 0);
	unsigned int code = std::stoul(code_buffer, nullptr, MESSAGE_BASE);

	return code;
}


int Communicator::getLengthOfData(const SOCKET socket) const
{
	// Getting the length of the message
	char length_buffer[LENGTH_BUFFER_SIZE]{};
	recv(socket, (char*)&length_buffer, LENGTH_BUFFER_SIZE, 0);
	unsigned int length = std::stoul(length_buffer, nullptr, MESSAGE_BASE);

	return length;
}


std::vector<unsigned char> Communicator::getData(const SOCKET socket, const int length) const
{
	// Plus 1 to include '\0'
	char* data_buffer = new char[length + 1]; 

	// Number of bytes per packet
	const int bytes_per_packet = 2;

	// Recieving the message in a loop
	for (int i = 0; i < length; i = i + bytes_per_packet)
	{
		// Get next bytes - data
		recv(socket, data_buffer + i, bytes_per_packet, 0); 
	}

	// Adding null terminating character
	data_buffer[length] = '\0';

	// Creating a vector
	std::vector<unsigned char> data(data_buffer, data_buffer + length);

	// Deleting the c string
	delete[] data_buffer;

	// Returning the data
	return data;
}

void Communicator::printRequestType(const int code) const
{
	// Printing a message according to the request code

	if (code == LOGIN_REQUEST)
	{
		std::cout << "[INFO] Got Login request!\n" << std::endl;
	}

	else if (code == SIGNUP_REQUEST)
	{
		std::cout << "[INFO] Got Signup request!\n" << std::endl;
	}

	else if (code == CREATE_ROOM_REQUEST)
	{
		std::cout << "[INFO] Got Create Room request!\n" << std::endl;
	}

	else if (code == GET_ROOMS_REQUEST)
	{
		std::cout << "[INFO] Got Get Rooms request!\n" << std::endl;
	}

	else if (code == GET_PLAYERS_IN_ROOM_REQUEST)
	{
		std::cout << "[INFO] Got Get Players In Room request!\n" << std::endl;
	}

	else if (code == JOIN_ROOM_REQUEST)
	{
		std::cout << "[INFO] Got Join Room request!\n" << std::endl;
	}

	else if (code == GET_PERSONAL_STATISTICS_REQUEST)
	{
		std::cout << "[INFO] Got Get Statistics request!\n" << std::endl;
	}

	else if (code == GET_HIGH_SCORE_REQUEST)
	{
		std::cout << "[INFO] Got get high score request!\n" << std::endl;
	}

	else if (code == LOGOUT_REQUEST)
	{
		std::cout << "[INFO] Got Logout request!\n" << std::endl;
	}

	else if (code == CLOSE_ROOM_REQUEST)
	{
		std::cout << "[INFO] Got close room request!\n" << std::endl;
	}

	else if (code == START_GAME_REQUEST)
	{
		std::cout << "[INFO] Got start game request!\n" << std::endl;
	}

	else if (code == GET_ROOM_STATE_REQUEST)
	{
		std::cout << "[INFO] Got get room state request!\n" << std::endl;
	}

	else if (code == LEAVE_ROOM_REQEUST)
	{
		std::cout << "[INFO] Got leave room request!\n" << std::endl;
	}

	else if (code == LEAVE_GAME_REQUEST)
	{
		std::cout << "[INFO] Got leave game request!\n" << std::endl;
	}

	else if (code == GET_QUESTION_REQUEST)
	{
		std::cout << "[INFO] Got get question request!\n" << std::endl;
	}

	else if (code == SUBMIT_ANSWER_REQUEST)
	{
		std::cout << "[INFO] Got submit answer request!\n" << std::endl;
	}

	else if (code == GET_GAME_RESULT_REQUEST)
	{
		std::cout << "[INFO] Got get game result request!\n" << std::endl;
	}

	else if (code == CLIENT_EXIT)
	{
		std::cout << "[INFO] Got client exit request!\n" << std::endl;
	}
}