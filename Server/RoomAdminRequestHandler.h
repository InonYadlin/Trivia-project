#pragma once

#include "IRequestHandler.h"
#include "jsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "Requests.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "Communicator.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	/** Constructor */
	RoomAdminRequestHandler(const std::string username, const SOCKET socket, RoomManager& roomManager, RequestHandlerFactory& factory, const int roomId);

	/** Function checks if the request is a login or signup one */
	virtual bool isRequestRelevant(const RequestInfo request) override;

	/** Function gets a request and returns a "RequestResult" object(holds the response) */
	virtual RequestResult handleRequest(const RequestInfo request, const SOCKET socket) override;

private:

	/** The function closes the room */
	RequestResult closeRoom(const RequestInfo request) const;

	/** The function starts the game */
	RequestResult startGame(const RequestInfo request) const;

	/** The function gets the room's state */
	RequestResult getRoomState(const RequestInfo request) const;


	Room& m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};