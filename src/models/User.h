#pragma once

#include <string>

// Class User theo UML
class User
{
public:

    int user_id = 0;
    std::string username;
    std::string email;
    std::string password;
    std::string role;
    bool is_active = false;

    // constructor rỗng
    User() = default;

    // constructor đầy đủ
    User(int id,
        const std::string& username,
        const std::string& email,
        const std::string& password,
        const std::string& role,
        bool active)
        : user_id(id),
        username(username),
        email(email),
        password(password),
        role(role),
        is_active(active)
    {}

    // update profile
    void updateProfile(const std::string& newEmail,
                    const std::string& newRole)
    {
        email = newEmail;
        role = newRole;
    }

    // change password
    void changePassword(const std::string& newPassword)
    {
        password = newPassword;
    }
};