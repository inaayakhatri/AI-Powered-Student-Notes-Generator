#include "Admin.h"
#include <iostream>
using namespace std;

Admin::Admin(const string &uname, const string &pwd) : User(uname, pwd) {}

int Admin::getRole() const
{
    return 1;
}

void Admin::displayMenu()
{
    cout << "Admin Menu:" << endl;
    cout << "1. Manage Users" << endl;
    cout << "2. View Reports" << endl;
    cout << "3. Logout" << endl;
}