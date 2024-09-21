#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "IRequestHandler.h"

class IRequestHandler;

/** List of all request codes */
typedef enum RequestCode
{
	LOGIN_REQUEST = 102,
	SIGNUP_REQUEST = 103,
	CREATE_ROOM_REQUEST = 104,
	GET_ROOMS_REQUEST = 105,
	GET_PLAYERS_IN_ROOM_REQUEST = 106,
	JOIN_ROOM_REQUEST = 107,
	GET_PERSONAL_STATISTICS_REQUEST = 108,
	GET_HIGH_SCORE_REQUEST = 109,
	LOGOUT_REQUEST = 110,
	CLOSE_ROOM_REQUEST = 111,
	START_GAME_REQUEST = 112,
	GET_ROOM_STATE_REQUEST = 113,
	LEAVE_ROOM_REQEUST = 114,
	LEAVE_GAME_REQUEST = 115,
	GET_QUESTION_REQUEST = 116,
	SUBMIT_ANSWER_REQUEST = 117,
	GET_GAME_RESULT_REQUEST = 118,
	ADD_QUESTION_REQUEST = 119,
	CLIENT_EXIT = 199

} RequestCode;

/** LoginRequest structure */
typedef struct LoginRequest
{
	std::string username;
	std::string password;

	void print() const
	{
		std::cout << "LoginRequest - \nusername: " + username + "\npassword: " + password << std::endl;
	}

} LoginRequest;

/** SignupRequest structure */
typedef struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
	std::string address;
	std::string phoneNumber;
	std::string birthDate;

	void print() const
	{
		std::cout << "SignupRequest - \nusername: " + username + "\npassword: " + password + "\nemail: " + email +
			"\naddress: " + address + "\nphone number: " + phoneNumber + "\nbirth date:" + birthDate << std::endl;
	}
} SignupRequest;

/** RequestInfo structure */
typedef struct RequestInfo
{
	RequestCode id;
	time_t receivalTime;
	std::vector<unsigned char> buffer;
} RequestInfo;

/** RequestResult structure */
typedef struct RequestResult
{
	std::vector<char> response;
	IRequestHandler* newHandler;
} RequestResult;

/** GetPlayersInRoomRequest structure */
typedef struct GetPlayersInRoomRequest
{
	unsigned int roomId;

	void print() const
	{
		std::cout << "GetPlayersInRoomRequest - \roomId: " + roomId << std::endl;
	}
} GetPlayersInRoomRequest;

/** JoinRoomRequest structure */
typedef struct JoinRoomRequest
{
	unsigned int roomId;

	void print() const
	{
		std::cout << "JoinRoomRequest - \roomId: " + roomId << std::endl;
	}
} JoinRoomRequest;

/** CreateRoomRequest structure */
typedef struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;

	void print() const
	{
		std::cout << "CreateRoomRequest - \nroomName: " + roomName + "\nmaxUsers: " + std::to_string(maxUsers) + "\nquestionCount: " + std::to_string(questionCount) +
			"\nanswerTimeout: " + std::to_string(answerTimeout) << std::endl;
	}
} CreateRoomRequest;

/** AddQuestionRequest structure */
typedef struct AddQuestionRequest
{
	std::string question;
	std::string c_answer1;
	std::string w_answer2;
	std::string w_answer3;
	std::string w_answer4;

	void print() const
	{
		std::cout << "AddQuestionRequest - \nquestion: " + question + "\nc_answer1: " + c_answer1 + "\nw_answer2: " + w_answer2 +
			"\nw_answer3: " + w_answer3 + "\nw_answer4: " + w_answer4 << std::endl;
	}
} AddQuestionRequest;