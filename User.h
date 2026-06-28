#ifndef USER_H
#define USER_H
#include <string>
using namespace std;
#include <QList>
#include <QPair>
#include <QString>
#include <utility>

class User
{
private:
    static User *registeredUsers[100];
    static int userCount;

protected:
    string username;
    string password;

public:
    User(const string &uname = "", const string &pwd = "");
    virtual ~User() = default;

    string getUsername() const;
    bool checkPassword(const string &pwd) const;
    virtual int getRole() const = 0;

    bool login(const string &pass) const;
    bool changePassword(const string &newpass, string &outMessage);
    static bool isStrongPassword(const string &pass);
    static bool registerUser(const string &uname, const string &pwd, User *user);
    static User *findUser(const string &uname);
    static User *authenticate(const string &uname, const string &pwd);
    static void loadUsers();
    static void saveUsers();
    static QList<QPair<QString, int>> getAllUsers(); // username, role
    static bool deleteUser(const string &uname);

    virtual void displayMenu() = 0;
};
#endif