#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "FileConnector.h"

using namespace std;

class User {
public:
    string id;
    string username;
    string email;
    string password;
    string role;
};

class UserRepository {
private:
    FileConnector fileConnector;
    string path = "Data/user.txt";

public:
    vector<User> getAllUsers() {
        vector<User> users;
        vector<string> lines = fileConnector.readFile(path);

        for (int i = 1; i < lines.size(); i++) {
            stringstream ss(lines[i]);
            string item;
            vector<string> data;

            while (getline(ss, item, '|')) {
                data.push_back(item);
            }

            if (data.size() == 5) {
                User u;
                u.id = data[0];
                u.username = data[1];
                u.email = data[2];
                u.password = data[3];
                u.role = data[4];
                users.push_back(u);
            }
        }

        return users;
    }
    User findByEmail(string email) {
        vector<User> users = getAllUsers();

        for (auto u : users) {
            if (u.email == email) {
                return u;
            }
        }

        return User(); // không tìm thấy
    }

};