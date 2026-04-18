#pragma once

#include "IUserRepository.h"
#include <vector>

class UserRepositoryMemory : public IUserRepository
{
private:
    std::vector<User> users;

public:

    // tìm user theo username
    User getByUsername(const std::string& username)
    {
        for (const User& user : users)
        {
            if (user.username == username)
                return user;
        }

        return User(); // không tìm thấy
    }

    // tìm theo id
    User getById(int id)
    {
        for (const User& user : users)
        {
            if (user.user_id == id)
                return user;
        }

        return User();
    }

    // thêm user
    bool add(const User& user)
    {
        // check trùng username
        for (const User& u : users)
        {
            if (u.username == user.username)
                return false;
        }

        users.push_back(user);
        return true;
    }

    // update user
    bool update(const User& user)
    {
        for (User& u : users)
        {
            if (u.user_id == user.user_id)
            {
                u = user;
                return true;
            }
        }

        return false;
    }

    // xóa user
    bool remove(int id)
    {
        for (auto it = users.begin(); it != users.end(); ++it)
        {
            if (it->user_id == id)
            {
                users.erase(it);
                return true;
            }
        }

        return false;
    }

    // lấy tất cả user
    std::vector<User> getAll() const override
    {
    return users;
    }
};