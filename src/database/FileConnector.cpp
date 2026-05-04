#include "FileConnector.h"
#include <fstream>

vector<string> FileConnector::readFile(const string& path) {
    vector<string> lines;
    ifstream file(path);

    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}