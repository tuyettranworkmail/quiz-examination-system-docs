#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <regex>
#include <algorithm>
#include <map>
#include <random>
#include "database/FileConnector.h"
#include "models/User.h"
#include "models/Notification.h"
#include <limits>
#include "repositories/UserRepositoryMemory.h"
#include "repositories/NotificationRepositoryMemory.h"

#include "services/AuthService.h"
#include "services/UserService.h"
#include "services/NotificationService.h"
#include "services/GradingService.h"

#include "../QuizAttemptService/QuizAttemptService/ATTEMPTSERVICE.h"
#include "../QuizAttemptService/QuizAttemptService/RESULTSERVICE.h"

using namespace std;
using namespace std::chrono;

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen()
{
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


// ============== FR-02: Quiz Structure ==============
struct Question
{
    int id;
    string text;
    string A,B,C,D;
    int correct;
    int quizId;
};

struct Quiz
{
    int id;
    string title;
    string description;
    int timeLimit;
    int totalQuestions;
    bool isActive;
    string createdBy;
};

struct QuizAttemptRecord
{
    int attemptId;
    int userId;
    int quizId;
    int score;
    int maxScore;
    string submissionTime;
    int attemptCount;
};

// Global storage structures
vector<Question> quizQuestions;
vector<Quiz> quizzes;
vector<QuizAttemptRecord> attemptRecords;
map<int, int> userAttemptCount; // FR-14: Track attempt count per user

// ============== FR-01: Validation Functions (BR-01, BR-02, BR-03) ==============
bool isValidEmail(const string& email)
{
    const regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return regex_match(email, pattern);
}

bool isValidPassword(const string& password)
{
    // BR-03: Password must be at least 8 characters
    return password.length() >= 8;
}

bool isValidUsername(const string& username)
{
    // BR-01: Username must not be empty and at least 3 chars
    return !username.empty() && username.length() >= 3;
}

// ============== UI Menu Functions ==============
void guestMenu()
{
    clearScreen();
    cout<<"\n===== QUIZ SYSTEM - GUEST MENU =====\n";
    cout<<"1. Register\n";
    cout<<"2. Login\n";
    cout<<"0. Exit\n";
    cout<<"================================\n";
}

void adminMenu()
{
    cout<<"\n===== ADMIN MENU =====\n";
    cout<<"1. View All Users\n";
    cout<<"2. Delete User\n";
    cout<<"3. View Reports\n";
    cout<<"4. System Statistics\n";
    cout<<"5. Logout\n";
    cout<<"======================\n";
}

void studentMenu()
{
    clearScreen();
    cout<<"\n===== STUDENT MENU =====\n";
    cout<<"1. Take Quiz\n";
    cout<<"2. View Results\n";
    cout<<"3. View Notifications\n";
    cout<<"4. Change Password\n";
    cout<<"5. View Profile\n";
    cout<<"6. Logout\n";
    cout<<"========================\n";
}

void teacherMenu()
{
    clearScreen();
    cout<<"\n===== TEACHER MENU =====\n";
    cout<<"1. Create Quiz\n";
    cout<<"2. Create Question\n";
    cout<<"3. View Questions\n";
    cout<<"4. Edit Question\n";
    cout<<"5. Delete Question\n";
    cout<<"6. Manage Quizzes\n";
    cout<<"7. View Quiz Results\n";
    cout<<"8. Send Notification\n";
    cout<<"9. Change Password\n";
    cout<<"10. Logout\n";
    cout<<"=========================\n";
}

// ============== FR-02: Quiz Management ==============
void createQuiz(const User& teacher)
{
    cout<<"\n----- CREATE NEW QUIZ -----\n";
    
    int id;
    string title, description;
    int timeLimit;
    
    cout<<"Quiz ID: ";
    cin>>id;
    cin.ignore();
    for(const auto& q : quizzes)
    {
        if(q.id == id)
        {
            cout<<"ERROR: Quiz ID already exists\n";
            return;
        }
    }
    cout<<"Quiz Title (required): ";
    getline(cin, title);
    if(title.empty())
    {
        cout<<"ERROR: Title is required\n";
        return;
    }
    
    cout<<"Description: ";
    getline(cin, description);
    
    cout<<"Time Limit (minutes, > 0): ";
    cin>>timeLimit;
    if(timeLimit <= 0)
    {
        cout<<"ERROR: Invalid time limit (must be > 0)\n";
        return;
    }
    
    Quiz newQuiz;
    newQuiz.id = id;
    newQuiz.title = title;
    newQuiz.description = description;
    newQuiz.timeLimit = timeLimit;
    newQuiz.totalQuestions = 0;
    newQuiz.isActive = true;
    newQuiz.createdBy = teacher.username;
    
    quizzes.push_back(newQuiz);
    cout<<"Quiz created successfully! Quiz ID: "<<id<<"\n";
}

// ============== FR-03: Question Management ==============
void createQuestion(const User& teacher)
{
    cout<<"\n----- CREATE NEW QUESTION -----\n";
    
    if(quizzes.empty())
    {
        cout<<"ERROR: No quizzes available. Please create a quiz first.\n";
        return;
    }
    
    cout<<"Available Quizzes:\n";
    for(const auto& quiz : quizzes)
    {
        cout<<"ID: "<<quiz.id<<" - "<<quiz.title<<"\n";
    }
    
    int quizId;
    cout<<"Select Quiz ID: ";
    cin>>quizId;
    cin.ignore();
    
    auto quiz = find_if(quizzes.begin(), quizzes.end(),
                    [quizId](const Quiz& q){ return q.id == quizId; });
    if(quiz == quizzes.end())
    {
        cout<<"ERROR: Quiz not found\n";
        return;
    }
    if(!quiz->isActive)
    {
        cout<<"ERROR: Quiz is not active\n";
        return;
    }
    
    Question q;
    q.quizId = quizId;
    
    cout<<"Question ID: ";
    cin>>q.id;
    cin.ignore();
    for(const auto& question : quizQuestions)
    {
        if(question.id == q.id)
        {
            cout<<"ERROR: Question ID already exists\n";
            return;
        }
    }
    cout<<"Question text (required): ";
    getline(cin, q.text);
    if(q.text.empty())
    {
        cout<<"ERROR: Question content is required\n";
        return;
    }
    
    cout<<"Option A: ";
    getline(cin, q.A);
    cout<<"Option B: ";
    getline(cin, q.B);
    cout<<"Option C: ";
    getline(cin, q.C);
    cout<<"Option D: ";
    getline(cin, q.D);
    
    if(q.A.empty() || q.B.empty() || q.C.empty() || q.D.empty())
    {
        cout<<"ERROR: All options are required\n";
        return;
    }
    
    cout<<"Correct option (1-4): ";
    cin>>q.correct;
    
    if(q.correct < 1 || q.correct > 4)
    {
        cout<<"ERROR: Correct option must be 1-4\n";
        return;
    }
    
    quizQuestions.push_back(q);
    quiz->totalQuestions++;
    
    cout<<"Question created successfully!\n";
}

// ============== FR-04 & FR-05: Take Quiz & Submit ==============
void takeQuiz(User user,
            AttemptService &attemptService,
            ResultService &resultService)
{
    cout<<"\n----- TAKE QUIZ -----\n";
    
    if(quizzes.empty())
    {
        cout<<"ERROR: No quizzes available\n";
        return;
    }
    
    cout<<"Available Quizzes:\n";
    for(const auto& quiz : quizzes)
    {
        cout<<"ID: "<<quiz.id<<" - "<<quiz.title<<" ("<<quiz.totalQuestions<<" questions)\n";
    }
    
    int quizId;
    cout<<"Select Quiz ID: ";
    cin>>quizId;
    
    auto quiz = find_if(quizzes.begin(), quizzes.end(),
                    [quizId](const Quiz& q){ return q.id == quizId; });
    if(quiz == quizzes.end())
    {
        cout<<"ERROR: Quiz not found\n";
        return;
    }
    if(!quiz->isActive)
    {
        cout<<"ERROR: Quiz is not active\n";
        return;
    }
    
    // FR-14: Check attempt limit
    if(userAttemptCount[user.user_id] >=3)
    {
        cout<<"ERROR: Maximum attempts reached\n";
        return;
    }
    userAttemptCount[user.user_id]++;
    
    vector<Question> quizQuestionsList;
    for(const auto& q : quizQuestions)
    {
        if(q.quizId == quizId)
            quizQuestionsList.push_back(q);
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(quizQuestionsList.begin(), quizQuestionsList.end(), g);
    if(quizQuestionsList.empty())
    {
        cout<<"ERROR: Quiz has no questions\n";
        return;
    }
    
    int attemptId = attemptRecords.size() + 1;

    Attempt attempt =
        attemptService.startAttempt(
            attemptId,
            user.user_id,
            quizId
        );
    
    auto start = steady_clock::now();
    int timeLimit = quiz->timeLimit * 60; // Convert to seconds
    
    // FR-09: Timer System
    cout<<"\nQuiz starts! Time limit: "<<quiz->timeLimit<<" minutes\n";
    
    for(auto &q : quizQuestionsList)
    {
        auto now = steady_clock::now();
        int elapsed = duration_cast<seconds>(now-start).count();
        int remaining = timeLimit - elapsed;
        
        if(remaining <= 0)
        {
            cout<<"\nERROR: Time is up - Quiz auto-submitted\n";
            break;
        }
        
        cout<<"\nTime remaining: "<<remaining<<" seconds\n";
        cout<<q.text<<"\n";
        cout<<"1. "<<q.A<<"\n";
        cout<<"2. "<<q.B<<"\n";
        cout<<"3. "<<q.C<<"\n";
        cout<<"4. "<<q.D<<"\n";
        
        int ans;
        cout<<"Your answer (1-4, 0=skip): ";
        cin>>ans;
        
        if(ans < 0 || ans > 4)
        {
            cout<<"Invalid answer - skipped\n";
            continue;
        }
        if(ans == 0)
        {
            cout<<"Question skipped\n";
            continue;
        }
        
        // FR-15: Auto Save
        if(ans > 0)
        {
            attemptService.saveAnswer(attempt, q.id, ans);
        }
    }
    
    attemptService.submitAttempt(attempt);
    
    // FR-06: Auto Grading & FR-07: View Result
    int score = attempt.getScore();
    int maxScore = quizQuestionsList.size();
    
    QuizAttemptRecord record;
    record.attemptId = attempt.getAttemptId();
    record.userId = user.user_id;
    record.quizId = quizId;
    record.score = score;
    record.maxScore = maxScore;
    record.attemptCount = userAttemptCount[user.user_id];
    time_t now = time(0);
    string timeStr = ctime(&now);
    timeStr.pop_back(); // remove newline
    record.submissionTime = timeStr;
    
    attemptRecords.push_back(record);
    
    cout<<"\n===== QUIZ RESULT =====\n";
    cout<<"Quiz: "<<quiz->title<<"\n";
    cout<<"Score: "<<score<<"/"<<maxScore<<"\n";
    cout<<"Percentage: "<<(maxScore > 0 ? (score*100)/maxScore : 0)<<"%\n";
    cout<<"=======================\n";
}

// ============== FR-07: View Results ==============
void viewResults(const User& user)
{
    cout<<"\n----- YOUR RESULTS -----\n";
    
    vector<QuizAttemptRecord> userRecords;
    for(const auto& record : attemptRecords)
    {
        if(record.userId == user.user_id)
            userRecords.push_back(record);
    }
    
    if(userRecords.empty())
    {
        cout<<"No results available\n";
        return;
    }
    
    for(const auto& record : userRecords)
    {
        auto quiz = find_if(quizzes.begin(), quizzes.end(),
                        [record](const Quiz& q){ return q.id == record.quizId; });
        
        cout<<"\nAttempt #"<<record.attemptCount<<"\n";
        if(quiz != quizzes.end())
            cout<<"Quiz: "<<quiz->title<<"\n";
        cout<<"Score: "<<record.score<<"/"<<record.maxScore<<"\n";
        cout<<"Percentage: "<<(record.maxScore > 0 ? (record.score*100)/record.maxScore : 0)<<"%\n";
        cout<<"Time: "<<record.submissionTime<<"\n";
    }
}

// ============== FR-17: Reporting & Export ==============
void generateReport(const User& admin)
{
    cout<<"\n----- SYSTEM REPORT -----\n";
    cout<<"Total Quizzes: "<<quizzes.size()<<"\n";
    cout<<"Total Questions: "<<quizQuestions.size()<<"\n";
    cout<<"Total Attempts: "<<attemptRecords.size()<<"\n";
    
    if(!attemptRecords.empty())
    {
        cout<<"\nAttempt Details:\n";
        for(const auto& record : attemptRecords)
        {
            cout<<"UserID: "<<record.userId<<" | Score: "<<record.score<<"/"<<record.maxScore<<"\n";
        }
    }
    cout<<"=========================\n";
}

// ============== FR-12: Change Password ==============
void changePassword(User& user, AuthService& authService)
{
    cout<<"\n----- CHANGE PASSWORD -----\n";
    
    string oldPassword, newPassword, confirmPassword;
    
    cout<<"Current Password: ";
    cin>>oldPassword;
    
    // Verify old password (simplified)
    if(oldPassword != user.password)
    {
        cout<<"ERROR: Incorrect current password\n";
        return;
    }
    
    cout<<"New Password: ";
    cin>>newPassword;
    
    if(!isValidPassword(newPassword))
    {
        cout<<"ERROR: Password must be at least 8 characters\n";
        return;
    }
    
    if(newPassword == oldPassword)
    {
        cout<<"ERROR: New password must be different from old password\n";
        return;
    }
    
    cout<<"Confirm Password: ";
    cin>>confirmPassword;
    
    if(newPassword != confirmPassword)
    {
        cout<<"ERROR: Passwords do not match\n";
        return;
    }
    
    user.password = newPassword;
    cout<<"Password changed successfully!\n";
}

// ============== FR-22: User Profile Management ==============
void viewProfile(const User& user)
{
    cout<<"\n----- USER PROFILE -----\n";
    cout<<"Username: "<<user.username<<"\n";
    cout<<"Email: "<<user.email<<"\n";
    cout<<"Role: "<<user.role<<"\n";
    cout<<"User ID: "<<user.user_id<<"\n";
    cout<<"========================\n";
}

void editProfile(User& user)
{
    cout<<"\n----- EDIT PROFILE -----\n";
    cout<<"1. Change Email\n";
    cout<<"2. View Profile\n";
    cout<<"0. Cancel\n";
    
    int choice;
    cin>>choice;
    cin.ignore();
    
    if(choice == 1)
    {
        cout<<"New Email: ";
        string newEmail;
        getline(cin, newEmail);
        
        if(!isValidEmail(newEmail))
        {
            cout<<"ERROR: Invalid email format\n";
            return;
        }
        
        user.email = newEmail;
        cout<<"Email updated successfully!\n";
    }
    else if(choice == 2)
    {
        viewProfile(user);
    }
}

// ============== FR-21: View Notifications ==============
void viewNotifications(const User& user, NotificationService& notificationService)
{
    cout<<"\n----- YOUR NOTIFICATIONS -----\n";
    
    auto list = notificationService.getNotifications(user.user_id);
    
    if(list.empty())
    {
        cout<<"No notifications available\n";
    }
    else
    {
        for(const auto &n : list)
        {
            cout<<"- "<<n.content<<" (Read: "<<(n.is_read ? "Yes" : "No")<<")\n";
        }
    }
    cout<<"================================\n";
}

// ============== FR-08: Question Management Functions ==============
void viewQuestions(const User& teacher)
{
    cout<<"\n----- VIEW QUESTIONS -----\n";
    
    if(quizQuestions.empty())
    {
        cout<<"No questions available\n";
        return;
    }
    
    for(const auto& q : quizQuestions)
    {
        cout<<"\nQuestion ID: "<<q.id<<" (Quiz "<<q.quizId<<")\n";
        cout<<"Text: "<<q.text<<"\n";
        cout<<"Options: A) "<<q.A<<" | B) "<<q.B<<" | C) "<<q.C<<" | D) "<<q.D<<"\n";
        cout<<"Correct: "<<q.correct<<"\n";
    }
}

// FR-20: Edit Answer
void editQuestion(const User& teacher)
{
    cout<<"\n----- EDIT QUESTION -----\n";
    
    int questionId;
    cout<<"Enter Question ID: ";
    cin>>questionId;
    cin.ignore();
    
    auto it = find_if(quizQuestions.begin(), quizQuestions.end(),
                     [questionId](const Question& q){ return q.id == questionId; });
    
    if(it == quizQuestions.end())
    {
        cout<<"ERROR: Question not found\n";
        return;
    }
    
    cout<<"\n1. Edit Text\n";
    cout<<"2. Edit Options\n";
    cout<<"3. Edit Correct Answer\n";
    cout<<"0. Cancel\n";
    
    int choice;
    cin>>choice;
    cin.ignore();
    
    if(choice == 1)
    {
        cout<<"New question text: ";
        getline(cin, it->text);
        cout<<"Updated!\n";
    }
    else if(choice == 2)
    {
        cout<<"New Option A: ";
        getline(cin, it->A);
        cout<<"New Option B: ";
        getline(cin, it->B);
        cout<<"New Option C: ";
        getline(cin, it->C);
        cout<<"New Option D: ";
        getline(cin, it->D);
        cout<<"Updated!\n";
    }
    else if(choice == 3)
    {
        cout<<"New Correct Answer (1-4): ";
        cin>>it->correct;
        cout<<"Updated!\n";
    }
}

// FR-18: Delete Question
void deleteQuestion(const User& teacher)
{
    cout<<"\n----- DELETE QUESTION -----\n";
    
    int questionId;
    cout<<"Enter Question ID to delete: ";
    cin>>questionId;
    
    auto it = find_if(quizQuestions.begin(), quizQuestions.end(),
                    [questionId](const Question& q){ return q.id == questionId; });
    
    if(it == quizQuestions.end())
    {
        cout<<"ERROR: Question not found\n";
        return;
    }
    for(auto& quiz : quizzes)
    {
    if(quiz.id == it->quizId)
        quiz.totalQuestions--;
    }
    quizQuestions.erase(it);
    cout<<"Question deleted successfully!\n";
}

// ============== MAIN APPLICATION ==============
int main()
{
    UserRepositoryMemory userRepo;
    NotificationRepositoryMemory notificationRepo;

    AuthService authService(&userRepo);
    UserService userService(&userRepo);
    NotificationService notificationService(&notificationRepo);

    GradingService gradingService;
    ResultService resultService;
    AttemptService attemptService(&gradingService,&resultService);

    User currentUser;
    bool logged=false;
    
    cout<<"==============================================\n";
    cout<<"        QUIZ EXAMINATION SYSTEM v1.1         \n";
    cout<<"==============================================\n";

    while(true)
    {
        if(!logged)
        {
            guestMenu();

            int c;
            cout<<"Select: ";
            cin>>c;

            if(c==0)
            {
                cout<<"Goodbye!\n";
                break;
            }

            if(c==1)
            {
                cout<<"\n----- REGISTER NEW ACCOUNT -----\n";
                
                int id;
                string username,email,password,role;

                cout<<"User ID: ";
                cin>>id;
                cin.ignore();
                

                cout<<"Username: ";
                getline(cin,username);
                
                if(!isValidUsername(username))
                {
                    cout<<"ERROR: Username must be at least 3 characters\n";
                    continue;
                }

                cout<<"Email: ";
                getline(cin,email);
                
                if(!isValidEmail(email))
                {
                    cout<<"ERROR: Invalid email format\n";
                    continue;
                }

                cout<<"Password: ";
                cin>>password;
                
                if(!isValidPassword(password))
                {
                    cout<<"ERROR: Password must be at least 8 characters\n";
                    continue;
                }

                cout<<"Role(student/teacher/admin): ";
                cin>>role;
                if(role!="student" && role!="teacher" && role!="admin")
                {
                    cout<<"ERROR: Invalid role\n";
                    pauseScreen();
                    continue;
                }

                User u(id,username,email,password,role,true);

                try
                {
                    authService.registerUser(u);
                    cout<<" Register success!\n";
                    pauseScreen();
                }
                catch(const exception& e)
                {
                    cout<<"ERROR: "<<e.what()<<"\n";
                    pauseScreen();
                }
            }

            else if(c==2)
            {
                cout<<"\n----- LOGIN -----\n";
                
                string u,p;

                cout<<"Username: ";
                cin>>u;

                cout<<"Password: ";
                cin>>p;

                try
                {
                    currentUser = authService.login(u,p);
                    logged=true;
                    cout<<" Login success! Welcome "<<currentUser.username<<"\n";
                    pauseScreen();
                    clearScreen();
                }
                catch(const exception& e)
                {
                    cout<<"ERROR: Login failed\n";
                }
            }
        }

        else
        {
            // FR-11: Role-based Access Control
            if(currentUser.role=="student")
            {
                studentMenu();

                int c;
                cout<<"Select: ";
                cin>>c;

                if(c==1){
                    takeQuiz(currentUser, attemptService, resultService);
                    pauseScreen();
                }

                else if(c==2){
                    viewResults(currentUser);
                    pauseScreen();
                }

                else if(c==3){
                    viewNotifications(currentUser, notificationService);
                    pauseScreen();
                }

                else if(c==4){
                    changePassword(currentUser, authService);
                    pauseScreen();
                }

                else if(c==5){
                    viewProfile(currentUser);
                    pauseScreen();
                }
                else if(c==6)
                {
                    logged=false;
                    cout<<" Logged out successfully\n";
                }
            }

            else if(currentUser.role=="teacher")
            {
                teacherMenu();

                int c;
                cout<<"Select: ";
                cin>>c;

                if(c==1){
                    createQuiz(currentUser);
                    pauseScreen();
                }

                else if(c==2){
                    createQuestion(currentUser);
                    pauseScreen();
                }

                else if(c==3){
                    viewQuestions(currentUser);
                    pauseScreen();
                }

                else if(c==4){
                    editQuestion(currentUser);
                    pauseScreen();
                }

                else if(c==5){
                    deleteQuestion(currentUser);
                    pauseScreen();
                }

                else if(c==6)
                {
                    cout<<"\nAvailable Quizzes:\n";
                    for(const auto& q : quizzes)
                    {
                        cout<<"ID: "<<q.id<<" - "<<q.title<<" ("<<q.totalQuestions<<" Q)\n";
                    }
                    pauseScreen();
                }

                else if(c==7)
                {
                    if(attemptRecords.empty())
                    {
                        cout<<"No results available\n";
                    }
                    else
                    {
                        cout<<"\nQuiz Results:\n";
                        for(const auto& r : attemptRecords)
                        {
                            cout<<"User "<<r.userId<<": "<<r.score<<"/"<<r.maxScore<<"\n";
                        }
                    }
                    pauseScreen();
                }

                else if(c==8)
                {
                    int userId;
                    string msg;
                    
                    cout<<"User ID to notify: ";
                    cin>>userId;
                    cin.ignore();

                    cout<<"Message: ";
                    getline(cin,msg);

                    Notification n(0,userId,msg);
                    notificationService.sendNotification(n);
                    
                    cout<<" Notification sent!\n";
                    pauseScreen();
                }

                else if(c==9){
                    changePassword(currentUser, authService);
                    pauseScreen();
                }

                else if(c==10)
                {
                    logged=false;
                    cout<<" Logged out successfully\n";
                }
            }

            else if(currentUser.role=="admin")
            {
                adminMenu();

                int c;
                cout<<"Select: ";
                cin>>c;

                if(c==1)
                {
                    cout<<"\nAll Users (stored in repository):\n";
                }

                else if(c==2)
                {
                    cout<<"\nUser management would delete users from repository\n";
                }

                else if(c==3)
                {
                    generateReport(currentUser);
                    pauseScreen();
                }

                else if(c==4)
                {
                    cout<<"\n----- SYSTEM STATISTICS -----\n";
                    cout<<"Total Users: "<<"(tracked in repository)\n";
                    cout<<"Total Quizzes: "<<quizzes.size()<<"\n";
                    cout<<"Total Questions: "<<quizQuestions.size()<<"\n";
                    cout<<"Total Attempts: "<<attemptRecords.size()<<"\n";
                    cout<<"============================\n";
                    pauseScreen();
                }

                else if(c==5)
                {
                    logged=false;
                    cout<<" Logged out successfully\n";
                }
            }
        }
    }

    cout<<"\n System shutdown complete.\n";
    return 0;
}