#pragma once

#include <string>
#include "../Models/User.h"

// Interface AuthService
class IAuthService
{
public:
    virtual ~IAuthService() = default;

    // đăng nhập
    virtual User login(const std::string& username,
                        const std::string& password) = 0;

    // đăng ký
    virtual bool registerUser(const User& user) = 0;
};