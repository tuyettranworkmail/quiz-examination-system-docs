#pragma once
#ifndef ATTEMPTANSWER_H
#define ATTEMPTANSWER_H

class AttemptAnswer
{
private:
    int attemptAnswerId;
    int attemptId;
    int questionId;
    int selectedOptionId;
    bool isSaved;

public:
    // Constructor
    AttemptAnswer();
    AttemptAnswer(int aaId, int atId, int qId, int optId);

    // Destructor
    ~AttemptAnswer();

    // Getter
    int getAttemptAnswerId() const;
    int getAttemptId() const;
    int getQuestionId() const;
    int getSelectedOptionId() const;
    bool getIsSaved() const;

    // Setter
    void setAttemptAnswerId(int id);
    void setAttemptId(int id);
    void setQuestionId(int id);
    void setSelectedOptionId(int optionId);
    void setIsSaved(bool saved);

    // Business methods
    void selectAnswer(int optionId); // chọn đáp án
    void autoSave();
};

#endif

