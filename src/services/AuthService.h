#pragma once

#include "../Repositories/IUserRepository.h"
#include "../Models/User.h"

// AuthService theo UML
class AuthService
{
private:

    IUserRepository* userRepository;

public:

    AuthService(IUserRepository* repo)
    {
        userRepository = repo;
    }

    // =====================
    // LOGIN
    // =====================
    User login(string username, string password)
    {
        User user =
            userRepository->getByUsername(username);

        if (user.username == "")
        {
            throw runtime_error("User not found");
        }

        if (user.password != password)
        {
            throw runtime_error("Wrong password");
        }

        return user;
    }

    // =====================
    // REGISTER
    // =====================
    bool registerUser(User user)
    {
        userRepository->add(user);
        return true;
    }

    // =====================
    // LOGOUT
    // =====================
    void logout()
    {
        // clear session nếu có
    }
};