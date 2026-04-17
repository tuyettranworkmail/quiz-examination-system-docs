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
        // chỉ test: mỗi câu = 1 điểm
        return (int)attempt.getAnswerList().size();

    }
};

void testAttemptFlow()
{
    cout << "===== TEST ATTEMPT SERVICE =====" << endl;

    // Khởi tạo service
    MockGradingService gradingService;
    ResultService ResultService;
    AttemptService AttemptService(&gradingService, &ResultService);

    // 1. Start attempt
    Attempt attempt = AttemptService.startAttempt(1, 1001, 5001);
    cout << "Start Attempt ID: " << attempt.getAttemptId() << endl;

    // 2. Save answers
    AttemptService.saveAnswer(attempt, 1, 2);
    AttemptService.saveAnswer(attempt, 2, 3);
    AttemptService.saveAnswer(attempt, 3, 1);   
    cout << "Answers count: " << attempt.getAnswerList().size() << endl;

    // 3. Submit
    AttemptService.submitAttempt(attempt);
    cout << "Submitted Score: " << attempt.getScore() << endl;

    // 4. Get result
    Result result = ResultService.getResultByAttemptId(attempt.getAttemptId());
    cout << "Result Score: " << result.getScore() << endl;

    cout << "===== END TEST =====" << endl;
}

int main()
{
    testAttemptFlow();
    return 0;
}
