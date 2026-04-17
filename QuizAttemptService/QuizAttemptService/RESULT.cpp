#include "RESULT.h"

// Constructor mặc định
Result::Result()
{
    resultId = 0;
    attemptId = 0;
    score = 0;
}

// Constructor có tham số
Result::Result(int rId, int atId, int s)
{
    resultId = rId;
    attemptId = atId;
    score = s;
}

// Destructor
Result::~Result()
{
}

// Getter
int Result::getResultId() const
{
    return resultId;
}

int Result::getAttemptId() const
{
    return attemptId;
}

int Result::getScore() const
{
    return score;
}

// Setter
void Result::setResultId(int id)
{
    resultId = id;
}

void Result::setAttemptId(int id)
{
    attemptId = id;
}

void Result::setScore(int s)
{
    score = s;
}
