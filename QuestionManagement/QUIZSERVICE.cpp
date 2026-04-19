#include "QUIZSERVICE.h"
#include <stdexcept>

// Tạo Quiz
Quiz QuizService::createQuiz(int id, const std::string& title, const std::string& description, int timeLimit) {
    if (title.empty()) {
        throw std::runtime_error("Title is required");
    }

    if (description.empty()) {
        throw std::runtime_error("Description is required");
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
    // Kiểm tra title
    if (quiz.getTitle().empty()) return false;

    // Kiểm tra description (cần có getter)
    if (quiz.getDescription().empty()) return false;

    // Kiểm tra time
    if (quiz.getTimeLimit() <= 0) return false;

    // Phải có ít nhất 1 câu hỏi
    if (quiz.getQuestions().empty()) return false;

    return true;
}