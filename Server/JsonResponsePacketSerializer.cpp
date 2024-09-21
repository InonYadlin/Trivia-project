#include "JsonResponsePacketSerializer.h"

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const ErrorResponse response)
{
	json serializedData = { {"message", response.message} };
	return buildResponse(ERROR_RESPONSE, serializedData.dump());
}


std::vector<char> JsonResponsePacketSerializer::serializeResponse(const LoginResponse response)
{
	json serializedData = { {"status", response.status} };
	return buildResponse(response.status, serializedData.dump());
}


std::vector<char> JsonResponsePacketSerializer::serializeResponse(const SignupResponse response)
{
	json serializedData = { {"status", response.status} };
	return buildResponse(response.status, serializedData.dump());
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const LogoutResponse response)
{
	json serializedData = { {"status", response.status} };
	return buildResponse(response.status, serializedData.dump());
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const GetRoomsResponse response)
{
	json serializedData = { {"status", response.status}, {"Rooms", {}} };

	// Loop which gets all the rooms
	for (auto& room : response.rooms)
	{
		serializedData["Rooms"].push_back({
			{"id", room.id},
			{"name", room.name},
			{"maxPlayers", room.maxPlayers},
			{"numOfQuestionsInGame", room.numOfQuestionsInGame},
			{"timePerQuestion", room.timePerQuestion},
			{"isActive", room.isActive},

			});
	}

	return buildResponse(response.status, serializedData.dump());
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse response)
{
	json serializedData = { {"PlayersInRoom", response.players} };

	return buildResponse(GET_PLAYERS_RESPONSE, serializedData.dump());
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const JoinRoomResponse response)
{
	json serializedData = { {"status", response.status} };

	return buildResponse(response.status, serializedData.dump());
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const CreateRoomResponse response)
{
	json serializedData = { {"status", response.status} };

	return buildResponse(response.status, serializedData.dump());
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const GetPersonalStatsResponse response)
{
	json serializedData = { {"status", response.status} };

	return buildResponse(response.status, serializedData.dump());
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const GetHighScoreResponse response)
{
	json serializedData = { {"status", response.status}, {"HighScores", {}} };

	for (auto& statistics : response.statistics)
	{
		serializedData["HighScores"].push_back({ {"username", statistics.username}, {"score", statistics.score} });
	}

	return buildResponse(response.status, serializedData.dump());
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const CloseRoomResponse response)
{
	json serializedData = { {"status", response.status} };
	return buildResponse(response.status, serializedData.dump());
}


std::vector<char> JsonResponsePacketSerializer::serializeResponse(const StartGameResponse response)
{
	json serializedData = { {"status", response.status} };
	return buildResponse(response.status, serializedData.dump());
}


std::vector<char> JsonResponsePacketSerializer::serializeResponse(const GetRoomStateResponse response)
{
	json serializedData = { {"status", response.status}, {"hasGameBegun", response.hasGameBegun}, {"players", response.players}, {"questionCount", response.questionCount}, {"answerTimeout", response.answerTimeout}, {"maxPlayers", response.maxPlayers} };
	return buildResponse(response.status, serializedData.dump());
}


std::vector<char> JsonResponsePacketSerializer::serializeResponse(const LeaveRoomResponse response)
{
	json serializedData = { {"status", response.status} };
	return buildResponse(response.status, serializedData.dump());
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const AddQuestionResponse response)
{
	json serializedData = { {"status", response.status} };
	return buildResponse(ADD_QUESTION_RESPONSE, serializedData.dump());
}

std::vector<char> JsonResponsePacketSerializer::buildResponse(const int response_code, const std::string serializedData)
{
	// Vector of chars which holds the bytes of the response packet 
	std::vector<char> response_packet_bytes;

	// Add code
	response_packet_bytes.push_back(static_cast<unsigned char>(response_code)); 

	// Convert length to bytes
	std::vector<char> bytes_of_data_len = convertIntToBytes(serializedData.size()); 

	// Add length
	std::copy(bytes_of_data_len.begin(), bytes_of_data_len.end(), std::back_inserter(response_packet_bytes)); 

	// Add data
	std::copy(serializedData.begin(), serializedData.end(), std::back_inserter(response_packet_bytes)); 

	// Returning the packets of the response 
	return response_packet_bytes;
}


std::vector<char> JsonResponsePacketSerializer::convertIntToBytes(const int num)
{
	// Vector of chars which behaves as an array of bytes
	std::vector<char> arrayOfByte(CODE_LENGTH_SIZE);

	// Going over all the bytes and shifting them
	for (int i = 0; i < CODE_LENGTH_SIZE; i++) 
		arrayOfByte[CODE_LENGTH_SIZE - 1 - i] = (num >> (i * SHIFT_BY)); 

	// Returning the array of bytes
	return arrayOfByte;
}