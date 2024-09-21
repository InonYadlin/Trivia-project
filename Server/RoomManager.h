#pragma once

#include "Room.h"
#include <map>
#include <mutex>

class RoomManager
{
public:
	/** Constructor */
	RoomManager();

	/** Destructor (default) */
	~RoomManager() = default;

	/** Function creates a new room */
	void createRoom(const LoggedUser user, RoomData& room);

	/** Function deletes a room */
	void deleteRoom(const int ID);

	/** Function gives the room's state (active or not) */
	unsigned int getRoomState(const int ID) const;

	/** Function gives all the rooms */
	std::vector<RoomData> getRooms() const;

	/** Function checks if a room with the given id exists */
	bool hasRoom(const int ID) const;

	/** Function gives the room with the given id */
	Room& getRoom(const int ID);

private:
	std::map<unsigned int, Room> m_rooms;
	int lastUsedId;
	mutable std::mutex rooms_mtx;
};