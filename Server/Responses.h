#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Room.h"

/** List of all response codes */
typedef enum ResponseCode
{
	ERROR_RESPONSE = 101,
	LOGIN_RESPONSE = 102,
	SIGNUP_RESPONSE = 103,
	LOGOUT_RESPONSE = 104,
	GET_ROOMS_RESPONSE = 105,
	GET_PLAYERS_RESPONSE = 106,
	GET_HIGHSCORE_RESPONSE = 107,
	GET_PERSONAL_STATS_RESPONSE = 108,
	JOIN_ROOM_RESPONSE = 109,
	CREATE_ROOM_RESPONSE = 110,
	CLOSE_ROOM_RESPONSE = 111,
	START_GAME_RESPONSE = 112,
	GET_ROOM_RESPONSE = 113,
	LEAVE_ROOM_RESPONSE = 114,
	LEAVE_GAME_RESPONSE = 115,
	GET_QUESTION_RESPONSE = 116,
	SUBMIT_ANSWER_RESPONSE = 117,
	GET_GAME_RESULT_RESPONSE = 118,
	ADD_QUESTION_RESPONSE = 119,
	SUCCESS_RESPONSE = 1,
	FAIL_RESPONSE = 0
} ResponseCode;

/** Highscore structure */
typedef struct Highscore 
{
	std::string username;
	double score;
} Highscore;

/** ErrorResponse structure */
typedef struct ErrorResponse
{
	std::string message;

	void print() const
	{
		std::cout << "ErrorResponse -\nmessage: " + message << std::endl;
	}
} ErrorResponse;

/** LoginResponse structure */
typedef struct LoginResponse
{
	unsigned int status;

	void print() const
	{
		std::cout << "LoginResponse -\nstatus: " + status << std::endl;
	}
} LoginResponse;

/** SignupResponse structure */
typedef struct SignupResponse
{
	unsigned int status;

	void print() const
	{
		std::cout << "SignupResponse -\nstatus: " + status << std::endl;
	}
} SignupResponse;

/** LogoutResponse structure */
typedef struct LogoutResponse
{
	unsigned int status;

	void print() const
	{
		std::cout << "LogoutResponse -\nstatus: " + status << std::endl;
	}
} LogoutResponse;

/** GetRoomsResponse structure */
typedef struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;

	void print() const
	{
		std::cout << "GetRoomsResponse -\nstatus: " + status << std::endl;
	}
} GetRoomsResponse;

/** GetPlayersInRoomResponse structure */
typedef struct GetPlayersInRoomResponse
{
	unsigned int status;
	std::vector<std::string> players;

	void print() const
	{
		std::cout << "GetPlayersInRoomResponse -\nstatus: " + status << std::endl;
	}
} GetPlayersInRoomResponse;

/** GetHighScoreResponse structure */
typedef struct GetHighScoreResponse
{
	unsigned int status;
	std::vector<Highscore> statistics;

	void print() const
	{
		std::cout << "GetHighScoreResponse -\nstatus: " + status << std::endl;
	}
} GetHighScoreResponse;

/** GetPersonalStatsResponse structure */
typedef struct GetPersonalStatsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;

	void print() const
	{
		std::cout << "GetPersonalStatsResponse -\nstatus: " + status << std::endl;
	}
} GetPersonalStatsResponse;

/** JoinRoomResponse structure */
typedef struct JoinRoomResponse
{
	unsigned int status;

	void print() const
	{
		std::cout << "JoinRoomResponse -\nstatus: " + status << std::endl;
	}
} JoinRoomResponse;

/** CreateRoomResponse structure */
typedef struct CreateRoomResponse
{
	unsigned int status;

	void print() const
	{
		std::cout << "CreateRoomResponse -\nstatus: " + status << std::endl;
	}
} CreateRoomResponse;

/** CloseRoomResponse structure */
typedef struct CloseRoomResponse
{
	unsigned int status;

	void print() const
	{
		std::cout << "CloseRoomResponse -\nstatus: " + status << std::endl;
	}
} CloseRoomResponse;

/** StartGameResponse structure */
typedef struct StartGameResponse
{
	unsigned int status;

	void print() const
	{
		std::cout << "StartGameResponse -\nstatus: " + status << std::endl;
	}
} StartGameResponse;

/** GetRoomStateResponse structure */
typedef struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
	unsigned int maxPlayers;

	void print() const
	{
		std::cout << "GetRoomStateResponse -\nstatus: " + status << std::endl;
	}
} GetRoomStateResponse;

/** LeaveRoomResponse structure */
typedef struct LeaveRoomResponse
{
	unsigned int status;

	void print() const
	{
		std::cout << "LeaveRoomResponse -\nstatus: " + status << std::endl;
	}
} LeaveRoomResponse;

/** AddQuestionResponse structure */
typedef struct AddQuestionResponse
{
	unsigned int status;

	void print() const
	{
		std::cout << "AddQuestionResponse -\nstatus: " + status << std::endl;
	}
} AddQuestionResponse;