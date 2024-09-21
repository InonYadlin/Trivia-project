#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(const std::string username, const SOCKET socket, RoomManager& roomManager, RequestHandlerFactory& factory, const int roomId) : m_user(username, socket), m_roomManager(roomManager), m_handlerFactory(factory), m_room(roomManager.getRoom(roomId))
{
}


bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo request)
{
	// Check if request is relevant
	return (request.id == LEAVE_ROOM_REQEUST) || (request.id == GET_ROOM_STATE_REQUEST);
}


RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo request, const SOCKET socket)
{
	try
	{
		// Leave room
		if (request.id == LEAVE_ROOM_REQEUST) 
		{
			return this->leaveRoom(request);
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


RequestResult RoomMemberRequestHandler::leaveRoom(const RequestInfo request) const
{
	LeaveRoomResponse res = { LEAVE_ROOM_RESPONSE };

	this->m_roomManager.getRoom(this->m_room.getMetaData().id).removeUser(this->m_user);

	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername(), this->m_user.getSocket()) };
}


RequestResult RoomMemberRequestHandler::getRoomState(const RequestInfo request) const
{
	if (this->m_roomManager.hasRoom(this->m_room.getMetaData().id))
	{
		GetRoomStateResponse res = { GET_ROOM_STATE_REQUEST,
			this->m_roomManager.getRoomState(this->m_room.getMetaData().id),
			this->m_room.getAllUsers(),
			this->m_room.getMetaData().numOfQuestionsInGame,
			this->m_room.getMetaData().timePerQuestion,
			this->m_room.getMetaData().maxPlayers };

		return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user.getUsername(), this->m_user.getSocket(), this->m_room.getMetaData().id) };
	}
	else
	{
		std::vector<char> null_packet;
		null_packet.push_back(static_cast<unsigned char>(' '));
		return { null_packet, (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername(), this->m_user.getSocket()) };
	}
}