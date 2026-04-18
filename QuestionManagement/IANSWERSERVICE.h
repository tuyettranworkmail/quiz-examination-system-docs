#pragma once
#include "QUESTION.h"
#include "ANSWER.h"

class IAnswerService {
public:
    // Thêm đáp án
    virtual void addAnswer(Question& question,
        const Answer& answer) = 0;

    // Set đáp án đúng (chỉ 1)
    virtual void setCorrectAnswer(Question& question,
        int answerId) = 0;

    // Validate đáp án
    virtual bool validateAnswers(const Question& question) = 0;

    virtual ~IAnswerService() {}
};