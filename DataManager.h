#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QDate>
#include <QList>
#include <QString>
#include <QStringList>
#include <string>

using namespace std;

/**
 * Represents an order in the e-commerce system.
 * Contains all information about a customer's order including
 * product details, delivery information, and payment method.
 */
struct Order
{
    int orderId;
    string username;
    string product;
    int quantity;
    double total;
    string status;
    string address;
    string city;
    double deliveryFee;
    QDate date;
    string paymentMethod;
};

/**
 * Abstract base class for data management operations.
 * Defines the interface for loading and saving order data.
 */
class DataManager
{
public:
    virtual ~DataManager() = default;

    virtual QList<Order> loadOrders() const = 0;
    virtual bool saveOrders(const QList<Order> &orders) const = 0;
};

#endif
