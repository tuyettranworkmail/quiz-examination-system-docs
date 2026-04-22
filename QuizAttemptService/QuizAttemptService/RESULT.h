#pragma once
#ifndef RESULT_H
#define RESULT_H

class Result
{
private:
    int resultId;
    int attemptId;
    int score;

public:
    // Constructor
    Result();
    Result(int rId, int atId, int s);

    // Destructor
    ~Result();

    // Getter
    int getResultId() const;
    int getAttemptId() const;
    int getScore() const;

    // Setter
    void setResultId(int id);
    void setAttemptId(int id);
    void setScore(int s);
};

#endif
