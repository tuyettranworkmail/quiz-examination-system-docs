#include <iostream>
#include <vector>

#include "repositories/UserRepositoryMemory.h"
#include "repositories/NotificationRepositoryMemory.h"
#include "services/AuthService.h"
#include "services/NotificationService.h"
#include "models/User.h"
#include "models/Notification.h"
#include "utils/PasswordHasher.h"

int main()
{
    try
    {
        UserRepositoryMemory userRepo;
        NotificationRepositoryMemory notificationRepo;
        AuthService authService(&userRepo);
        NotificationService notificationService(&notificationRepo);
        // REGISTER
        User user1(1, "john", "john@gmail.com",
                    "123456",
                    "student", true);
        authService.registerUser(user1);
        std::cout << "Register success\n";
        // LOGIN
        User loginUser =
            authService.login("john", "123456");
        std::cout << "Login success: "
                << loginUser.username << "\n";
        // SEND NOTIFICATION
        Notification n1(1, 1, "Welcome to system");
        notificationService.sendNotification(n1);
        // VIEW NOTIFICATION
        std::vector<Notification> list =
            notificationService.getNotifications(1);
        for (const Notification& n : list)
        {
            std::cout << "Notification: "
                    << n.content
                    << " | Read: "
                    << (n.is_read ? "Yes" : "No")
                    << "\n";
        }
        // MARK READ
        notificationService.markAsRead(1);
        std::cout << "Notification marked as read\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }
    return 0;
}