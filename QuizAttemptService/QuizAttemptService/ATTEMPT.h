#pragma once
#ifndef ATTEMPT_H
#define ATTEMPT_H

#include <vector>
#include <string>
#include "ATTEMPTANSWER.h"

class Attempt
{
private:
    int attemptId;
    int userId;
    int quizId;

    bool isSubmitted;
    int score;

    std::vector<AttemptAnswer> answerList;

public:
    // ===================== CONSTRUCTOR =====================
    Attempt();
    Attempt(int atId, int uId, int qzId);
    ~Attempt();

    // ===================== GETTER =====================
    int getAttemptId() const;
    int getUserId() const;
    int getQuizId() const;
    bool getIsSubmitted() const;
    int getScore() const;
    std::vector<AttemptAnswer> getAnswerList() const;

    // ===================== SETTER =====================
    void setAttemptId(int id);
    void setUserId(int id);
    void setQuizId(int id);
    void setIsSubmitted(bool submitted);
    void setScore(int s);

    // ===================== BUSINESS LOGIC =====================
    void addAnswer(const AttemptAnswer& answer);
    void submit();

    // =========================================================
    //  FILE HANDLING
    // =========================================================

    static std::vector<Attempt> loadFromFile(const std::string& path);

    static void saveToFile(const std::string& path, const std::vector<Attempt>& list);

    static void appendToFile(const std::string& path, const Attempt& a);

    static void updateInFile(const std::string& path, const Attempt& a);

    static void deleteFromFile(const std::string& path, int attemptId);

    static std::vector<Attempt> findByUserId(const std::vector<Attempt>& list, int userId);

    // convert giữa object ↔ string (rất quan trọng)
    std::string toLine() const;
    static Attempt fromLine(const std::string& line);
};

#endif