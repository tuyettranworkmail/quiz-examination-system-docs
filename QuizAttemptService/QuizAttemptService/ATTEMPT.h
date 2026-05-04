#pragma once
#ifndef ATTEMPT_H
#define ATTEMPT_H

#include <vector>
#include "ATTEMPTANSWER.h"

class Attempt
{
private:
    int attemptId;
    int userId;
    int quizId;

    bool isSubmitted;   // đã nộp bài chưa
    int score;          // điểm (do GradingService trả về)

    std::vector<AttemptAnswer> answerList; // danh sách câu trả lời

public:
    // Constructor
    Attempt();
    Attempt(int atId, int uId, int qzId);

    // Destructor
    ~Attempt();

    // Getter
    int getAttemptId() const;
    int getUserId() const;
    int getQuizId() const;
    bool getIsSubmitted() const;
    int getScore() const;
    std::vector<AttemptAnswer> getAnswerList() const;

    // Setter
    void setAttemptId(int id);
    void setUserId(int id);
    void setQuizId(int id);
    void setIsSubmitted(bool submitted);
    void setScore(int s);

    // Business methods
    void addAnswer(const AttemptAnswer& answer); // thêm câu trả lời
    void submit();                               // nộp bài
};

#endif
