/**
 * @file OrderManager.cpp
 * @brief Implementation of the OrderManager class for order data management and analytics.
 *
 * This file contains the implementation of order loading, saving, and analytics
 * functions. It handles CSV file operations and provides business intelligence
 * features like popular product identification and order summaries.
 */

#include "OrderManager.h"
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QDate>
#include <QPair>
#include <QList>
#include <QMap>
#include <QtGlobal>
#include <QtCore/qmath.h>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

/**
 * @brief Constructs an OrderManager with the specified file path.
 * @param filePath Path to the CSV file for order storage.
 */
OrderManager::OrderManager(const QString &filePath)
    : filePath(filePath)
{
}

/**
 * @brief Loads all orders from the CSV file.
 *
 * Reads the CSV file line by line, parses each line into an Order struct,
 * and returns a list of all orders.
 *
 * @return A list of all orders in the file.
 */
QList<Order> OrderManager::loadOrders() const
{
    QList<Order> orders;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return orders;

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;
        orders.append(parseOrderLine(line));
    }

    file.close();
    return orders;
}

/**
 * @brief Saves all orders to the CSV file (overwrites existing file).
 *
 * Writes each order as a formatted CSV line to the file.
 * This operation truncates the existing file.
 *
 * @param orders The list of orders to save.
 * @return True if saving was successful, false otherwise.
 */
bool OrderManager::saveOrders(const QList<Order> &orders) const
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return false;

    QTextStream out(&file);
    for (const Order &order : orders)
        out << formatOrderLine(order) << "\n";

    file.close();
    return true;
}

/**
 * @brief Appends new orders to the existing CSV file.
 *
 * Adds new orders to the end of the file without overwriting existing data.
 *
 * @param orders The list of orders to append.
 * @return True if appending was successful, false otherwise.
 */
bool OrderManager::appendOrders(const QList<Order> &orders) const
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        return false;

    QTextStream out(&file);
    for (const Order &order : orders)
        out << formatOrderLine(order) << "\n";

    file.close();
    return true;
}

/**
 * @brief Counts orders per product.
 * @param orders The list of orders to analyze.
 * @return A map of product names to order counts.
 */
QMap<QString, int> OrderManager::ordersPerProduct(const QList<Order> &orders) const
{
    QMap<QString, int> counts;
    for (const Order &order : orders)
        counts[QString::fromStdString(order.product)] += order.quantity;
    return counts;
}

QStringList OrderManager::popularProducts(const QList<Order> &orders, int topPercent) const
{
    QMap<QString, int> counts = ordersPerProduct(orders);
    QList<QPair<QString, int>> products;
    for (auto it = counts.constBegin(); it != counts.constEnd(); ++it)
        products.append(QPair<QString, int>(it.key(), it.value()));

    // ===== SORTING: Order products by frequency (highest first) =====
    sort(products.begin(), products.end(), [](const QPair<QString, int> &a, const QPair<QString, int> &b)
         { return a.second > b.second; });

    // ===== CALCULATION: Determine top N products to return =====
    // topPercent parameter (default 5%) determines cutoff
    // Example: 20 total products * 5% = top 1 product
    // At least 1 product is always returned if any exist
    int distinctCount = products.size();
    if (distinctCount == 0)
        return {};

    int topCount = qMax(1, static_cast<int>(ceil(distinctCount * topPercent / 100.0)));
    QStringList popular;

    // ===== FORMATTING: Build display strings =====
    // Each line shows: "ProductName (X orders)"
    for (int i = 0; i < topCount && i < products.size(); ++i)
        popular.append(products[i].first + " (" + QString::number(products[i].second) + " orders)");

    return popular;
}

/**
 * @brief Generates weekly and yearly order analytics for admin dashboard
 * @param orders The list of orders to analyze.
 * @return A pair containing weekly summary and yearly summary strings.
 */
QPair<QString, QString> OrderManager::analyticsThisWeekAndYear(const QList<Order> &orders) const
{
    QDate today = QDate::currentDate();
    int thisWeek = 0;
    int thisYear = 0;
    double thisWeekRevenue = 0.0;
    double thisYearRevenue = 0.0;

    // ===== CURRENT PERIOD IDENTIFICATION =====
    int currentWeekNumber = today.weekNumber();
    int currentYear = today.year();

    // ===== ANALYSIS: Iterate through all orders =====
    for (const Order &order : orders)
    {
        // Skip invalid dates
        if (!order.date.isValid())
            continue;

        int orderWeekNumber = order.date.weekNumber();
        int orderYear = order.date.year();

        // ===== YEARLY ACCUMULATION =====
        // Count all orders placed in the current year
        if (orderYear == currentYear)
        {
            thisYear++;
            thisYearRevenue += order.total;

            // ===== WEEKLY ACCUMULATION =====
            // Count orders placed in the current week
            // A week is determined by ISO 8601 week number
            if (orderWeekNumber == currentWeekNumber)
            {
                thisWeek++;
                thisWeekRevenue += order.total;
            }
        }
    }

    // ===== FORMATTING: Create display strings =====
    QString weekSummary = QString("Orders this week: %1, revenue: $%2")
                              .arg(thisWeek)
                              .arg(QString::number(thisWeekRevenue, 'f', 2));
    QString yearSummary = QString("Orders this year: %1, revenue: $%2")
                              .arg(thisYear)
                              .arg(QString::number(thisYearRevenue, 'f', 2));

    return QPair<QString, QString>(weekSummary, yearSummary);
}

/**
 * @brief Formats a date for display.
 *
 * Converts a QDate to ISO date string format.
 *
 * @param date The date to format.
 * @return Formatted date string, or empty string if invalid.
 */
QString OrderManager::formatDate(const QDate &date)
{
    if (date.isValid())
        return date.toString(Qt::ISODate);
    return QString();
}

/**
 * @brief Formats an order into a CSV line.
 * @param order The order to format.
 * @return CSV-formatted string.
 */
QString OrderManager::formatOrderLine(const Order &order) const
{
    return QString("%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11")
        .arg(order.orderId)
        .arg(QString::fromStdString(order.username))
        .arg(QString::fromStdString(order.product))
        .arg(order.quantity)
        .arg(order.total, 0, 'f', 2)
        .arg(QString::fromStdString(order.status))
        .arg(QString::fromStdString(order.address))
        .arg(QString::fromStdString(order.city))
        .arg(order.deliveryFee, 0, 'f', 2)
        .arg(formatDate(order.date))
        .arg(QString::fromStdString(order.paymentMethod));
}

/**
 * @brief Parses a CSV line into an Order struct.
 * @param line The CSV line to parse.
 * @return Parsed Order struct.
 */
Order OrderManager::parseOrderLine(const QString &line) const
{
    Order order;
    QStringList fields = line.split(',');
    if (fields.size() < 10)
        return order;

    order.orderId = fields[0].toInt();
    order.username = fields[1].toStdString();
    order.product = fields[2].toStdString();
    order.quantity = fields[3].toInt();
    order.total = fields[4].toDouble();
    order.status = fields[5].toStdString();
    order.address = fields[6].toStdString();
    order.city = fields[7].toStdString();
    order.deliveryFee = fields[8].toDouble();

    if (fields.size() > 9)
    {
        order.date = QDate::fromString(fields[9], Qt::ISODate);
    }

    // ===== PARSE PAYMENT METHOD (Version 4 - 11 fields) =====
    // Added payment method information for order tracking
    if (fields.size() >= 11)
    {
        order.paymentMethod = fields[10].toStdString();
    }

    return order;
}
