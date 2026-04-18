#pragma once
#include <string>
#include <vector>
#include "Question.h"

class Quiz {
private:
    int quizId;
    std::string title;
    std::string description;
    int timeLimit;
    std::vector<Question> questions;

public:
    // Constructor
    Quiz(int id, const std::string& t, const std::string& d, int time)
        : quizId(id), title(t), description(d), timeLimit(time) {}

    // Getter
    int getQuizId() const { return quizId; }

    std::string getTitle() const { return title; }

    int getTimeLimit() const { return timeLimit; }

    std::vector<Question>& getQuestions() { return questions; }

    // Add Question
    void addQuestion(const Question& q) {
        questions.push_back(q);
    }

    // Remove Question
    void removeQuestion(int questionId) {
        for (auto it = questions.begin(); it != questions.end(); ++it) {
            if (it->getQuestionId() == questionId) {
                questions.erase(it);
                return;
            }
        }
    }
};