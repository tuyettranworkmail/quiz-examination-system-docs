#pragma once
#include <string>

using namespace std;

// Class User theo UML
class User
{
public:

    int user_id;        // id user
    string username;    // username
    string email;       // email
    string password;    // password
    string role;        // role
    bool is_active;     // trạng thái hoạt động

    // constructor rỗng
    User() {}

    // constructor đầy đủ
    User(int id, string username, string email,
        string password, string role, bool active)
    {
        this->user_id = id;
        this->username = username;
        this->email = email;
        this->password = password;
        this->role = role;
        this->is_active = active;
    }

    // update profile
    void updateProfile(string email, string role)
    {
        this->email = email;
        this->role = role;
    }

    // change password
    void changePassword(string newPassword)
    {
        this->password = newPassword;
    }
};