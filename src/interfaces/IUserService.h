#pragma once

#include <vector>
#include "../Models/User.h"

class IUserService
{
public:
    virtual ~IUserService() = default;

    virtual std::vector<User> getAllUsers() const = 0;

    virtual User getUserById(int id) const = 0;

    virtual bool updateUser(const User& user) = 0;

    virtual bool deleteUser(int id) = 0;
};