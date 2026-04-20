#pragma once
#include <vector>
#include <string>
#include "../../QuizAttemptService/QuizAttemptService/IGRADINGSERVICE.h"

using namespace std;

class GradingService : public IGradingService
{
public:
    int gradeAttempt(const Attempt& attempt) override;
};