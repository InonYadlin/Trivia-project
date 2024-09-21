#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(const std::string username, const SOCKET socket, RoomManager& roomManager, StatisticsManager& statisticsManager, RequestHandlerFactory& factory) : m_user(username, socket), m_roomManager(roomManager), m_statisticsManager(statisticsManager), m_handlerFactory(factory)
{}


bool MenuRequestHandler::isRequestRelevant(const RequestInfo request)
{
	// Check if request is relevant to Menu
	return (request.id == CREATE_ROOM_REQUEST) ||
		(request.id == GET_ROOMS_REQUEST) ||
		(request.id == GET_PLAYERS_IN_ROOM_REQUEST) ||
		(request.id == JOIN_ROOM_REQUEST) ||
		(request.id == GET_PERSONAL_STATISTICS_REQUEST) ||
		(request.id == GET_HIGH_SCORE_REQUEST) ||
		(request.id == LOGOUT_REQUEST) ||
		(request.id == CLIENT_EXIT) ||
		(request.id == ADD_QUESTION_REQUEST); 

}


RequestResult MenuRequestHandler::handleRequest(const RequestInfo request, const SOCKET socket)
{
	try
	{
		// Create room
		if (request.id == CREATE_ROOM_REQUEST) 
		{
			return this->createRoom(request);
		}

		// Get rooms
		else if (request.id == GET_ROOMS_REQUEST) 
		{
			return this->getRooms(request);
		}

		// Get players in room
		else if (request.id == GET_PLAYERS_IN_ROOM_REQUEST) 
		{
			return this->getPlayersInRoom(request);
		}

		// Join room
		else if (request.id == JOIN_ROOM_REQUEST) 
		{
			return this->joinRoom(request);
		}

		// Get statistics
		else if (request.id == GET_PERSONAL_STATISTICS_REQUEST) 
		{
			return this->getPersonalStats(request);
		}

		// Get highscore
		else if (request.id == GET_HIGH_SCORE_REQUEST) 
		{
			return this->getHighScore(request);
		}

		// Logout
		else if (request.id == LOGOUT_REQUEST) 
		{
			return this->signout(request);
		}

		// Add question
		else if (request.id == ADD_QUESTION_REQUEST) 
		{
			return this->addQuestion(request);
		}
	}

	// json error
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


RequestResult MenuRequestHandler::signout(const RequestInfo request) const
{
	LoginManager::getInstance(this->m_handlerFactory.getDataBase()).logout(this->m_user.getUsername());
	LogoutResponse res = { LOGOUT_RESPONSE };
	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createLoginRequestHandler() };
}


RequestResult MenuRequestHandler::getRooms(const RequestInfo request) const
{
	GetRoomsResponse res = { GET_ROOMS_RESPONSE, this->m_roomManager.getRooms() };
	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername(), this->m_user.getSocket()) };
}


RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo request) const
{

	GetPlayersInRoomRequest req = JsonRequestPacketDeserializer::desirializeGetPlayersRequest(request.buffer);

	if (!this->m_roomManager.hasRoom(req.roomId))
	{
		ErrorResponse error_res = { "Room doesn't exist!" };
		return { JsonResponsePacketSerializer::serializeResponse(error_res), (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername(), this->m_user.getSocket()) };
	}

	GetPlayersInRoomResponse res = { GET_PLAYERS_RESPONSE, this->m_roomManager.getRoom(req.roomId).getAllUsers() };
	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername(), this->m_user.getSocket()) };
}


RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo request) const
{
	GetPersonalStatsResponse res = { GET_PERSONAL_STATS_RESPONSE, this->m_statisticsManager.getUserStatistics(this->m_user.getUsername()) };
	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername(), this->m_user.getSocket()) };
}


RequestResult MenuRequestHandler::getHighScore(const RequestInfo request) const
{
	GetHighScoreResponse res = { GET_HIGHSCORE_RESPONSE, this->m_statisticsManager.getHighScore() };
	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername(), this->m_user.getSocket()) };
}


RequestResult MenuRequestHandler::joinRoom(const RequestInfo request) const
{

	JoinRoomRequest req = JsonRequestPacketDeserializer::desirializeJoinRoomRequest(request.buffer);
	ErrorResponse error_res;

	// Check if room exists
	if (this->m_roomManager.hasRoom(req.roomId)) 
	{
		if (this->m_roomManager.getRoom(req.roomId).getMetaData().maxPlayers > this->m_roomManager.getRoom(req.roomId).getAllUsers().size()) // check if room isn't full
		{
			this->m_roomManager.getRoom(req.roomId).addUser(this->m_user);

			JoinRoomResponse res = { JOIN_ROOM_RESPONSE };
			return { JsonResponsePacketSerializer::serializeResponse(res) , (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername(), this->m_user.getSocket()) };
		}

		else
		{
			error_res = { "Room is full!" };
		}
	}

	else
	{
		error_res = { "Room doesn't exist" };
	}

	return { JsonResponsePacketSerializer::serializeResponse(error_res), (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername(), this->m_user.getSocket()) };
}


RequestResult MenuRequestHandler::createRoom(const RequestInfo request) const
{

	CreateRoomRequest req = JsonRequestPacketDeserializer::desirializeCreateRoomRequest(request.buffer);

	int amount_of_questions = this->m_handlerFactory.getDataBase()->getAmountOfQuestions(); // amount of questions in the database

	if (req.maxUsers >= 1 && req.answerTimeout >= 1 && req.questionCount >= 1 && req.questionCount <= amount_of_questions) // check if details are valid
	{
		RoomData room_data = { 0, req.roomName, req.maxUsers, req.questionCount, req.answerTimeout, true };
		this->m_roomManager.createRoom(this->m_user, room_data);
		CreateRoomResponse res = { CREATE_ROOM_RESPONSE };
		return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername(), this->m_user.getSocket()) };
	}

	ErrorResponse error_res = { this->getErrorMessage(req, amount_of_questions) }; // get the proper error message

	return { JsonResponsePacketSerializer::serializeResponse(error_res), (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername(), this->m_user.getSocket()) };
}

RequestResult MenuRequestHandler::addQuestion(const RequestInfo request) const
{
	AddQuestionRequest req = JsonRequestPacketDeserializer::deserializerAddQuestionRequest(request.buffer);
	unsigned int status = FAIL_RESPONSE;

	if ((req.question != "") && (req.c_answer1 != "") && (req.w_answer2 != "") && (req.w_answer3 != "") && (req.w_answer4 != ""))
	{
		this->m_handlerFactory.getDataBase()->addQuestion(req.question, req.c_answer1, req.w_answer2, req.w_answer3, req.w_answer4);
		status = SUCCESS_RESPONSE;
	}

	AddQuestionResponse res = { status };

	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername(), this->m_user.getSocket()) };

}

std::string MenuRequestHandler::getErrorMessage(const CreateRoomRequest req, const int amount_of_questions) const
{
	std::string error_msg = "";

	if (req.maxUsers < 1)
		error_msg = "There should be at least one player!";

	else if (req.answerTimeout < 1)
		error_msg = "Answer time should be at least one second!";

	else if (amount_of_questions == 0)
	{
		error_msg = "There are no questions in the database, add the questions with the 'Add Question' button in the main menu";
	}

	else if (req.questionCount > amount_of_questions)
	{
		error_msg = "Too many questions requested. There are only " + std::to_string(amount_of_questions) + " questions in the database";
	}

	else if (req.questionCount < 1)
		error_msg = "There should be at least one question in the game!";

	return error_msg;
}