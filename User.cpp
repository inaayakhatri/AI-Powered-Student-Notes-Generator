#include "User.h"
#include "Admin.h"
#include "Customer.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
using namespace std;

User *User::registeredUsers[100];
int User::userCount = 0;
static string usersFilePath = "users.csv";

static string resolveDataFilePath(const string &filename)
{
    QString qFilename = QString::fromStdString(filename); 
    QString appDir = QCoreApplication::applicationDirPath(); // getting app directory
    QDir dir(appDir);
    QString pathInAppDir = dir.filePath(qFilename); // mwking the file path
    if (QFileInfo::exists(pathInAppDir)) // if file exists
        return pathInAppDir.toStdString();
    QString pathInParent = dir.absoluteFilePath("../" + qFilename); // trying parent directory
    if (QFileInfo::exists(pathInParent))
        return pathInParent.toStdString();
    return filename;
}

User::User(const string &uname, const string &pwd) : username(uname), password(pwd) {}

string User::getUsername() const
{
    return username;
}

bool User::checkPassword(const string &pwd) const
{
    return password == pwd;
}

bool User::login(const string &pass) const
{
    return checkPassword(pass);
}

bool User::changePassword(const string &newpass, string &outMessage)
{
    if (!isStrongPassword(newpass))
    {
        outMessage = "Password is not strong enough.";
        return false;
    }
    password = newpass;
    saveUsers();
    outMessage = "Password changed successfully.";
    return true;
}

bool User::isStrongPassword(const string &pass)
{
    if (pass.length() < 8)
        return false;
    bool hasUpper = false, hasLower = false, hasDigit = false;
    for (char c : pass)
    {
        if (isupper(c))
            hasUpper = true;
        else if (islower(c))
            hasLower = true;
        else if (isdigit(c))
            hasDigit = true;
    }
    return hasUpper && hasLower && hasDigit;
}

bool User::registerUser(const string &uname, const string &pwd, User *user)
{
    if (userCount >= 100 || !user)
        return false;
    for (int i = 0; i < userCount; ++i)
    {
        if (registeredUsers[i] && registeredUsers[i]->getUsername() == uname)
            return false;
    }
    registeredUsers[userCount] = user;
    userCount++;
    saveUsers();
    return true;
}

User *User::findUser(const string &uname)
{
    for (int i = 0; i < userCount; ++i)
    {
        if (registeredUsers[i] && registeredUsers[i]->getUsername() == uname)
        {
            return registeredUsers[i];
        }
    }
    return nullptr;
}

void User::loadUsers()
{
    usersFilePath = resolveDataFilePath("users.csv");
    ifstream file(usersFilePath);
    if (!file)
        return;
    string line;
    userCount = 0;
    while (getline(file, line) && userCount < 100)
    {
        size_t pos1 = line.find(',');
        if (pos1 == string::npos) // no position 
            continue;
        size_t pos2 = line.find(',', pos1 + 1);
        if (pos2 == string::npos)
            continue;
        string uname = line.substr(0, pos1);
        string pwd = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string roleStr = line.substr(pos2 + 1);
        int role = stoi(roleStr);
        if (role == 1)
            registeredUsers[userCount] = new Admin(uname, pwd);
        else
            registeredUsers[userCount] = new Customer(uname, pwd);
        userCount++;
    }
}

void User::saveUsers()
{
    ofstream file(usersFilePath.empty() ? "users.csv" : usersFilePath);
    for (int i = 0; i < userCount; ++i)
    {
        if (registeredUsers[i])
            file << registeredUsers[i]->getUsername() << "," << registeredUsers[i]->password << "," << registeredUsers[i]->getRole() << endl;
    }
}

void User::displayMenu()
{
}

User *User::authenticate(const string &uname, const string &pwd)
{
    for (int i = 0; i < userCount; ++i)
    {
        if (registeredUsers[i] && registeredUsers[i]->getUsername() == uname)
        {
            if (registeredUsers[i]->checkPassword(pwd))
                return registeredUsers[i];
            return nullptr;
        }
    }
    return nullptr;
}

QList<QPair<QString, int>> User::getAllUsers() // cuz the list contains names with either cutomer or admin
{
    QList<QPair<QString, int>> users;
    for (int i = 0; i < userCount; ++i)
    {
        if (registeredUsers[i])
            users.append(qMakePair(QString::fromStdString(registeredUsers[i]->getUsername()), registeredUsers[i]->getRole()));
    }
    return users;
}

bool User::deleteUser(const string &uname)
{
    for (int i = 0; i < userCount; ++i)
    {
        if (registeredUsers[i] && registeredUsers[i]->getUsername() == uname)
        {
            delete registeredUsers[i];
            for (int j = i; j < userCount - 1; ++j)
            {
                registeredUsers[j] = registeredUsers[j + 1];
            }
            registeredUsers[--userCount] = nullptr;
            saveUsers();
            return true;
        }
    }
    return false;
}