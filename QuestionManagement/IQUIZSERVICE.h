#pragma once
#include <string>
#include "QUIZ.h"
#include "QUESTION.h"

class IQuizService {
public:
    // Tạo quiz
    virtual Quiz createQuiz(int id,
        const std::string& title,
        const std::string& description,
        int timeLimit) = 0;

    // Thêm câu hỏi vào quiz
    virtual void addQuestionToQuiz(Quiz& quiz,
        const Question& question) = 0;

    // Validate quiz theo business rules
    virtual bool validateQuiz(const Quiz& quiz) = 0;

    // Destructor ảo (tránh lỗi khi dùng con trỏ base)
    virtual ~IQuizService() {}
};