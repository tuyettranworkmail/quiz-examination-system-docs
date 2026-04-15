#pragma once
#include <vector>
#include "../Models/Notification.h"

using namespace std;

class INotificationService
{
public:
    virtual vector<Notification> getNotifications(int userId) = 0;

    virtual void sendNotification(Notification notification) = 0;

    virtual void markAsRead(int id) = 0;
};