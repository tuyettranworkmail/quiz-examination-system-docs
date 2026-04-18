#include <iostream>
#include "QUIZSERVICE.h"
#include "QUESTIONSERVICE.h"
#include "ANSWERSERVICE.h"

using namespace std;

int main() {
    try {
        // Service
        QuizService quizService;
        QuestionService questionService;
        AnswerService answerService;

        // 1. Tạo Quiz
        Quiz quiz = quizService.createQuiz(1, "Math Quiz", "Basic Math", 30);
        cout << "Quiz created: " << quiz.getTitle() << endl;

        // 2. Tạo Question
        Question q1 = questionService.createQuestion(101, "2 + 2 = ?");
        cout << "Question created: " << q1.getContent() << endl;

        // 3. Thêm Answer
        answerService.addAnswer(q1, Answer(1, "3"));
        answerService.addAnswer(q1, Answer(2, "4"));
        answerService.addAnswer(q1, Answer(3, "5"));

        // 4. Set đáp án đúng
        answerService.setCorrectAnswer(q1, 2);

        // 5. Validate Question
        if (!answerService.validateAnswers(q1)) {
            cout << "Invalid answers!" << endl;
            return 0;
        }

        if (!questionService.validateQuestion(q1)) {
            cout << "Invalid question!" << endl;
            return 0;
        }

        // 6. Thêm Question vào Quiz
        quizService.addQuestionToQuiz(quiz, q1);

        // 7. Validate Quiz
        if (!quizService.validateQuiz(quiz)) {
            cout << "Invalid quiz!" << endl;
            return 0;
        }

        // 8. In kết quả
        cout << "\n=== QUIZ INFO ===" << endl;
        cout << "Title: " << quiz.getTitle() << endl;
        cout << "Time: " << quiz.getTimeLimit() << " minutes" << endl;
        cout << "Number of questions: " << quiz.getQuestions().size() << endl;

        cout << "\n=== QUESTION DETAIL ===" << endl;
        for (const auto& ans : q1.getAnswers()) {
            cout << "- " << ans.getContent();
            if (ans.isCorrect()) cout << " (Correct)";
            cout << endl;
        }

        cout << "\n Test PASSED!" << endl;
    }
    catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}