#include "ATTEMPT.h"
#include <fstream>
#include <sstream>

// ===================== CONSTRUCTOR =====================
Attempt::Attempt()
{
    attemptId = 0;
    userId = 0;
    quizId = 0;
    isSubmitted = false;
    score = 0;
}
Attempt::Attempt(int atId, int uId, int qzId)
{
    attemptId = atId;
    userId = uId;
    quizId = qzId;
    isSubmitted = false;
    score = 0;
}

Attempt::~Attempt() {}

// ===================== GETTER =====================
int Attempt::getAttemptId() const { return attemptId; }
int Attempt::getUserId() const { return userId; }
int Attempt::getQuizId() const { return quizId; }
bool Attempt::getIsSubmitted() const { return isSubmitted; }
int Attempt::getScore() const { return score; }
std::vector<AttemptAnswer> Attempt::getAnswerList() const { return answerList; }

// ===================== SETTER =====================
void Attempt::setAttemptId(int id) { attemptId = id; }
void Attempt::setUserId(int id) { userId = id; }
void Attempt::setQuizId(int id) { quizId = id; }
void Attempt::setIsSubmitted(bool submitted) { isSubmitted = submitted; }
void Attempt::setScore(int s) { score = s; }

// ===================== BUSINESS =====================
void Attempt::addAnswer(const AttemptAnswer& answer)
{
    answerList.push_back(answer);
}

void Attempt::submit()
{
    if (!isSubmitted)
    {
        isSubmitted = true;
    }
}



// ===================== PATH =====================
static std::string PATH = "Data/attempt.txt";



//===================== CONVERT =====================

std::string attemptToLine(const Attempt & a)
{
    return std::to_string(a.getAttemptId()) + "|" +
        std::to_string(a.getUserId()) + "|" +
        std::to_string(a.getQuizId()) + "|" +
        std::to_string(a.getScore()) + "|" +
        std::to_string(a.getIsSubmitted());
}

Attempt lineToAttempt(const std::string& line)
{
    std::stringstream ss(line);
    std::string item;

    Attempt a;

    getline(ss, item, '|');
    a.setAttemptId(stoi(item));

    getline(ss, item, '|');
    a.setUserId(stoi(item));

    getline(ss, item, '|');
    a.setQuizId(stoi(item));

    getline(ss, item, '|');
    a.setScore(stoi(item));

    getline(ss, item, '|');
    a.setIsSubmitted(item == "1");

    return a;
}

///===================== SAVE =====================

void saveAllAttempts(const std::vector<Attempt>&list)
{
    std::ofstream file(PATH);

    for (auto& a : list)
    {
        file << attemptToLine(a) << "\n";
    }
}

void addAttempt(const Attempt& a)
{
    std::ofstream file(PATH, std::ios::app);
    file << attemptToLine(a) << "\n";
}

//===================== LOAD =====================

std::vector<Attempt> loadAttempts()
{
    std::vector<Attempt> list;
    std::ifstream file(PATH);

    std::string line;

    while (getline(file, line))
    {
        if (!line.empty())
        {
            list.push_back(lineToAttempt(line));
        }
    }

    return list;
}