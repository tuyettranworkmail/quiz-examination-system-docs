#pragma once
#include <string>
#include <vector>
#include "QUESTION.h"

class Quiz {
private:
    int quizId;
    std::string title;
    std::string description;
    int timeLimit;
    std::vector<Question> questions;

public:
    Quiz(int id, const std::string& t, const std::string& d, int time)
        : quizId(id), title(t), description(d), timeLimit(time) {
    }

    int getQuizId() const {
        return quizId;
    }

    const std::string& getTitle() const {
        return title;
    }

    // thêm getter description
    const std::string& getDescription() const {
        return description;
    }

    int getTimeLimit() const {
        return timeLimit;
    }

    std::vector<Question>& getQuestions() {
        return questions;
    }

    const std::vector<Question>& getQuestions() const {
        return questions;
    }

    void addQuestion(const Question& q) {
        questions.push_back(q);
    }

    void removeQuestion(int questionId) {
        for (auto it = questions.begin(); it != questions.end(); ++it) {
            if (it->getQuestionId() == questionId) {
                questions.erase(it);
                return;
            }
        }
    }
};