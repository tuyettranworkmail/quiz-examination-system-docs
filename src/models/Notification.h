#pragma once

#include <string>
#include <ctime>

// Notification class theo UML
class Notification
{
public:

    int notification_id = 0;
    int user_id = 0;
    std::string content;
    std::time_t created_at = 0;
    bool is_read = false;

    // constructor rỗng
    Notification() = default;

    // constructor đầy đủ
    Notification(int id,
                int userId,
                const std::string& content)
        : notification_id(id),
        user_id(userId),
        content(content),
        created_at(std::time(nullptr)),
        is_read(false)
    {}

    // mark read
    void markAsRead()
    {
        is_read = true;
    }
};