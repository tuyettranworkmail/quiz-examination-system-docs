#pragma once

#include "../Repositories/IUserRepository.h"
#include "../Models/User.h"
#include "../utils/Validator.h"
#include "../utils/PasswordHasher.h"
#include <stdexcept>

class AuthService
{
private:
    IUserRepository* userRepository;

    // BUSINESS LOGIC
    User loginInternal(const std::string& username, const std::string& password)
    {
        User user = userRepository->getByUsername(username);

        // check tồn tại
        if (user.username.empty())
        {
            throw std::runtime_error("User not found");
        }

        if (!PasswordHasher::verify(password, user.password))
        {
            throw std::runtime_error("Wrong password");
        }

        return user;
    }

    bool registerInternal(const User& user)
    {
        // check trùng username
        User existing = userRepository->getByUsername(user.username);

        if (!existing.username.empty())
        {
            throw std::runtime_error("Username already exists");
        }

        return userRepository->add(user);
    }

public:
    AuthService(IUserRepository* repo)
    {
        userRepository = repo;
    }

    // LOGIN (HANDLER)
    User login(const std::string& username, const std::string& password)
    {
        if (!Validator::isNotEmpty(username) || !Validator::isNotEmpty(password))
        {
            throw std::runtime_error("Invalid input");
        }

        return loginInternal(username, password);
    }

    // REGISTER (HANDLER)
    bool registerUser(User user)
    {
        if (!Validator::isNotEmpty(user.username) ||
            !Validator::isValidPassword(user.password))
        {
            throw std::runtime_error("Invalid user data");
        }

        user.password = PasswordHasher::hash(user.password);

        return registerInternal(user);
    }

    // LOGOUT
    void logout()
    {
      // Hệ thống hiện tại không sử dụng session hoặc token
      // nên không có trạng thái đăng nhập để xóa
    }
};