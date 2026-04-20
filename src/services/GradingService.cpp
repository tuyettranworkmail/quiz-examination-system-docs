#include "GradingService.h"

int GradingService::gradeAttempt(const Attempt& attempt) {
    auto answers = attempt.getAnswerList();
    int correct = 0;
    int total = answers.size();

    if (total == 0) return 0;

    // Grade calculation - this needs to be adjusted based on actual grading logic
    for (const auto& answer : answers) {
        // Add your grading logic here
        correct++;  // Placeholder
    }

    return (correct * 100) / total;
}