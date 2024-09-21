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

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	/** Constructor */
	MenuRequestHandler(const std::string username, const SOCKET socket, RoomManager& roomManager, StatisticsManager& statisticsManager, RequestHandlerFactory& factory);

	/** Function checks if the given request is relevant to the current handler */
	virtual bool isRequestRelevant(const RequestInfo request) override;
	
	/** Function handles the given request */
	virtual RequestResult handleRequest(const RequestInfo request, const SOCKET socket) override;

private:
	/** Function signs out (based on the request) */
	RequestResult signout(const RequestInfo request) const;

	/** Function gets all the rooms */
	RequestResult getRooms(const RequestInfo request) const;

	/** Function gets all the players in a room (based on the request) */
	RequestResult getPlayersInRoom(const RequestInfo request) const;

	/** Function gets all the personal statistics of a user */
	RequestResult getPersonalStats(const RequestInfo request) const;

	/** Function gets the highscore table (first 5 users with the hightes scores) */
	RequestResult getHighScore(const RequestInfo request) const;

	/** Function tries to enter into a room (based on the request) */
	RequestResult joinRoom(const RequestInfo request) const;

	/** Function tries to create a room (based on the request) */
	RequestResult createRoom(const RequestInfo request) const;

	/** The function adds a question to the database */
	RequestResult addQuestion(const RequestInfo request) const;

	/** Function gives the proper error message */
	std::string getErrorMessage(const CreateRoomRequest req, const int amount_of_questions) const;

	LoggedUser m_user;
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;
	RequestHandlerFactory& m_handlerFactory;
};