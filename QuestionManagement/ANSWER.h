#pragma once
#include <string>

class Answer {
private:
    int answerId;
    std::string content;
    bool correct;

public:
    Answer(int id, const std::string& c, bool isCorrect = false)
        : answerId(id), content(c), correct(isCorrect) {
    }

    int getAnswerId() const {
        return answerId;
    }

    std::string getContent() const {
        return content;
    }

    bool isCorrect() const {
        return correct;
    }

    bool isCorrectAnswer() const {
        return correct;
    }

    void setCorrect(bool value) {
        correct = value;
    }
};