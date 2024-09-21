#include "Room.h"

Room::Room(RoomData data)
{
	this->m_metadata = data;
}

Room::Room(const Room& room)
{
	this->m_metadata = room.m_metadata;
	this->m_users = room.m_users;
}


void Room::addUser(const LoggedUser user)
{
	this->users_mtx.lock();

	// Check if room full
	if (this->m_users.size() >= this->m_metadata.maxPlayers) 
	{
		this->users_mtx.unlock();
		throw std::exception("[ERROR] Room is full");
	}

	// Check if user already exists in room
	else if (std::find(this->m_users.begin(), this->m_users.end(), user) != this->m_users.end()) 
	{
		this->users_mtx.unlock();
		throw std::exception("[ERROR] User already exists in this room");
	}

	else
	{
		// Add user to room
		this->m_users.push_back(user); 
		this->users_mtx.unlock();
	}
}


void Room::removeUser(const LoggedUser user)
{
	this->users_mtx.lock();

	bool exist = false;
	auto it = this->m_users.begin();

	// Search the user in the vector of users
	while (it != this->m_users.end() && !exist)
	{
		if (it->getUsername() == user.getUsername())
			exist = true;
		else
			it++;
	}

	if (exist)
	{
		// Remove the user from the vector of users
		this->m_users.erase(it); 
		this->users_mtx.unlock();
	}

	else
	{
		this->users_mtx.unlock();
		throw std::exception("[ERROR] This user doesn't exist in this room");
	}
}


std::vector<std::string> Room::getAllUsers() const
{
	this->users_mtx.lock();

	// Get all users and place them in a vector of strings
	std::vector<std::string> userNames = {};
	for (auto const& user : this->m_users)
	{
		userNames.push_back(user.getUsername());
	}

	this->users_mtx.unlock();
	return userNames;
}


std::vector<LoggedUser> Room::getAllLoggedUsers() const
{
	return this->m_users;
}


RoomData& Room::getMetaData() const
{
	return this->m_metadata;
}