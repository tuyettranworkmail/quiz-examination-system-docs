#ifndef FILECONNECTOR_H
#define FILECONNECTOR_H

#include <vector>
#include <string>
using namespace std;

class FileConnector {
public:
    vector<string> readFile(const string& path);
    void writeFile(const string& path, vector<string> lines);
    void appendLine(const string& path, const string& line);
    void deleteById(const string& path, const string& id);
    void updateById(const string& path, const string& id, const string& newLine);
};

#endif
