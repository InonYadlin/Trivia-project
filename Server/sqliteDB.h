#pragma once

#include <string>
#include "sqlite3.h"
#include "IDatabase.h"
#include <io.h>
#include <list>

#define DB_NAME "TriviaDB.db"
#define USERNAME "USERNAME"
#define PASSWORD "PASSWORD"
#define QUESTION "QUESTION"
#define C_ANSWER1 "C_ANSWER1"
#define W_ANSWER "W_ANSWER"
#define AVG_TIME "AVG_TIME"

class SqliteDataBase : public IDatabase
{
public:
	/** Static function which behaves like a constructor */
	static SqliteDataBase& getInstance()
	{
		static SqliteDataBase instance;
		return instance;
	}

	/** Delete copy constructor and assignment operator for singleton */
	SqliteDataBase(SqliteDataBase const&) = delete;
	void operator=(SqliteDataBase const&) = delete;

	~SqliteDataBase();

	/** Function will check if the given user exists in the database */
	virtual bool doesUserExist(const std::string username) override;

	/** Function checks if the given password matches the given username's password in the database */
	virtual bool doesPasswordMatch(const std::string username, const std::string password) override;

	
	/** Function adds a new user to the database with the given info */
	virtual void addNewUser(const std::string username, const std::string password, const std::string email,
		const std::string address, const std::string phoneNumber, const std::string birthDate) override;

	/** Function gets the questions from the database(with given amount) */
	virtual std::list<Question> getQuestions(const int questionsNumber) override;

	/** Function gives the amount of questions in the database */
	virtual int getAmountOfQuestions() override;
	
	/** Function gives the average answer time of given player */
	virtual float getPlayerAverageAnswerTime(const std::string username) override;

	/** Function gives the amount of correct answer a given player has */
	virtual int getNumOfCorrectAnswers(const std::string username) override;

	/** Function gets the number of wrong answers */
	virtual int getNumOfWrongAnswers(const std::string username) override;

	/** The function gives the total amount of answers a given player has */
	virtual int getNumOfTotalAnswers(const std::string username) override;

	/** The function gives the amount of games a given player played */
	virtual int getNumOfPlayerGames(const std::string username) override;

	/** Function sets the given player's average answer time to a new given value */
	virtual void setPlayerAverageAnswerTime(const std::string username, const float new_avg_time) override;

	/** Function sets the given player's correct answers count to a new given value */
	virtual void setNumOfCorrectAnswers(const std::string username, const int new_correct_answers) override;

	/** Function sets the given player's wrong answers count to a new given value */
	virtual void setNumOfWrongAnswers(const std::string username, const int new_wrong_answers) override;

	/** Function sets the given player's games count to a new given value */
	virtual void setNumOfPlayerGames(const std::string username, const int new_num_games) override;

	/** Function gives all the users in the database */
	virtual std::list<std::string> getUsers() override;

	/** Fucntion adds the given function to the db */
	virtual void addQuestion(const std::string question, const std::string c_answer1, const std::string w_answer2, const std::string w_answer3, const std::string w_answer4) override;
private:
	/** Constructor */
	SqliteDataBase();

	/** Runs query according the parameters (callback/default) */
	bool runQuery(const std::string query, int (*callback)(void*, int, char**, char**), void* data);

	sqlite3* _db;
};