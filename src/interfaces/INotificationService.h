#pragma once

#include <vector>
#include "../Models/Notification.h"

class INotificationService
{
public:
    virtual ~INotificationService() = default;

    virtual std::vector<Notification> getNotifications(int userId) const = 0;

    virtual void sendNotification(const Notification& notification) = 0;

    virtual void markAsRead(int id) = 0;
};