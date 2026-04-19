#pragma once
#include "QUIZ.h"
#include "QUESTION.h"
#include <string>

class QuizService {
public:
    // Tạo Quiz
    Quiz createQuiz(int id, const std::string& title,
        const std::string& description, int timeLimit);

    // Thêm Question vào Quiz
    void addQuestionToQuiz(Quiz& quiz, const Question& question);

    // Validate Quiz
    bool validateQuiz(const Quiz& quiz);
};