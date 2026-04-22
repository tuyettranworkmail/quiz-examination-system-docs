#pragma once

#include <string>
#include <functional>

// Utility hash password đơn giản
class PasswordHasher
{
public:

    // hash password
    static std::string hash(const std::string& password)
    {
        std::hash<std::string> hasher;
        size_t hashed = hasher(password);

        return std::to_string(hashed);
    }

    // verify password
    static bool verify(const std::string& password,
                    const std::string& hashedPassword)
    {
        return hash(password) == hashedPassword;
    }
};