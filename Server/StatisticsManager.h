#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "sqlite3.h"
#include "IDatabase.h"
#include "SqliteDB.h"
#include "Responses.h"
#include <map>

#define AMOUNT_OF_PLAYERS_TO_SHOW 3
#define POINTS_FOR_CORRECT 10
#define POINTS_FOR_WRONG 2
#define C_ANSWER_INDEX 0
#define W_ANSWER_INDEX 1
#define AVG_TIME_INDEX 2

class StatisticsManager
{
public:
	/** Constructor */
	StatisticsManager(IDatabase* db);
	
	/** Function returns vector which sorted by the highest points */
	std::vector<Highscore> getHighScore() const;

	/** Function gets user statistics(wrong answers, correct answers, avg time) */
	std::vector<std::string> getUserStatistics(const std::string username) const;

	/** Function counts the points of the username according his statistics (correct answers, wrong answers and avg time) */
	static double countPoints(const std::vector<std::string> usernameStatistics);

private:
	IDatabase* m_database;
};