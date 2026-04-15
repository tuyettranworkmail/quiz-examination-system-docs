#pragma once
#include "../Models/User.h"

// Interface AuthService
// Service xử lý logic nghiệp vụ
class IAuthService
{
public:

    // đăng nhập
    virtual User login(string username, string password) = 0;

    // đăng ký
    virtual bool registerUser(User user) = 0;
};