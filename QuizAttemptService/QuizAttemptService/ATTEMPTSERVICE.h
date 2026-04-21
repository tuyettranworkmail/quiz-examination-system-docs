#pragma once
#ifndef ATTEMPTSERVICE_H
#define ATTEMPTSERVICE_H   

#include "ATTEMPT.h"
#include "ATTEMPTANSWER.h"
#include "IGRADINGSERVICE.h"
#include "RESULTSERVICE.h"
#include <vector>
class AttemptService
{
private:
    IGradingService* gradingService;
    ResultService* resultService;    // lưu kết quả

public:
    // Constructor
    AttemptService(IGradingService* gs, ResultService* rs);

    // Use cases
    Attempt startAttempt(int attemptId, int userId, int quizId);

    void saveAnswer(Attempt& attempt, int questionId, int optionId);

    void submitAttempt(Attempt& attempt);
};

#endif