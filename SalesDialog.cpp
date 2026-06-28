#include "SalesDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <fstream>
#include <QString>
#include <QStringList>

SalesDialog::SalesDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Sales Summary - ShopBuddy Admin");
    setModal(true);
    setMinimumWidth(400);
    setMinimumHeight(300);
    setupUI();
    loadSalesData();
}

SalesDialog::~SalesDialog()
{
}

void SalesDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Sales Summary");
    titleLabel->setStyleSheet("font-weight: bold; font-size: 16px;");
    mainLayout->addWidget(titleLabel);

    mainLayout->addSpacing(10);

    // Sales metrics
    QGroupBox *metricsBox = new QGroupBox("Metrics");
    QVBoxLayout *metricsLayout = new QVBoxLayout(metricsBox);

    totalRevenueLabel = new QLabel("Total Revenue: $0.00");
    totalOrdersLabel = new QLabel("Total Orders: 0");
    pendingOrdersLabel = new QLabel("Pending Orders: 0");
    completedOrdersLabel = new QLabel("Completed Orders: 0");
    averageOrderLabel = new QLabel("Average Order Value: $0.00");

    metricsLayout->addWidget(totalRevenueLabel);
    metricsLayout->addWidget(totalOrdersLabel);
    metricsLayout->addWidget(pendingOrdersLabel);
    metricsLayout->addWidget(completedOrdersLabel);
    metricsLayout->addWidget(averageOrderLabel);

    mainLayout->addWidget(metricsBox);
    mainLayout->addStretch();

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    refreshBtn = new QPushButton("Refresh");
    closeBtn = new QPushButton("Close");
    buttonLayout->addWidget(refreshBtn);
    buttonLayout->addWidget(closeBtn);
    mainLayout->addLayout(buttonLayout);

    connect(refreshBtn, &QPushButton::clicked, this, &SalesDialog::loadSalesData);
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);
}

void SalesDialog::loadSalesData()
{
    double totalRevenue = 0.0;
    int totalOrders = 0;
    int pendingOrders = 0;
    int completedOrders = 0;

    std::ifstream ordersFile("orders.csv");
    std::string line;
    while (std::getline(ordersFile, line))
    {
        if (line.empty())
            continue;

        QStringList fields = QString::fromStdString(line).split(',');
        if (fields.size() >= 6)
        {
            totalOrders++;
            try
            {
                double amount = fields[4].toDouble();
                totalRevenue += amount;
                QString status = fields[5];
                if (status == "Pending")
                    pendingOrders++;
                else if (status == "Completed")
                    completedOrders++;
            }
            catch (...)
            {
                // Skip malformed lines
            }
        }
    }
    ordersFile.close();

    double averageOrder = (totalOrders > 0) ? (totalRevenue / totalOrders) : 0.0;

    totalRevenueLabel->setText("Total Revenue: $" + QString::number(totalRevenue, 'f', 2));
    totalOrdersLabel->setText("Total Orders: " + QString::number(totalOrders));
    pendingOrdersLabel->setText("Pending Orders: " + QString::number(pendingOrders));
    completedOrdersLabel->setText("Completed Orders: " + QString::number(completedOrders));
    averageOrderLabel->setText("Average Order Value: $" + QString::number(averageOrder, 'f', 2));
}
