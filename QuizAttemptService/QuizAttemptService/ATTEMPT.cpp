#include "ATTEMPT.h"

// Constructor mặc định
Attempt::Attempt()
{
    attemptId = 0;
    userId = 0;
    quizId = 0;
    isSubmitted = false;
    score = 0;
}

// Constructor có tham số
Attempt::Attempt(int atId, int uId, int qzId)
{
    attemptId = atId;
    userId = uId;
    quizId = qzId;
    isSubmitted = false;
    score = 0;
}

// Destructor
Attempt::~Attempt()
{
}

// Getter
int Attempt::getAttemptId() const
{
    return attemptId;
}

int Attempt::getUserId() const
{
    return userId;
}

int Attempt::getQuizId() const
{
    return quizId;
}

bool Attempt::getIsSubmitted() const
{
    return isSubmitted;
}

int Attempt::getScore() const
{
    return score;
}

std::vector<AttemptAnswer> Attempt::getAnswerList() const
{
    return answerList;
}

// Setter
void Attempt::setAttemptId(int id)
{
    attemptId = id;
}

void Attempt::setUserId(int id)
{
    userId = id;
}

void Attempt::setQuizId(int id)
{
    quizId = id;
}

void Attempt::setIsSubmitted(bool submitted)
{
    isSubmitted = submitted;
}

void Attempt::setScore(int s)
{
    score = s;
}

// Business methods

// Thêm câu trả lời
void Attempt::addAnswer(const AttemptAnswer& answer)
{
    answerList.push_back(answer);
}

// Submit bài
void Attempt::submit()
{
    if (!isSubmitted)
    {
        isSubmitted = true;
    }
}
