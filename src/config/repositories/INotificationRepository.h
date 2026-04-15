#pragma once

#include "../Models/Notification.h"
#include <vector>

using namespace std;

class INotificationRepository
{
public:

    virtual void add(Notification notification) = 0;

    virtual vector<Notification> getByUserId(int userId) = 0;

    virtual void markAsRead(int id) = 0;
};