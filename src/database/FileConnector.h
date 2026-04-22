#ifndef FILECONNECTOR_H
#define FILECONNECTOR_H

#include <vector>
#include <string>
using namespace std;

class FileConnector {
public:
    vector<string> readFile(const string& path);
};

#endif
