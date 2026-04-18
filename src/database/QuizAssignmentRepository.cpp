#include <vector>
#include <string>
#include <sstream>
#include "FileConnector.h"

using namespace std;

class QuizAssignment {
public:
    string id;
    string quizId;
    string userId;
    string startTime;
    string endTime;
};

class QuizAssignmentRepository {
private:
    FileConnector fileConnector;
    string path = "Data/quiz_assignment.txt";

public:
    vector<QuizAssignment> getAll() {
        vector<QuizAssignment> list;
        vector<string> lines = fileConnector.readFile(path);

        for (int i = 1; i < lines.size(); i++) {
            stringstream ss(lines[i]);
            string item;
            vector<string> data;

            while (getline(ss, item, '|')) {
                data.push_back(item);
            }

            if (data.size() == 5) {
                QuizAssignment q;
                q.id = data[0];
                q.quizId = data[1];
                q.userId = data[2];
                q.startTime = data[3];
                q.endTime = data[4];
                list.push_back(q);
            }
        }

        return list;
    }
};