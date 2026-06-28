#ifndef CART_H
#define CART_H
#include <string>
#include <QList>
#include <QString>
using namespace std;

class Cart
{
private:
    QList<QString> items;

public:
    Cart() {}
    void addItem(const string &item);
    void removeItem(const string &item);
    void displayCart() const;
    void clearCart();
    void saveToFile(const string &filename);
    void loadFromFile(const string &filename);
    QList<QString> getItems() const;
    void setItems(const QList<QString> &newItems);
};

#endif // CART_H