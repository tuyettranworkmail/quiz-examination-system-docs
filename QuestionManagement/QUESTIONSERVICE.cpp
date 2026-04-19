#include "QUESTIONSERVICE.h"
#include <stdexcept>

// ===== ADD QUESTION =====
// Thêm câu hỏi vào danh sách
void QuestionService::addQuestion(std::vector<Question>& questions, const Question& q) {
    questions.push_back(q);
}

// ===== UPDATE QUESTION =====
// Cập nhật nội dung câu hỏi
void QuestionService::updateQuestion(Question& q, const std::string& newContent) {
    q.setContent(newContent);
}

// ===== DELETE QUESTION =====
// Xóa câu hỏi theo ID
void QuestionService::deleteQuestion(std::vector<Question>& questions, int questionId) {
    for (auto it = questions.begin(); it != questions.end(); ++it) {
        if (it->getQuestionId() == questionId) {
            questions.erase(it);
            return;
        }
    }
    throw std::runtime_error("Question not found");
}

// ===== ADD ANSWER =====
// Thêm đáp án vào câu hỏi
void QuestionService::addAnswer(Question& q, const Answer& a) {
    q.addAnswer(a);
}

// ===== REMOVE ANSWER =====
// Xóa đáp án theo ID
void QuestionService::removeAnswer(Question& q, int answerId) {
    q.removeAnswer(answerId);
}

// ===== SET CORRECT ANSWER =====
// Đặt 1 đáp án là đúng (các đáp án khác = false)
void QuestionService::setCorrectAnswer(Question& q, int answerId) {
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

// ===== VALIDATE QUESTION =====
// Kiểm tra câu hỏi hợp lệ:
// - nội dung không rỗng
// - có ít nhất 2 đáp án
// - có đúng 1 đáp án đúng
bool QuestionService::validateQuestion(const Question& q) {
    if (q.getContent().empty()) return false;

    const auto& answers = q.getAnswers();
    if (answers.size() < 2) return false;

    int correctCount = 0;
    for (const auto& a : answers) {
        if (a.isCorrect()) correctCount++;
    }

    return correctCount == 1;
}

// ===== CREATE QUESTION =====
// Tạo câu hỏi mới
Question QuestionService::createQuestion(int id, const std::string& content) {
    if (content.empty()) {
        throw std::runtime_error("Question content is required");
    }

    return Question(id, content);
}