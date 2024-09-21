#pragma once

#include <iostream>
#include <vector>
#include <string>

class Question
{
public:
	/** Constructor (default) */
	Question() = default;

	/** Constructor with parameters */
	Question(const std::string question, const std::string correctAnswer, const std::vector<std::string> wrongAnswers);

	/** Question getter */
	std::string getQuestion() const;

	/** All possible answer getter */
	std::vector<std::string> getPossibleAnswers() const;

	/** Correct answer getter */
	std::string getCorrectAnswer() const;

	/** Comparison operator */
	bool operator==(const Question& other) const;

private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
};