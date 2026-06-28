#include "Cart.h"
#include <iostream>
#include <fstream>
#include <QDebug>

void Cart::addItem(const string &item)
{
    if (items.size() < 100)
    {
        items.append(QString::fromStdString(item));
        cout << item << " added to cart." << endl;
    }
}

void Cart::removeItem(const string &item)
{
    QString qitem = QString::fromStdString(item);
    if (items.removeOne(qitem))
    {
        cout << item << " removed from cart." << endl;
    }
    else
    {
        cout << item << " not found in cart." << endl;
    }
}

void Cart::displayCart() const
{
    cout << "Cart contents:" << endl;
    for (const QString &item : items)
    {
        cout << "- " << item.toStdString() << endl;
    }
}

void Cart::clearCart()
{
    items.clear();
    cout << "Cart cleared." << endl;
}

void Cart::saveToFile(const string &filename)
{
    ofstream file(filename);
    for (const QString &item : items)
    {
        file << item.toStdString() << endl;
    }
}

void Cart::loadFromFile(const string &filename)
{
    ifstream file(filename);
    string line;
    items.clear();
    while (getline(file, line))
    {
        items.append(QString::fromStdString(line));
    }
}

QList<QString> Cart::getItems() const
{
    return items;
}

void Cart::setItems(const QList<QString> &newItems)
{
    items = newItems;
}