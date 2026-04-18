#pragma once
#include "QUESTION.h"
#include "ANSWER.h"
#include <vector>
#include <stdexcept>

class QuestionService {
public:
    // Thêm câu hỏi
    void addQuestion(std::vector<Question>& questions, const Question& q);

    // Sửa câu hỏi
    void updateQuestion(Question& q, const std::string& newContent);

    // Xóa câu hỏi
    void deleteQuestion(std::vector<Question>& questions, int questionId);

    // Thêm đáp án
    void addAnswer(Question& q, const Answer& a);

    // Xóa đáp án
    void removeAnswer(Question& q, int answerId);

    // Set đáp án đúng (chỉ 1)
    void setCorrectAnswer(Question& q, int answerId);

    // Validate
    bool validateQuestion(const Question& q);

    Question createQuestion(int id, const std::string& content);
};