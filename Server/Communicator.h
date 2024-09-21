#pragma once
#include "RequestHandlerFactory.h"
#include <iostream>
#include <map>
#include <thread>
#include <winsock2.h>
#include <exception>
#pragma comment(lib, "Ws2_32.lib")

#define PORT 1306

#define CODE_BUFFER_SIZE 2 // (1 byte length, because the length is convert into hex, 1 * 2 = 2 ==> 2 bytes)
#define LENGTH_BUFFER_SIZE 8 // (4 bytes length, because the length is converted into hex, 4 * 2 = 8 ==> 8 bytes)
#define MESSAGE_BASE 16 // 16 - HEXADECIMAL

class RequestHandlerFactory;

class Communicator
{
public:
	/** Behaves as a constructor */
	static Communicator& getInstance(RequestHandlerFactory& factory_handle)
	{
		static Communicator instance(factory_handle);
		return instance;
	}

	/** Delete copy constructor and assignment operator for singleton */
	Communicator(Communicator const&) = delete;
	void operator=(Communicator const&) = delete;

	/** Destructor (closes server socket) */
	~Communicator();

	/** The function handles the clients' requests (connecting) */
	void startHandleRequests();

	/** Clients getter */
	std::map<SOCKET, IRequestHandler*>& getClients();

	/** General purpose data sending function */
	static void sendData(const SOCKET sc, const std::string message);

private:
	/** Constructor (opens server socket) */
	Communicator(RequestHandlerFactory& factory_handle);

	/** Function handles the conversation between the server and the client */
	void handleNewClient(const SOCKET socket);

	/** Function binds the port and listens to new connections */
	void bindAndListen(const int port);

	/** Function gives the data's code */
	int getCode(const SOCKET socket) const;

	/** Function gives the data's length */
	int getLengthOfData(const SOCKET socket) const;

	/** Function gives the data of the packet */
	std::vector<unsigned char> getData(const SOCKET socket, const int length) const;

	/** Function prints the type of request based on its code */
	void printRequestType(const int code) const;

	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;
};