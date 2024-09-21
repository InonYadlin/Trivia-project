#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <vector>
#include <mutex>
#include "LoggedUser.h"

/** RoomData structure */
typedef struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
} RoomData;

class Room
{
public:

	/** Constructor */
	Room(RoomData data);

	/** Copy constructor */
	Room(const Room& room);

	/** Destructor (default) */
	~Room() = default;

	/** Function adds a given user to the room */
	void addUser(const LoggedUser user);

	/** Function removes a given user of the room */
	void removeUser(const LoggedUser user);

	/** Function gives all the users' names in the room */
	std::vector<std::string> getAllUsers() const;

	/** User getter */
	std::vector<LoggedUser> getAllLoggedUsers() const;

	/** MetaData getter  */
	RoomData& getMetaData() const;

private:
	mutable RoomData m_metadata;
	std::vector<LoggedUser> m_users;
	mutable std::mutex users_mtx;
};
