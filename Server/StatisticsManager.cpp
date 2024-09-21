#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* db) : m_database(db) {}

std::vector<Highscore> StatisticsManager::getHighScore() const
{
    std::vector<Highscore> highestScore;
    std::list<std::string> users = this->m_database->getUsers();

    // <points, username>
    std::multimap<double, std::string> usersStatisticsMap; 

    int counter = 0;

    // Insert into map
    for (auto& user : users)
    {
        usersStatisticsMap.insert({ countPoints(getUserStatistics(user)), user });
    }


    // Push from map into vector (from highest to lowest score)
    for (auto it = usersStatisticsMap.rbegin(); (it != usersStatisticsMap.rend()) && (counter <= AMOUNT_OF_PLAYERS_TO_SHOW); ++it)
    {
        highestScore.push_back({ it->second, it->first });
        counter++;
    }

    return highestScore;
}


double StatisticsManager::countPoints(const std::vector<std::string> usernameStatistics)
{
    double points = 0;

    // Right answers
    points += (std::atoi(usernameStatistics[C_ANSWER_INDEX].c_str()) * POINTS_FOR_CORRECT);

    // Wrong answers
    points -= (std::atoi(usernameStatistics[W_ANSWER_INDEX].c_str()) * POINTS_FOR_WRONG); 

    double averageTime = std::stod(usernameStatistics[AVG_TIME_INDEX]);
    if (averageTime != 0)
        // avg answer time
        points /= std::stod(usernameStatistics[AVG_TIME_INDEX]); 

    // Player can't lose score by playing (only gaining score)
    if (points < 0) 
    {
        return 0;
    }

    return points;
}


std::vector<std::string> StatisticsManager::getUserStatistics(const std::string username) const
{
    std::vector<std::string> user_stats;

    // Get stats
    int right_answers = this->m_database->getNumOfCorrectAnswers(username);
    int total_answers = this->m_database->getNumOfTotalAnswers(username);
    float avg_answer_time = this->m_database->getPlayerAverageAnswerTime(username);

    // Get stats formatted
    user_stats.push_back(std::to_string(right_answers));
    user_stats.push_back(std::to_string(total_answers - right_answers));
    user_stats.push_back(std::to_string(avg_answer_time));

    return user_stats;
}