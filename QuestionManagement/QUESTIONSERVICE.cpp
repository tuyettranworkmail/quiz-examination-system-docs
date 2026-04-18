#include "QUESTIONSERVICE.h"
#include <stdexcept>

// Add Question
void QuestionService::addQuestion(std::vector<Question>& questions, const Question& q) {
    if (q.getContent().empty()) {
        throw std::runtime_error("Question content is required");
    }
    questions.push_back(q);
}

// Update Question
void QuestionService::updateQuestion(Question& q, const std::string& newContent) {
    if (newContent.empty()) {
        throw std::runtime_error("Question content is required");
    }
    q.setContent(newContent);
}

// Delete Question
void QuestionService::deleteQuestion(std::vector<Question>& questions, int questionId) {
    for (auto it = questions.begin(); it != questions.end(); ++it) {
        if (it->getQuestionId() == questionId) {
            questions.erase(it);
            return;
        }
    }
    throw std::runtime_error("Question not found");
}

// Add Answer
void QuestionService::addAnswer(Question& q, const Answer& a) {
    q.addAnswer(a);
}

// Remove Answer
void QuestionService::removeAnswer(Question& q, int answerId) {
    q.removeAnswer(answerId);
}

// Set Correct Answer (chỉ 1 đáp án đúng)
void QuestionService::setCorrectAnswer(Question& q, int answerId) {
    auto answers = q.getAnswers();

    bool found = false;

    for (auto& a : answers) {
        if (a.getAnswerId() == answerId) {
            a.setCorrect(true);
            found = true;
        }
        else {
            a.setCorrect(false);
        }
    }

    if (!found) {
        throw std::runtime_error("Answer not found");
    }

    
    void QuestionService::setCorrectAnswer(Question & q, int answerId) {
        auto& answers = q.getAnswers();

        bool found = false;

        for (auto& a : answers) {
            if (a.getAnswerId() == answerId) {
                a.setCorrect(true);
                found = true;
            }
            else {
                a.setCorrect(false);
            }
        }

        if (!found) {
            throw std::runtime_error("Answer not found");
        }
    }

    }
}

// Validate Question
bool QuestionService::validateQuestion(const Question& q) {
    if (q.getContent().empty()) return false;

    auto answers = q.getAnswers();

    if (answers.size() < 2) return false;

    int correctCount = 0;
    for (const auto& a : answers) {
        if (a.isCorrectAnswer()) correctCount++;
    }

    return correctCount == 1;
}