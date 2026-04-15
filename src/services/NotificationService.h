#pragma once

#include "../Repositories/INotificationRepository.h"
#include "../Models/Notification.h"
#include <vector>

using namespace std;

// NotificationService theo UML
class NotificationService
{
private:

    INotificationRepository* repository;

public:

    NotificationService(INotificationRepository* repo)
    {
        repository = repo;
    }

    // create notification
    void createNotification(Notification notification)
    {
        repository->add(notification);
    }

    // get notifications
    vector<Notification> getNotifications(int userId)
    {
        return repository->getByUserId(userId);
    }

    // mark read
    void markAsRead(int id)
    {
        repository->markAsRead(id);
    }
};