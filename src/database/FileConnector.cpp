#include "FileConnector.h"
#include <fstream>
#include <iostream>

vector<string> FileConnector::readFile(const string& path) {
    vector<string> lines;
    ifstream file(path);
    string line;

    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    return lines;
}

// ghi đè toàn bộ file
void FileConnector::writeFile(const string& path, vector<string> lines) {
    ofstream file(path);

    for (string line : lines) {
        file << line << endl;
    }

    file.close();
}

// thêm 1 dòng vào cuối
void FileConnector::appendLine(const string& path, const string& line) {
    ofstream file(path, ios::app);
    file << line << endl;
    file.close();
}

// xóa theo id
void FileConnector::deleteById(const string& path, const string& id) {
    vector<string> lines = readFile(path);
    vector<string> newLines;

    newLines.push_back(lines[0]); // giữ header

    for (int i = 1; i < lines.size(); i++) {
        string lineId = lines[i].substr(0, lines[i].find('|'));
        if (lineId != id) {
            newLines.push_back(lines[i]);
        }
    }

    writeFile(path, newLines);
}

// update theo id
void FileConnector::updateById(const string& path, const string& id, const string& newLine) {
    vector<string> lines = readFile(path);

    for (int i = 1; i < lines.size(); i++) {
        string lineId = lines[i].substr(0, lines[i].find('|'));
        if (lineId == id) {
            lines[i] = newLine;
        }
    }

    writeFile(path, lines);
}
