#pragma once
#include "IUserRepository.h"
#include <vector>

using namespace std;

// Repository dùng vector để test
class UserRepositoryMemory : public IUserRepository
{
private:
    vector<User> users;   // lưu danh sách user

public:

    // tìm user theo username
    User getByUsername(string username)
    {
        for (User user : users)
        {
            if (user.username == username)
                return user;
        }

        return User(); // không tìm thấy
    }

    // thêm user
    void add(User user)
    {
        users.push_back(user);
    }

    // lấy tất cả user
    vector<User> getAll()
    {
        return users;
    }
};