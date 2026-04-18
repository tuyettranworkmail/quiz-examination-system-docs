#pragma once
#include <string>
#include <vector>
#include "ANSWER.h"
#include <stdexcept>
class Question {
private:
    int questionId;
    std::string content;
    std::vector<Answer> answers;

public:
    // Constructor
    Question(int id, const std::string& c)
        : questionId(id), content(c) {
    }

    // Getter
    int getQuestionId() const {
        return questionId;
    }

    std::string getContent() const {
        return content;
    }

    std::vector<Answer>& getAnswers() {
        return answers;
    }

    const std::vector<Answer>& getAnswers() const {
        return answers;
    }

    // 
    void setContent(const std::string& newContent) {
        content = newContent;
    }

    void addAnswer(const Answer& answer) {
        answers.push_back(answer);
    }

    //
    void removeAnswer(int answerId) {
        for (auto it = answers.begin(); it != answers.end(); ++it) {
            if (it->getAnswerId() == answerId) {
                answers.erase(it);
                return;
            }
        }
        throw std::runtime_error("Answer not found");
    }
};
