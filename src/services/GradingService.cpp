#include <vector>
#include <string>
using namespace std;

class AttemptAnswer {
public:
    string questionId;
    string answerId;
};

class Answer {
public:
    string questionId;
    string answerId;
    bool isCorrect;
};

class GradingService {
public:
    double grade(vector<AttemptAnswer> userAnswers, vector<Answer> correctAnswers) {
        int correct = 0;
        int total = userAnswers.size();

        for (auto ua : userAnswers) {
            for (auto ca : correctAnswers) {
                if (ua.questionId == ca.questionId &&
                    ua.answerId == ca.answerId &&
                    ca.isCorrect) {
                    correct++;
                }
            }
        }

        if (total == 0) return 0;

        return (double)correct / total * 10;
    }
};