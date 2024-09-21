#pragma once

#pragma once

#include "Requests.h"
#include <iostream>
#include <vector>
#include <string>
#include "json.hpp"
#include <sstream>
#include <iomanip>

using json = nlohmann::json;

class JsonRequestPacketDeserializer
{
public:
	/** Behaves as a constructor */
	static JsonRequestPacketDeserializer& getInstance()
	{
		static JsonRequestPacketDeserializer instance;
		return instance;
	}

	/** Delete copy constructor and assignment operator for singleton */
	JsonRequestPacketDeserializer(JsonRequestPacketDeserializer const&) = delete;
	void operator=(JsonRequestPacketDeserializer const&) = delete;

	/** Function deserializes the given buffer - turns it into a "LoginRequest" object */
	static LoginRequest deserializeLoginRequest(const std::vector<unsigned char> buffer);

	/** Function deserializes the given buffer - turns it into a "SignupRequest" object */
	static SignupRequest deserializeSignupRequest(const std::vector<unsigned char> buffer);

	/** Function deserializes the given buffer - turns it into a "GetPlayersInRoomRequest" object */
	static GetPlayersInRoomRequest desirializeGetPlayersRequest(const std::vector<unsigned char> buffer);

	/** Function deserializes the given buffer - turns it into a "JoinRoomRequest" object */
	static JoinRoomRequest desirializeJoinRoomRequest(const std::vector<unsigned char> buffer);

	/** Function deserializes the given buffer - turns it into a "CreateRoomRequest" object */
	static CreateRoomRequest desirializeCreateRoomRequest(const std::vector<unsigned char> buffer);

	/** The function deserializes the given buffer - turns it into a "AddQuestionRequest" object */
	static AddQuestionRequest deserializerAddQuestionRequest(const std::vector<unsigned char> buffer);

private:
	JsonRequestPacketDeserializer() {}
};