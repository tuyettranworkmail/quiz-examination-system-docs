#include "QuizService.h"
#include <stdexcept>

// Tạo Quiz
Quiz QuizService::createQuiz(int id, const std::string& title, const std::string& description, int timeLimit) {
    if (title.empty()) {
        throw std::runtime_error("Title is required");
    }

    if (timeLimit <= 0) {
        throw std::runtime_error("Invalid time limit");
    }

    return Quiz(id, title, description, timeLimit);
}

// Thêm Question vào Quiz
void QuizService::addQuestionToQuiz(Quiz& quiz, const Question& question) {
    quiz.addQuestion(question);
}

// Validate Quiz
bool QuizService::validateQuiz(const Quiz& quiz) {
    if (quiz.getTitle().empty()) return false;

    if (quiz.getTimeLimit() <= 0) return false;

    if (quiz.getQuestions().size() < 1) return false;

    return true;
}