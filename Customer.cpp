#include "Customer.h"
#include <iostream>

using namespace std;

Customer::Customer(const string &uname, const string &pwd) : User(uname, pwd) {}

int Customer::getRole() const
{
    return 0; // ROLE_USER
}

void Customer::displayMenu()
{
    cout << "Customer Menu:" << endl;
    cout << "1. View Products" << endl;
    cout << "2. Add to Cart" << endl;
    cout << "3. Checkout" << endl;
    cout << "4. Logout" << endl;
}
