#include <iostream>

#include "../Repositories/UserRepositoryMemory.h"
#include "../Services/AuthService.h"

using namespace std;

int main()
{
    // tạo repository
    UserRepositoryMemory userRepo;

    // tạo service
    AuthService authService(&userRepo);

    // tạo user test
    User user1(1, "john", "john@gmail.com", "123", "student", true);

    // test register
    authService.registerUser(user1);

    cout << "Register success" << endl;

    // test login
    User loginUser = authService.login("john", "123");

    cout << "Login success: " << loginUser.username << endl;

    return 0;
}