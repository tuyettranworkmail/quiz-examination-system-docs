#pragma once

#include <vector>
#include "../Models/User.h"

class IUserRepository
{
public:
    virtual ~IUserRepository() = default;

    // tìm theo username
    virtual User getByUsername(const std::string& username) = 0;

    // tìm theo id
    virtual User getById(int id) = 0;

    // thêm user
    virtual bool add(const User& user) = 0;

    // update user
    virtual bool update(const User& user) = 0;

    // xóa user
    virtual bool remove(int id) = 0;

    // lấy tất cả
    virtual std::vector<User> getAll() const = 0;
};