#pragma once

#include "../Models/User.h"
#include <vector>

using namespace std;

class IUserRepository
{
public:

    virtual User getByUsername(string username) = 0;

    virtual void add(User user) = 0;

    virtual vector<User> getAll() = 0;
};