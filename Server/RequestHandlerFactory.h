#pragma once

#include "IRequestHandler.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"
#include "RoomManager.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomMemberRequestHandler;
class RoomAdminRequestHandler;

class RequestHandlerFactory
{
public:
	/** Behaves as a constructor */
	static RequestHandlerFactory& getInstance(IDatabase* db)
	{
		static RequestHandlerFactory instance(db);
		return instance;
	}

	/** Delete copy constructor and assignment operator for singleton */
	RequestHandlerFactory(RequestHandlerFactory const&) = delete;
	void operator=(RequestHandlerFactory const&) = delete;

	/** Destructor */
	~RequestHandlerFactory();

	/** Database getter */
	IDatabase* getDataBase();

	/** LoginManager getter */
	LoginManager& getLoginManager();

	/** StatisticsManager getter */
	StatisticsManager& getStatisticsManager();

	/** RoomManager Getter */
	RoomManager& getRoomManager();

	/** The function creates a "LoginRequestHandler" object */
	LoginRequestHandler* createLoginRequestHandler();

	/** The function creates a "MenuRequestHandler" object */
	MenuRequestHandler* createMenuRequestHandler(const std::string username, const SOCKET socket);

	/** The function creates a "RoomAdminRequestHandler" object */
	RoomAdminRequestHandler* createRoomAdminRequestHandler(const std::string username, const SOCKET socket, const int roomId);

	/** The function creates a "RoomMemberRequestHandler" object */
	RoomMemberRequestHandler* createRoomMemberRequestHandler(const std::string username, const SOCKET socket, const int roomId);

private:

	/** Constructor */
	RequestHandlerFactory(IDatabase* db);

	IDatabase* m_database;
	RoomManager m_roomManager;
	StatisticsManager m_StatisticsManager;
};