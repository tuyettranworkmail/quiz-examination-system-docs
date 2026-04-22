#pragma once

#include "../Repositories/INotificationRepository.h"
#include "../Models/Notification.h"
#include "../utils/Validator.h"
#include <vector>
#include <stdexcept>

class NotificationService
{
private:
    INotificationRepository* repository;

    // =====================
    // BUSINESS LOGIC
    // =====================
    void createNotificationInternal(const Notification& notification)
    {
        if (!repository->add(notification))
        {
            throw runtime_error("Failed to create notification");
        }
    }

    vector<Notification> getNotificationsInternal(int userId)
    {
        return repository->getByUserId(userId);
    }

    void markAsReadInternal(int id)
    {
        bool result = repository->markAsRead(id);

        if (!result)
        {
            throw runtime_error("Notification not found");
        }
    }

public:

    NotificationService(INotificationRepository* repo)
    {
        if(repo == nullptr)
            throw std::runtime_error("Repository cannot be null");

        repository = repo;
    }

    // =====================
    // HANDLER
    // =====================

    void sendNotification(const Notification& notification)
    {
        if (notification.user_id <= 0)
        {
            throw runtime_error("Invalid userId");
        }

        if (!Validator::isNotEmpty(notification.content))
        {
            throw runtime_error("Content is empty");
        }

        createNotificationInternal(notification);
    }

    vector<Notification> getNotifications(int userId)
    {
        if (userId <= 0)
        {
            throw runtime_error("Invalid userId");
        }

        return getNotificationsInternal(userId);
    }

    void markAsRead(int id)
    {
        if (id <= 0)
        {
            throw runtime_error("Invalid id");
        }

        markAsReadInternal(id);
    }
};