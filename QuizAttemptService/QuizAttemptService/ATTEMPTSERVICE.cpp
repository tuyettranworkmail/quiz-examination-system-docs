#include "ATTEMPTSERVICE.h"

// Constructor
AttemptService::AttemptService(IGradingService* gs, ResultService* rs)
{
    gradingService = gs;
    resultService = rs;
}

// 1. Start Attempt
Attempt AttemptService::startAttempt(int attemptId, int userId, int quizId)
{
    return Attempt(attemptId, userId, quizId);
}

// 2. Save Answer 
void AttemptService::saveAnswer(Attempt& attempt, int questionId, int optionId)
{
    AttemptAnswer answer;

    answer.setAttemptId(attempt.getAttemptId());
    answer.setQuestionId(questionId);

    // chọn đáp án (auto save)
    answer.selectAnswer(optionId);

    // thêm vào danh sách
    attempt.addAnswer(answer);
}

// 3. Submit Attempt 
void AttemptService::submitAttempt(Attempt& attempt)
{
    // BR: chỉ submit 1 lần
    if (attempt.getIsSubmitted())
    {
        return;
    }

    // CALL GradingService
    int score = gradingService->gradeAttempt(attempt);

    // lưu điểm vào attempt
    attempt.setScore(score);
    attempt.submit();

    // tạo result
    Result result;
    result.setAttemptId(attempt.getAttemptId());
    result.setScore(score);

    // lưu result
    resultService->saveResult(result);
}
