#include "ANSWERSERVICE.h"
#include <stdexcept>

// Thêm đáp án
void AnswerService::addAnswer(Question& question, const Answer& answer) {
    question.addAnswer(answer);
}

// Set đáp án đúng
void AnswerService::setCorrectAnswer(Question& question, int answerId) {
    auto& answers = question.getAnswers();

    bool found = false;

    for (auto& ans : answers) {
        if (ans.getAnswerId() == answerId) {
            ans.setCorrect(true);
            found = true;
        }
        else {
            ans.setCorrect(false); // đảm bảo chỉ 1 correct
        }
    }

    if (!found) {
        throw std::runtime_error("Correct answer is required");
    }
}

// Validate
bool AnswerService::validateAnswers(const Question& question) {
    const auto& answers = question.getAnswers();

    if (answers.size() < 2) return false;

    int correctCount = 0;

    for (const auto& ans : answers) {
        if (ans.isCorrect()) {
            correctCount++;
        }
    }

    if (correctCount != 1) return false;

    return true;
}