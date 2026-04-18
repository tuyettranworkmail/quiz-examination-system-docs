#pragma once
#include <string>
#include "QUESTION.h"
#include "ANSWER.h"

class IQuestionService {
public:
    // Tạo câu hỏi
    virtual Question createQuestion(int id,
        const std::string& content) = 0;

    // Thêm đáp án vào câu hỏi
    virtual void addAnswerToQuestion(Question& question,
        const Answer& answer) = 0;

    // Validate câu hỏi
    virtual bool validateQuestion(const Question& question) = 0;

    virtual ~IQuestionService() {}
};