#pragma once
#include <string>
#include <ctime>

using namespace std;

// Notification class theo UML
class Notification
{
public:

    int notification_id;
    int user_id;
    string content;
    time_t created_at;
    bool is_read;

    Notification() {}

    Notification(int id, int userId, string content)
    {
        this->notification_id = id;
        this->user_id = userId;
        this->content = content;
        this->created_at = time(0);
        this->is_read = false;
    }

    // mark read
    void markAsRead()
    {
        is_read = true;
    }
};