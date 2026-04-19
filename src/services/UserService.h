#pragma once

#include "../Models/User.h"
#include "../Repositories/IUserRepository.h"
#include "../utils/Validator.h"
#include <stdexcept>

class UserService
{
private:

    IUserRepository* userRepository;

    // INTERNAL BUSINESS LOGIC

    User getUserInternal(int id)
    {
        User user = userRepository->getById(id);

        if (user.user_id == 0)
        {
            throw std::runtime_error("User not found");
        }

        return user;
    }


    bool updateProfileInternal(const User& user)
    {
        return userRepository->update(user);
    }


    bool changePasswordInternal(int userId, const std::string& newPassword)
    {
        User user = getUserInternal(userId);

        if (user.password == newPassword)
        {
            throw std::runtime_error("New password must be different from old password");
        }

        user.password = newPassword;

        return userRepository->update(user);
    }

public:

    // =====================
    // CONSTRUCTOR
    // =====================

    UserService(IUserRepository* repo)
    {
        if (repo == nullptr)
        {
            throw std::runtime_error("Repository cannot be null");
        }

        userRepository = repo;
    }


    // =====================
    // HANDLERS
    // =====================

    // GET USER PROFILE
    User getUser(int id)
    {
        if (id <= 0)
        {
            throw std::runtime_error("Invalid user id");
        }

        return getUserInternal(id);
    }


    // UPDATE USER PROFILE
    bool updateProfile(const User& user)
    {
        if (user.user_id <= 0)
        {
            throw std::runtime_error("Invalid user");
        }

        if (user.username.empty())
        {
            throw std::runtime_error("Username cannot be empty");
        }

        if (!Validator::isValidEmail(user.email))
        {
            throw std::runtime_error("Invalid email format");
        }

        return updateProfileInternal(user);
    }


    // CHANGE PASSWORD
    bool changePassword(int userId, const std::string& newPassword)
    {
        if (userId <= 0)
        {
            throw std::runtime_error("Invalid user id");
        }

        if (!Validator::isValidPassword(newPassword))
        {
            throw std::runtime_error("Password must be at least 8 characters");
        }

        return changePasswordInternal(userId, newPassword);
    }
};