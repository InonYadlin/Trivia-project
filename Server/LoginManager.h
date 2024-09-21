#pragma once

#include <iostream>
#include <vector>
#include "IDatabase.h"
#include "LoggedUser.h"
#include <string>
#include <regex>
#include <mutex>
#include <unordered_map>
#include <vector>

#define REGEX_PASSWORD R"(^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#?!@$%^&*-])\S{8,}$)"
#define REGEX_EMAIL R"((?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:(2(5[0-5]|[0-4][0-9])|1[0-9][0-9]|[1-9]?[0-9]))\.){3}(?:(2(5[0-5]|[0-4][0-9])|1[0-9][0-9]|[1-9]?[0-9])|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\]))"
#define REGEX_ADDRESS R"(^\([a-zA-Z]+, \d+, [a-zA-Z]+\)$)"
#define REGEX_PHONE_NUMBER R"(^0\d{1,2}\d{7,8}$)"
#define REGEX_BIRTH_DATE R"(^\d{1,2}(\.|\/)\d{1,2}(\.|\/)\d{4}$)"

class LoginManager
{
public:
	/** Behaves as a constructor */
	static LoginManager& getInstance(IDatabase* db)
	{
		static LoginManager instance(db);
		return instance;
	}

	/** Destructor */
	~LoginManager();

	/** Constructor */
	LoginManager(IDatabase* db);
	LoginManager(LoginManager& loginManager);

	/** Logs the given username into the system(if the user isn't already logged in and the password matches the sql record) */
	void login(const std::string username, const std::string password, const SOCKET socket);

	/** Signs the given username into the system and into the database according his data */
	void signup(const std::string username, const std::string password, const std::string email,
		const std::string address, const std::string phoneNumber, const std::string birthDate);

	/** Logging the given username out */
	void logout(const std::string username);

	/** Database getter */
	IDatabase* getDatabase();

private:

	/** Current active database */
	IDatabase* m_database;

	/** Vector(list) of current active logged users */
	static std::vector<LoggedUser> m_loggedUsers;
	std::mutex users_mtx;
};