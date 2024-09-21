#include "SqliteDB.h"

#pragma region callbackFunctions
/** Returns to data pointer list of users which the sql data base contains */
int callbackUsers(void* _data, int argc, char** argv, char** azColName)
{
	auto& usersList = *static_cast<std::list<std::string>*>(_data);
	std::string username = "";

	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == USERNAME)
			username = argv[i];
	}

	usersList.push_back(username);
	return 0;
}

/** Returns to data pointer username string which the sql data base contains with the given password record */
int callbackUserPassword(void* _data, int argc, char** argv, char** azColName)
{
	auto& password = *static_cast<std::string*>(_data);

	if (std::string(azColName[0]) == PASSWORD)
		password = argv[0];

	return 0;
}

/** Returns to data pointer list of questions which stored in the database */
int callbackQuestions(void* _data, int argc, char** argv, char** azColName)
{
	auto& questions = *static_cast<std::list<Question>*>(_data);

	std::vector<std::string> wrongAnswers;
	wrongAnswers.clear();

	std::string correctAnswer;
	std::string question;


	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == QUESTION)
			question = argv[i];
		else if (std::string(azColName[i]) == C_ANSWER1)
			correctAnswer = argv[i];
		// Check if string contains "W_ANSWER" (W_ANSWER Substring of W_ANSER2/3/4)
		else if (std::string(azColName[i]).find(W_ANSWER) != std::string::npos)
			wrongAnswers.push_back(argv[i]);
	}

	questions.push_back(Question(question, correctAnswer, wrongAnswers));
	return 0;
}


int callbackFloat(void* _data, int argc, char** argv, char** azColName)
{
	auto& avgTime = *static_cast<float*>(_data);

	if (argc == 1 && argv[0] != nullptr)
	{
		avgTime = std::stof(argv[0]);
		return 0;
	}
	else
		return 1;
}


int callbackInt(void* _data, int argc, char** argv, char** azColName)
{
	auto& avgTime = *static_cast<int*>(_data);

	if (argc == 1 && argv[0] != nullptr)
	{
		avgTime = std::atoi(argv[0]);
		return 0;
	}
	else
		return 1;
}
#pragma endregion


SqliteDataBase::SqliteDataBase()
{
	int fileExist = _access(DB_NAME, 0);
	int res = sqlite3_open(DB_NAME, &this->_db);

	if (res != SQLITE_OK)
	{
		this->_db = nullptr;
		throw std::exception("[SQL ERROR] Can't create database file.");
	}

	// USERS Table
	if (!runQuery("CREATE TABLE IF NOT EXISTS USERS (USERNAME TEXT NOT NULL PRIMARY KEY, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL, ADDRESS TEXT NOT NULL, PHONENUMBER TEXT NOT NULL, BIRTHDATE TEXT NOT NULL);", nullptr, nullptr))
		throw std::exception("[SQL ERROR] Can't create USERS Table.");

	// QUESTIONS Table
	if (!runQuery("CREATE TABLE IF NOT EXISTS QUESTIONS (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, QUESTION TEXT NOT NULL, C_ANSWER1 TEXT NOT NULL, W_ANSWER2 TEXT NOT NULL, W_ANSWER3 TEXT NOT NULL, W_ANSWER4 TEXT NOT NULL);", nullptr, nullptr))
		throw std::exception("[SQL ERROR] Can't create QUESTIONS Table.");

	// STATISTICS Table
	if (!runQuery("CREATE TABLE IF NOT EXISTS STATISTICS (USERNAME TEXT NOT NULL, AVG_TIME FLOAT NOT NULL, C_ANSWERS INTEGER NOT NULL, W_ANSWERS INTEGER NOT NULL, GAMES INTEGER NOT NULL, FOREIGN KEY(USERNAME) REFERENCES USERS(USERNAME));", nullptr, nullptr))
		throw std::exception("[SQL ERROR] Can't create STATISTICS Table.");

	// GAMES Table
	if (!runQuery("CREATE TABLE IF NOT EXISTS GAMES (GAME_ID INTEGER PRIMARY KEY NOT NULL);", nullptr, nullptr))
		throw std::exception("[SQL ERROR] Can't create GAMES Table.");
}


SqliteDataBase::~SqliteDataBase()
{
	sqlite3_close(this->_db);
	this->_db = nullptr;
}

bool SqliteDataBase::doesUserExist(const std::string username)
{
	std::list<std::string> users;
	users.clear();

	std::string query = "SELECT USERNAME FROM USERS WHERE USERNAME = '" + username + "';";
	runQuery(query, callbackUsers, &users);

	return !users.empty();
}


bool SqliteDataBase::doesPasswordMatch(const std::string username, const std::string password)
{
	std::string userPassword;

	std::string query = "SELECT PASSWORD FROM USERS WHERE USERNAME = '" + username + "';";
	runQuery(query, callbackUserPassword, &userPassword);

	return userPassword == password;
}


