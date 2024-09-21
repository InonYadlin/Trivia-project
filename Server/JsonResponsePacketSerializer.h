#pragma once

#include "Responses.h"
#include <iostream>
#include <vector>
#include <string>
#include "json.hpp"
#include <sstream>
#include <iomanip>

using json = nlohmann::json;

#define CODE_LENGTH_SIZE 4
#define SHIFT_BY 8
#define DIGITS_AFTER_DOT 2
#define C_ANSWER_INDEX 0
#define W_ANSWER_INDEX 1
#define AVG_TIME_INDEX 2

class JsonResponsePacketSerializer
{
public:
	/** Behaves as a constructor */
	static JsonResponsePacketSerializer& getInstance()
	{
		static JsonResponsePacketSerializer instance;
		return instance;
	}

	/** Delete copy constructor and assignment operator for singleton */
	JsonResponsePacketSerializer(JsonResponsePacketSerializer const&) = delete;
	void operator=(JsonResponsePacketSerializer const&) = delete;

	/** Function serializes the response - "ErrorResponse" object into a buffer (vector of char) */
	static std::vector<char> serializeResponse(const ErrorResponse response);

	/** Function serializes the response - "LoginResponse" object into a  buffer (vector of char) */
	static std::vector<char> serializeResponse(const LoginResponse response);

	/** Function serializes the response - "SignupResponse" object into a buffer (vector of char) */
	static std::vector<char> serializeResponse(const SignupResponse response);

	/** Function serializes the response - "LogoutResponse" object into a buffer (vector of char) */
	static std::vector<char> serializeResponse(const LogoutResponse response);

	/** Function serializes the response - "GetRoomsResponse" object into a buffer (vector of char) */
	static std::vector<char> serializeResponse(const GetRoomsResponse response);

	/** Function serializes the response - "GetPlayersInRoomResponse" object into a buffer (vector of char */
	static std::vector<char> serializeResponse(const GetPlayersInRoomResponse response);

	/** Function serializes the response - "JoinRoomResponse" object into a buffer (vector of char) */
	static std::vector<char> serializeResponse(const JoinRoomResponse response);

	/** Function serializes the response - "CreateRoomResponse" object into a buffer (vector of char) */
	static std::vector<char> serializeResponse(const CreateRoomResponse response);

	/** Function serializes the response - "GetPersonalStatsResponse" object into a buffer (vector of char) */
	static std::vector<char> serializeResponse(const GetPersonalStatsResponse response);

	/** Function serializes the response - "GetHighScoreResponse" object into a buffer(vector of char) */
	static std::vector<char> serializeResponse(const GetHighScoreResponse response);

	/** The function serializes the response - "CloseRoomResponse" object into a buffer (vector of char) */
	static std::vector<char> serializeResponse(const CloseRoomResponse response);

	/** The function serializes the response - "StartGameResponse" object into a buffer (vector of char) */
	static std::vector<char> serializeResponse(const StartGameResponse response);

	/** The function serializes the response - "GetRoomStateResponse" object into a buffer(vector of char) */
	static std::vector<char> serializeResponse(const GetRoomStateResponse response);

	/** The function serializes the response - "LeaveRoomResponse" object into a buffer(vector of char) */
	static std::vector<char> serializeResponse(const LeaveRoomResponse response);

	/** Function serializes the response - "AddQuestionResponse" object into a buffer (vector of char) */
	static std::vector<char> serializeResponse(const AddQuestionResponse response);

private:
	/** Constructor */
	JsonResponsePacketSerializer() {}
	
	/** Function builds the response */
	static std::vector<char> buildResponse(const int response_code, const std::string serializedData);

	/** Function converts integer into 4 bytes */
	static std::vector<char> convertIntToBytes(const int num);
};