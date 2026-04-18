#pragma once

#include <string>
#include <regex>

class Validator
{
public:
    // STRING
    static bool isNotEmpty(const std::string& value)
    {
        return !value.empty();
    }
    // EMAIL
    static bool isValidEmail(const std::string& email)
    {
        const std::regex pattern(R"(^[\w\.-]+@[\w\.-]+\.\w+$)");
        return std::regex_match(email, pattern);
    }
    // PASSWORD
    static bool isValidPassword(const std::string& password)
    {
        // ít nhất 6 ký tự
        return password.length() >= 6;
    }
    // USERNAME
    static bool isValidUsername(const std::string& username)
    {
        return username.length() >= 3;
    }
    // ID
    static bool isValidId(int id)
    {
        return id > 0;
    }
};