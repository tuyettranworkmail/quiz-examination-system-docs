#include <iostream>
#include "ATTEMPT.h"
#include "RESULTSERVICE.h"
#include "IGRADINGSERVICE.h"
#include "ATTEMPTSERVICE.h"

using namespace std;

// Mock GradingService
class MockGradingService : public IGradingService
{
public:
    int gradeAttempt(const Attempt& attempt) override
    {
        // chỉ để test (mỗi câu = 1 điểm)
        return attempt.getAnswerList().size();
    }
};

int main()
{
    // Khởi tạo service
    MockGradingService gradingService;
    ResultService resultService;

    AttemptService attemptService(&gradingService, &resultService);

    // Start Attempt
    Attempt attempt = attemptService.startAttempt(1, 1001, 5001);

    cout << "Start Attempt ID: " << attempt.getAttemptId() << endl;

    // Làm bài
    attemptService.saveAnswer(attempt, 1, 2);
    attemptService.saveAnswer(attempt, 2, 3);
    attemptService.saveAnswer(attempt, 3, 1);

    cout << "Answers saved: " << attempt.getAnswerList().size() << endl;

    // Submit
    attemptService.submitAttempt(attempt);

    cout << "Submitted. Score: " << attempt.getScore() << endl;

    // Lấy result
    Result result = resultService.getResultByAttemptId(attempt.getAttemptId());

    cout << "Result Score: " << result.getScore() << endl;

    return 0;
}
