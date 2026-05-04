#include "ATTEMPTANSWER.h"

// Constructor mặc định
AttemptAnswer::AttemptAnswer()
{
    attemptAnswerId = 0;
    attemptId = 0;
    questionId = 0;
    selectedOptionId = -1; // chưa chọn
    isSaved = false;
}

// Constructor có tham số
AttemptAnswer::AttemptAnswer(int aaId, int atId, int qId, int optId)
{
    attemptAnswerId = aaId;
    attemptId = atId;
    questionId = qId;
    selectedOptionId = optId;
    isSaved = false;
}

// Destructor
AttemptAnswer::~AttemptAnswer()
{
}

// Getter
int AttemptAnswer::getAttemptAnswerId() const
{
    return attemptAnswerId;
}

int AttemptAnswer::getAttemptId() const
{
    return attemptId;
}

int AttemptAnswer::getQuestionId() const
{
    return questionId;
}

int AttemptAnswer::getSelectedOptionId() const
{
    return selectedOptionId;
}

bool AttemptAnswer::getIsSaved() const
{
    return isSaved;
}

// Setter
void AttemptAnswer::setAttemptAnswerId(int id)
{
    attemptAnswerId = id;
}

void AttemptAnswer::setAttemptId(int id)
{
    attemptId = id;
}

void AttemptAnswer::setQuestionId(int id)
{
    questionId = id;
}

void AttemptAnswer::setSelectedOptionId(int optionId)
{
    selectedOptionId = optionId;
}

void AttemptAnswer::setIsSaved(bool saved)
{
    isSaved = saved;
}

// Business methods
void AttemptAnswer::selectAnswer(int optionId)
{
    // BR: chỉ 1 đáp án 
    selectedOptionId = optionId;

    // khi chọn thì auto save
    autoSave();
}

void AttemptAnswer::autoSave()
{
    // chỉ đánh dấu đã lưu 
    isSaved = true;
}
