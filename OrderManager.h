#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include "DataManager.h"
#include <QList>
#include <QMap>
#include <QString>
#include <QStringList>
#include <string>

/**
 * @brief Manages order data operations and analytics.
 *
 * Handles loading/saving orders from CSV files and provides
 * analytics functions for popular products and order summaries.
 */
class OrderManager : public DataManager
{
public:
    /**
     * @brief Constructs an OrderManager with the specified file path.
     * @param filePath Path to the CSV file for order storage.
     */
    explicit OrderManager(const QString &filePath = "orders.csv");

    /**
     * @brief Loads all orders from the CSV file.
     * @return A list of all orders in the file.
     */
    QList<Order> loadOrders() const override;

    /**
     * @brief Saves all orders to the CSV file (overwrites existing file).
     * @param orders The list of orders to save.
     * @return True if saving was successful, false otherwise.
     */
    bool saveOrders(const QList<Order> &orders) const override;

    /**
     * @brief Appends new orders to the existing CSV file.
     * @param orders The list of orders to append.
     * @return True if appending was successful, false otherwise.
     */
    bool appendOrders(const QList<Order> &orders) const;

    /**
     * @brief Counts orders per product.
     * @param orders The list of orders to analyze.
     * @return A map of product names to order counts.
     */
    QMap<QString, int> ordersPerProduct(const QList<Order> &orders) const;

    /**
     * @brief Identifies popular products based on order frequency.
     * @param orders The list of orders to analyze.
     * @param topPercent Percentage of top products to return (default 5%).
     * @return A list of popular product names with order counts.
     */
    QStringList popularProducts(const QList<Order> &orders, int topPercent = 5) const;

    /**
     * @brief Generates weekly and yearly order analytics.
     * @param orders The list of orders to analyze.
     * @return A pair containing weekly summary and yearly summary strings.
     */
    QPair<QString, QString> analyticsThisWeekAndYear(const QList<Order> &orders) const;

    /**
     * @brief Formats a date for display.
     * @param date The date to format.
     * @return Formatted date string.
     */
    static QString formatDate(const QDate &date);

private:
    /**
     * @brief Formats an order into a CSV line.
     * @param order The order to format.
     * @return CSV-formatted string.
     */
    QString formatOrderLine(const Order &order) const;

    /**
     * @brief Parses a CSV line into an Order struct.
     * @param line The CSV line to parse.
     * @return Parsed Order struct.
     */
    Order parseOrderLine(const QString &line) const;

    QString filePath; /**< Path to the CSV file for storage */
};

#endif // ORDERMANAGER_H
