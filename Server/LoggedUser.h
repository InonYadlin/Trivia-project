#pragma once

#include <iostream>
#include <WinSock2.h>

class LoggedUser
{
public:
	/** Constructor */
	LoggedUser(const std::string username, const SOCKET socket);

	/** Destructor (default) */
	~LoggedUser() = default;

	/** Username getter */
	std::string getUsername() const;

	/** Function gives the user's socket */
	SOCKET getSocket() const;

	/** Comparison operator */
	bool operator==(const LoggedUser user) const;

	/** Comparison operator */
	bool operator<(const LoggedUser& other) const;

private:
	std::string m_username;
	SOCKET m_socket;
};