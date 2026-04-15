#pragma once
#include <vector>
#include "../Models/User.h"

using namespace std;

class IUserService
{
public:
    virtual vector<User> getAllUsers() = 0;

    virtual User getUserById(int id) = 0;

    virtual bool updateUser(User user) = 0;

    virtual bool deleteUser(int id) = 0;
};