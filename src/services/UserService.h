#pragma once

#include "../Models/User.h"
#include "../Repositories/IUserRepository.h"

// UserService xử lý:
// Manage profile
// Change password
class UserService
{
private:

    IUserRepository* userRepository;

public:

    UserService(IUserRepository* repo)
    {
        userRepository = repo;
    }

    // ========================
    // GET USER PROFILE
    // ========================
    User getUser(int id)
    {
        return userRepository->getById(id);
    }

    // ========================
    // UPDATE PROFILE
    // ========================
    bool updateProfile(User user)
    {
        userRepository->update(user);
        return true;
    }

    // ========================
    // CHANGE PASSWORD
    // ========================
    bool changePassword(int userId, string newPassword)
    {
        // lấy user
        User user = userRepository->getById(userId);

        // đổi password
        user.password = newPassword;

        // update
        userRepository->update(user);

        return true;
    }
};