void SqliteDataBase::addNewUser(const std::string username, const std::string password, const std::string email,
	const std::string address, const std::string phoneNumber, const std::string birthDate)
{
	std::string query = "INSERT INTO USERS (USERNAME, PASSWORD, EMAIL, ADDRESS, PHONENUMBER, BIRTHDATE) VALUES ('" + username + "', '" + password + "', '" + email + "', '"
		+ address + "', '" + phoneNumber + "', '" + birthDate + "');";
	runQuery(query, nullptr, nullptr);

	query = "INSERT INTO STATISTICS (USERNAME, AVG_TIME, C_ANSWERS, W_ANSWERS, GAMES) VALUES ('" + username + "', 0, 0, 0, 0);";
	runQuery(query, nullptr, nullptr);
}


std::list<Question> SqliteDataBase::getQuestions(const int questionsNumber)
{
	std::list<Question> questions;
	questions.clear();

	std::string query = "SELECT * FROM QUESTIONS ORDER BY RANDOM() LIMIT " + std::to_string(questionsNumber) + "; ";
	runQuery(query, callbackQuestions, &questions);

	return questions;
}


int SqliteDataBase::getAmountOfQuestions()
{
	int amount = 0;

	std::string query = "SELECT COUNT(*) FROM QUESTIONS;";
	runQuery(query, callbackInt, &amount);

	return amount;
}


float SqliteDataBase::getPlayerAverageAnswerTime(const std::string username)
{
	float avgTime = 0;

	std::string query = "SELECT AVG_TIME FROM STATISTICS WHERE USERNAME = '" + username + "';";
	runQuery(query, callbackFloat, &avgTime);

	return avgTime;
}


int SqliteDataBase::getNumOfCorrectAnswers(const std::string username)
{
	int correctAnswers = 0;

	std::string query = "SELECT C_ANSWERS FROM STATISTICS WHERE USERNAME = '" + username + "';";
	runQuery(query, callbackInt, &correctAnswers);

	return correctAnswers;
}


int SqliteDataBase::getNumOfWrongAnswers(const std::string username)
{
	int wrongAnswers = 0;

	std::string query = "SELECT W_ANSWERS FROM STATISTICS WHERE USERNAME = '" + username + "';";
	runQuery(query, callbackInt, &wrongAnswers);

	return wrongAnswers;
}


int SqliteDataBase::getNumOfTotalAnswers(const std::string username)
{
	return getNumOfWrongAnswers(username) + getNumOfCorrectAnswers(username);
}


int SqliteDataBase::getNumOfPlayerGames(const std::string username)
{
	int gamesNumber = 0;

	std::string query = "SELECT GAMES FROM STATISTICS WHERE USERNAME = '" + username + "';";
	runQuery(query, callbackInt, &gamesNumber);

	return gamesNumber;
}


void SqliteDataBase::setPlayerAverageAnswerTime(const std::string username, const float new_avg_time)
{
	std::string query = "UPDATE STATISTICS SET AVG_TIME = " + std::to_string(new_avg_time) + " WHERE USERNAME = '" + username + "';";
	runQuery(query, nullptr, nullptr);
}


void SqliteDataBase::setNumOfCorrectAnswers(const std::string username, const int new_correct_answers)
{
	std::string query = "UPDATE STATISTICS SET C_ANSWERS = " + std::to_string(new_correct_answers) + " WHERE USERNAME = '" + username + "';";
	runQuery(query, nullptr, nullptr);
}


void SqliteDataBase::setNumOfWrongAnswers(const std::string username, const int new_wrong_answers)
{
	std::string query = "UPDATE STATISTICS SET W_ANSWERS = " + std::to_string(new_wrong_answers) + " WHERE USERNAME = '" + username + "';";
	runQuery(query, nullptr, nullptr);
}


void SqliteDataBase::setNumOfPlayerGames(const std::string username, const int new_num_games)
{
	std::string query = "UPDATE STATISTICS SET GAMES = " + std::to_string(new_num_games) + " WHERE USERNAME = '" + username + "';";
	runQuery(query, nullptr, nullptr);
}


std::list<std::string> SqliteDataBase::getUsers()
{
	std::list<std::string> users;
	users.clear();

	std::string query = "SELECT * FROM USERS";
	runQuery(query, callbackUsers, &users);

	return users;
}


void SqliteDataBase::addQuestion(const std::string question, const std::string c_answer1, const std::string w_answer2, const std::string w_answer3, const std::string w_answer4)
{
	std::string query = "INSERT INTO QUESTIONS (QUESTION, C_ANSWER1, W_ANSWER2, W_ANSWER3, W_ANSWER4) VALUES ('" + question + "', '" + c_answer1 + "', '" + w_answer2 + "', '" + w_answer3 + "', '" + w_answer4 + "');";
	runQuery(query, nullptr, nullptr);
}


bool SqliteDataBase::runQuery(const std::string query, int (*callback)(void*, int, char**, char**), void* data)
{
	char* errMessage = nullptr;

	bool SQL_OK = sqlite3_exec(this->_db, query.c_str(), callback, data, &errMessage) == SQLITE_OK;

	if (errMessage != nullptr)
		std::cerr << "[SQL ERROR] \"" << errMessage << "\"" << std::endl;

	return SQL_OK; 
}