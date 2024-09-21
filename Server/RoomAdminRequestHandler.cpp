#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(const std::string username, const SOCKET socket, RoomManager& roomManager, RequestHandlerFactory& factory, const int roomId) : m_user(username, socket), m_roomManager(roomManager), m_handlerFactory(factory), m_room(roomManager.getRoom(roomId))
{
}


bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo request)
{
	// Check if request is relevant
	return (request.id == CLOSE_ROOM_REQUEST) ||
		(request.id == START_GAME_REQUEST) ||
		(request.id == GET_ROOM_STATE_REQUEST); 
}


RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo request, const SOCKET socket)
{
	try
	{
		// Close room
		if (request.id == CLOSE_ROOM_REQUEST) 
		{
			return this->closeRoom(request);
		}

		// Start rooms
		else if (request.id == START_GAME_REQUEST) 
		{
			return this->startGame(request);
		}

		// Get room state
		else if (request.id == GET_ROOM_STATE_REQUEST) 
		{
			return this->getRoomState(request);
		}
	}

	// JSON error
	catch (nlohmann::json::exception& e) 
	{
		ErrorResponse res = { "[ERROR] Request contains invalid json" };
		return { JsonResponsePacketSerializer::serializeResponse(res), nullptr };
	}

	// Different error
	catch (std::exception& e) 
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::serializeResponse(res), nullptr };
	}
}

RequestResult RoomAdminRequestHandler::closeRoom(const RequestInfo request) const
{
	CloseRoomResponse res = { CLOSE_ROOM_RESPONSE };

	// Send all the players a LEAVE GAME RESPONSE
	for (auto& user : this->m_room.getAllLoggedUsers()) 
	{
		LeaveRoomResponse leave_res = { LEAVE_ROOM_RESPONSE };

		this->m_roomManager.getRoom(this->m_room.getMetaData().id).removeUser(user);


		std::vector<char> serialized_res = JsonResponsePacketSerializer::serializeResponse(leave_res);
		std::string serizlized_res_str(serialized_res.begin(), serialized_res.end());
		Communicator::sendData(user.getSocket(), serizlized_res_str);
	}
	this->m_roomManager.deleteRoom(this->m_room.getMetaData().id);

	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername(), this->m_user.getSocket()) };
}


RequestResult RoomAdminRequestHandler::startGame(const RequestInfo request) const
{
	StartGameResponse res = { START_GAME_RESPONSE };

	// Send all the players a LEAVE GAME RESPONSE
	for (auto& user : this->m_room.getAllLoggedUsers())
	{
		StartGameResponse start_res = { LEAVE_ROOM_RESPONSE };

		this->m_roomManager.getRoom(this->m_room.getMetaData().id).removeUser(user);
		std::vector<char> serialized_res = JsonResponsePacketSerializer::serializeResponse(start_res);
		std::string serizlized_res_str(serialized_res.begin(), serialized_res.end());
		Communicator::sendData(user.getSocket(), serizlized_res_str);
	}

	this->m_room.getMetaData().isActive = 0;

	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername(), this->m_user.getSocket()) };
}


RequestResult RoomAdminRequestHandler::getRoomState(const RequestInfo request) const
{
	GetRoomStateResponse res = { GET_ROOM_STATE_REQUEST,
		this->m_roomManager.getRoomState(this->m_room.getMetaData().id),
		this->m_room.getAllUsers(),
		this->m_room.getMetaData().numOfQuestionsInGame,
		this->m_room.getMetaData().timePerQuestion,
		this->m_room.getMetaData().maxPlayers };

	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createRoomAdminRequestHandler(this->m_user.getUsername(), this->m_user.getSocket(), this->m_room.getMetaData().id) };
}