#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "User.h"

class Customer : public User
{
public:
    Customer(const string &uname = "", const string &pwd = "");
    int getRole() const override;
    void displayMenu() override;
};

#endif // CUSTOMER_H