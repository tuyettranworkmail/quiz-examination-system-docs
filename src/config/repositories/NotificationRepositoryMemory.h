#pragma once
#include "INotificationRepository.h"
#include <vector>

using namespace std;

class NotificationRepositoryMemory : public INotificationRepository
{
private:
    vector<Notification> notifications;

public:

    // thêm notification
    void add(Notification notification)
    {
        notifications.push_back(notification);
    }

    // lấy theo user
    vector<Notification> getByUserId(int userId)
    {
        vector<Notification> result;

        for (Notification n : notifications)
        {
            if (n.user_id == userId)
            {
                result.push_back(n);
            }
        }

        return result;
    }

    // mark read
    void markAsRead(int id)
    {
        for (Notification &n : notifications)
        {
            if (n.notification_id == id)
            {
                n.is_read = true;
            }
        }
    }
};