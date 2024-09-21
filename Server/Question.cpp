#include "Question.h"

Question::Question(const std::string question, const std::string correctAnswer, const std::vector<std::string> wrongAnswers)
{
    // Set up the question
    this->m_question = question; 

    // Insert correct answer (1)
    this->m_possibleAnswers.push_back(correctAnswer); 

    // Insert wrong answers (2,3,4)
    this->m_possibleAnswers.insert(this->m_possibleAnswers.end(), wrongAnswers.begin(), wrongAnswers.end()); 
}


std::string Question::getQuestion() const
{
    return this->m_question;
}


std::vector<std::string> Question::getPossibleAnswers() const
{
    return this->m_possibleAnswers;
}


std::string Question::getCorrectAnswer() const
{
    return this->m_possibleAnswers[0];
}


bool Question::operator==(const Question& other) const
{
    return this->m_question == other.m_question;
}