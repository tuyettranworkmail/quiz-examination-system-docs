#pragma once

#include "../Models/User.h"
#include "../Repositories/IUserRepository.h"
#include "../utils/Validator.h"
#include <stdexcept>

class UserService
{
private:
    IUserRepository* userRepository;

    // =====================
    // BUSINESS LOGIC
    // =====================
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

        user.password = newPassword;

        return userRepository->update(user);
    }

public:

    UserService(IUserRepository* repo)
    {
        userRepository = repo;
    }

    // =====================
    // HANDLER
    // =====================

    // GET USER PROFILE
    User getUser(int id)
    {
        if (id <= 0)
        {
            throw std::runtime_error("Invalid id");
        }

        return getUserInternal(id);
    }

    // UPDATE PROFILE
    bool updateProfile(const User& user)
    {
        if (user.user_id <= 0)
        {
            throw std::runtime_error("Invalid user");
        }

        return updateProfileInternal(user);
    }

    // CHANGE PASSWORD
    bool changePassword(int userId, const std::string& newPassword)
    {
        if (userId <= 0)
        {
            throw std::runtime_error("Invalid userId");
        }

        if (!Validator::isValidPassword(newPassword))
        {
            throw std::runtime_error("Weak password");
        }

        return changePasswordInternal(userId, newPassword);
    }
};