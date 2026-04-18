#pragma once
#include "QUESTION.h"
#include "ANSWER.h"
#include <vector>

class AnswerService {
public:
    // Thêm đáp án
    void addAnswer(Question& question, const Answer& answer);

    // Set đáp án đúng (chỉ 1)
    void setCorrectAnswer(Question& question, int answerId);

    // Validate danh sách đáp án
    bool validateAnswers(const Question& question);
};