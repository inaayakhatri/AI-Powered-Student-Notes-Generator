#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"

class Admin : public User
{
public:
    Admin(const string &uname = "", const string &pwd = "");
    int getRole() const override;
    void displayMenu() override;
};

#endif // ADMIN_H