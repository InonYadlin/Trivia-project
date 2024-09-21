#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const std::vector<unsigned char> buffer)
{
	// Initializing string to hold data from the buffer
	std::string data(buffer.begin(), buffer.end());

	// Get only the json part
	data = data.substr(data.find('{'));

	// Parse to json
	json jsonData = json::parse(data);

	// Return the login request
	return LoginRequest({ jsonData["username"], jsonData["password"] });
}


SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const std::vector<unsigned char> buffer)
{
	// Initializing string to hold data from the buffer
	std::string data(buffer.begin(), buffer.end());

	// Get only the json part
	data = data.substr(data.find('{'));

	// Parse to json
	json jsonData = json::parse(data);

	// Return the signup request
	return SignupRequest({ jsonData["username"], jsonData["password"], jsonData["email"],
		jsonData["address"], jsonData["phoneNumber"], jsonData["birthDate"] });
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::desirializeGetPlayersRequest(const std::vector<unsigned char> buffer)
{
	// Initializing string to hold data from the buffer
	std::string data(buffer.begin(), buffer.end());

	// Get only the json part
	data = data.substr(data.find('{'));

	// Parse to json
	json jsonData = json::parse(data);

	// Return get players in a room request
	return GetPlayersInRoomRequest({ jsonData["roomId"] });
}


JoinRoomRequest JsonRequestPacketDeserializer::desirializeJoinRoomRequest(const std::vector<unsigned char> buffer)
{
	// Initializing string to hold data from the buffer
	std::string data(buffer.begin(), buffer.end());

	// Get only the json part
	data = data.substr(data.find('{'));

	// Parse to json
	json jsonData = json::parse(data); 

	// Return the join room request
	return JoinRoomRequest({ jsonData["roomId"] });
}


CreateRoomRequest JsonRequestPacketDeserializer::desirializeCreateRoomRequest(const std::vector<unsigned char> buffer)
{
	// Initializing string to hold data from the buffer
	std::string data(buffer.begin(), buffer.end());

	// Get only the json part
	data = data.substr(data.find('{'));

	// Parse to json
	json jsonData = json::parse(data);

	// Return the create room request
	return CreateRoomRequest({ jsonData["roomName"], jsonData["maxUsers"], jsonData["questionCount"], jsonData["answerTimeout"] });
}

AddQuestionRequest JsonRequestPacketDeserializer::deserializerAddQuestionRequest(const std::vector<unsigned char> buffer)
{
	std::string data(buffer.begin(), buffer.end());
	data = data.substr(data.find('{'));// get only the json part

	json jsonData = json::parse(data); // parse to json

	return AddQuestionRequest({ jsonData["question"], jsonData["c_answer1"], jsonData["w_answer2"], jsonData["w_answer3"], jsonData["w_answer4"] });
}