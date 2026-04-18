#pragma once

#include "INotificationRepository.h"
#include <vector>

class NotificationRepositoryMemory : public INotificationRepository
{
private:
    std::vector<Notification> notifications;

public:

    // thêm notification
    bool add(const Notification& notification)
    {
        notifications.push_back(notification);
        return true;
    }

    // lấy theo user
    std::vector<Notification> getByUserId(int userId) const override
   {
        std::vector<Notification> result;

        for (const Notification& n : notifications)
        {
            if (n.user_id == userId)
            {
            result.push_back(n);
            }
        }

        return result;
   }

    // mark read
    bool markAsRead(int id)
    {
        for (Notification& n : notifications)
        {
            if (n.notification_id == id)
            {
                n.is_read = true;
                return true;
            }
        }

        return false;
    }
};