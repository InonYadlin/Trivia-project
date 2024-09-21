#pragma once

#include <iostream>
#include <string>
#include <list>
#include "Question.h"

class IDatabase
{
public:

	/** Function checks if username exist in the database */
	virtual bool doesUserExist(const std::string username) = 0;

	/** Function checks if the given password matches according the username which the database contains */
	virtual bool doesPasswordMatch(const std::string username, const std::string password) = 0;

	/** Function adds new user into database table */
	virtual void addNewUser(const std::string username, const std::string password, const std::string email, const std::string address, const std::string phoneNumber, const std::string birthDate) = 0;

	/** Function gets the questions from the database(with given amount) */
	virtual std::list<Question> getQuestions(const int questionsNumber) = 0;

	/** Function gets the amount of questions */
	virtual int getAmountOfQuestions() = 0;

	/** Function gives the average answer time of given player */
	virtual float getPlayerAverageAnswerTime(const std::string username) = 0;

	/** Function gives the amount of correct answer a given player has */
	virtual int getNumOfCorrectAnswers(const std::string username) = 0;

	/** Function gives the amount of questions in the database */
	virtual int getNumOfWrongAnswers(const std::string username) = 0;

	/** Function gives the total amount of answers a given player has */
	virtual int getNumOfTotalAnswers(const std::string username) = 0;

	/** Function gives the amount of games a given player played */
	virtual int getNumOfPlayerGames(const std::string username) = 0;

	/** Function sets the given player's average answer time to a new given value */
	virtual void setPlayerAverageAnswerTime(const std::string username, const float new_avg_time) = 0;

	/** Function sets the given player's correct answers count to a new given value */
	virtual void setNumOfCorrectAnswers(const std::string username, const int new_correct_answers) = 0;

	/** Function sets the given player's wrong answers count to a new given value */
	virtual void setNumOfWrongAnswers(const std::string username, const int new_wrong_answers) = 0;

	/** Function sets the given player's games count to a new given value */
	virtual void setNumOfPlayerGames(const std::string username, const int new_num_games) = 0;

	/** Function gives all the users in the database */
	virtual std::list<std::string> getUsers() = 0;

	/** Function adds the given function to the db */
	virtual void addQuestion(const std::string question, const std::string c_answer1, const std::string w_answer2, const std::string w_answer3, const std::string w_answer4) = 0;
};