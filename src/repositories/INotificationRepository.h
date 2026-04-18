#pragma once

#include <vector>
#include "../Models/Notification.h"

class INotificationRepository
{
public:
    virtual ~INotificationRepository() = default;

    // thêm notification
    virtual bool add(const Notification& notification) = 0;

    // lấy theo user
    virtual std::vector<Notification> getByUserId(int userId) const = 0;

    // mark read
    virtual bool markAsRead(int id) = 0;
};