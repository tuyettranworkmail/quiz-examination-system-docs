#include <iostream>

#include "Repositories/UserRepositoryMemory.h"
#include "Repositories/NotificationRepositoryMemory.h"

#include "Services/AuthService.h"
#include "Services/NotificationService.h"

using namespace std;

int main()
{
    // tạo repository
    UserRepositoryMemory userRepo;
    NotificationRepositoryMemory notificationRepo;

    // tạo service
    AuthService authService(&userRepo);
    NotificationService notificationService(&notificationRepo);

    // =========================
    // TEST REGISTER
    // =========================

    User user1(1, "john", "john@gmail.com", "123", "student", true);

    authService.registerUser(user1);

    cout << "Register success" << endl;


    // =========================
    // TEST LOGIN
    // =========================

    User loginUser =
        authService.login("john", "123");

    cout << "Login success: "
         << loginUser.username << endl;


    // =========================
    // TEST SEND NOTIFICATION
    // =========================

    Notification n1(1, 1, "Welcome to system");

    notificationService.createNotification(n1);


    // =========================
    // TEST VIEW NOTIFICATION
    // =========================

    vector<Notification> list =
        notificationService.getNotifications(1);

    for (Notification n : list)
    {
        cout << "Notification: "
             << n.content << endl;
    }


    // =========================
    // TEST MARK READ
    // =========================

    notificationService.markAsRead(1);

    cout << "Notification marked as read" << endl;

    return 0;
}