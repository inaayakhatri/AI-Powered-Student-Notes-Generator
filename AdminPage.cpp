#include "AdminPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QTabWidget>
#include "Product.h"
#include "User.h"

AdminPage::AdminPage(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *adminLayout = new QVBoxLayout(this);

    adminLabel = new QLabel("Admin Dashboard");
    adminProfileLabel = new QLabel;
    adminProfileLabel->setAlignment(Qt::AlignCenter);
    adminProfileLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
    adminLabel->setAlignment(Qt::AlignCenter);
    adminLabel->setStyleSheet("font-size: 22px; font-weight: bold;");

    QLabel *nameLabel = new QLabel("Product Name:");
    productNameEdit = new QLineEdit;

    QLabel *priceLabel = new QLabel("Price:");
    productPriceEdit = new QLineEdit;

    productPriceEdit->setValidator(new QDoubleValidator(0.0, 9999999.99, 2, this));

    QLabel *qtyLabel = new QLabel("Quantity:");
    productQtyEdit = new QLineEdit;

    productQtyEdit->setValidator(new QIntValidator(0, 1000000, this));
    QLabel *descLabel = new QLabel("Description:");
    productDescEdit = new QLineEdit;

    productListWidget = new QListWidget;

    addProductBtn = new QPushButton("Add Product");
    removeProductBtn = new QPushButton("Remove Product");
    viewOrdersBtn = new QPushButton("View Orders");
    clearOrdersBtn = new QPushButton("Clear Finished Orders");
    cancelAllOrdersBtn = new QPushButton("Cancel All Orders");
    confirmOrderBtn = new QPushButton("Confirm Order");
    completeOrderBtn = new QPushButton("Complete Order");
    completeAllOrdersBtn = new QPushButton("Complete All Orders");
    cancelOrderBtn = new QPushButton("Cancel Order");
    deleteUserBtn = new QPushButton("Delete User");
    changePasswordBtn = new QPushButton("Change Password");
    salesSummaryBtn = new QPushButton("View Sales Summary");
    themeToggle = new QCheckBox("Dark Theme");
    logoutBtn = new QPushButton("Logout");

    connect(addProductBtn, &QPushButton::clicked, this, [this]()
            { emit addProductRequested(productNameEdit->text(), productDescEdit->text(), productPriceEdit->text(), productQtyEdit->text()); });
    connect(removeProductBtn, &QPushButton::clicked, this, [this]()
            {
        if (productListWidget->currentRow() >= 0) {
            QListWidgetItem *item = productListWidget->item(productListWidget->currentRow());
            if (item) {
                QString text = item->text();
                QString productName = text.section(". ", 1, 1).section(" - $", 0, 0);
                emit removeProductRequested(productName);
            }
        } });
    connect(viewOrdersBtn, &QPushButton::clicked, this, &AdminPage::viewOrdersRequested);
    connect(clearOrdersBtn, &QPushButton::clicked, this, &AdminPage::clearOrdersRequested);
    connect(cancelAllOrdersBtn, &QPushButton::clicked, this, &AdminPage::cancelAllOrdersRequested);
    connect(confirmOrderBtn, &QPushButton::clicked, this, &AdminPage::confirmOrderRequested);
    connect(completeOrderBtn, &QPushButton::clicked, this, &AdminPage::completeOrderRequested);
    connect(completeAllOrdersBtn, &QPushButton::clicked, this, &AdminPage::completeAllOrdersRequested);
    connect(cancelOrderBtn, &QPushButton::clicked, this, &AdminPage::cancelOrderRequested);
    connect(deleteUserBtn, &QPushButton::clicked, this, &AdminPage::deleteUserRequested);
    connect(changePasswordBtn, &QPushButton::clicked, this, &AdminPage::changePasswordRequested);
    connect(salesSummaryBtn, &QPushButton::clicked, this, &AdminPage::viewSalesSummaryRequested);
    connect(themeToggle, &QCheckBox::toggled, this, &AdminPage::themeToggled);
    connect(logoutBtn, &QPushButton::clicked, this, &AdminPage::logoutRequested);

    orderStatusFilterCombo = new QComboBox;
    orderStatusFilterCombo->addItem("All");
    orderStatusFilterCombo->addItem("Pending");
    orderStatusFilterCombo->addItem("Confirmed");
    orderStatusFilterCombo->addItem("Cancelled");
    connect(orderStatusFilterCombo, &QComboBox::currentTextChanged, this, [this]()
            { emit viewOrdersRequested(); });

    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(nameLabel);
    inputLayout->addWidget(productNameEdit);
    inputLayout->addWidget(descLabel);
    inputLayout->addWidget(productDescEdit);
    inputLayout->addWidget(priceLabel);
    inputLayout->addWidget(productPriceEdit);
    inputLayout->addWidget(qtyLabel);
    inputLayout->addWidget(productQtyEdit);

    adminLayout->addWidget(adminLabel);
    adminLayout->addWidget(adminProfileLabel);
    adminLayout->addLayout(inputLayout);
    QHBoxLayout *productActionLayout = new QHBoxLayout;
    productActionLayout->addWidget(addProductBtn);
    productActionLayout->addWidget(removeProductBtn);
    adminLayout->addLayout(productActionLayout);

    QHBoxLayout *orderActionLayout = new QHBoxLayout;
    orderActionLayout->addWidget(viewOrdersBtn);
    orderActionLayout->addWidget(clearOrdersBtn);
    orderActionLayout->addWidget(cancelAllOrdersBtn);
    orderActionLayout->addWidget(completeAllOrdersBtn);
    orderActionLayout->addWidget(confirmOrderBtn);
    orderActionLayout->addWidget(completeOrderBtn);
    orderActionLayout->addWidget(cancelOrderBtn);
    adminLayout->addLayout(orderActionLayout);

    adminLayout->addWidget(new QLabel("Filter Orders:"));
    adminLayout->addWidget(orderStatusFilterCombo);

    QHBoxLayout *userActionLayout = new QHBoxLayout;
    userActionLayout->addWidget(deleteUserBtn);
    adminLayout->addLayout(userActionLayout);

    ordersListWidget = new QListWidget;
    usersListWidget = new QListWidget;
    weeklySummaryLabel = new QLabel("Orders this week: N/A");
    yearlySummaryLabel = new QLabel("Orders this year: N/A");
    popularProductsList = new QListWidget;

    tabWidget = new QTabWidget;

    QWidget *ordersTab = new QWidget;
    QVBoxLayout *ordersTabLayout = new QVBoxLayout(ordersTab);
    ordersTabLayout->addWidget(new QLabel("Orders:"));
    ordersTabLayout->addWidget(ordersListWidget);
    ordersTab->setLayout(ordersTabLayout);
    tabWidget->addTab(ordersTab, "Orders");

    QWidget *usersTab = new QWidget;
    QVBoxLayout *usersTabLayout = new QVBoxLayout(usersTab);
    usersTabLayout->addWidget(new QLabel("Users:"));
    usersTabLayout->addWidget(usersListWidget);
    usersTab->setLayout(usersTabLayout);
    tabWidget->addTab(usersTab, "Users");

    QWidget *productsTab = new QWidget;
    QVBoxLayout *productsTabLayout = new QVBoxLayout(productsTab);
    productsTabLayout->addWidget(new QLabel("Products:"));
    productsTabLayout->addWidget(productListWidget);
    productsTab->setLayout(productsTabLayout);
    tabWidget->addTab(productsTab, "Products");

    QWidget *analyticsTab = new QWidget;
    QVBoxLayout *analyticsTabLayout = new QVBoxLayout(analyticsTab);
    analyticsTabLayout->addWidget(new QLabel("Admin Order Analysis:"));
    analyticsTabLayout->addWidget(weeklySummaryLabel);
    analyticsTabLayout->addWidget(yearlySummaryLabel);
    analyticsTabLayout->addWidget(new QLabel("Popular Products:"));
    analyticsTabLayout->addWidget(popularProductsList);
    analyticsTab->setLayout(analyticsTabLayout);
    tabWidget->addTab(analyticsTab, "Analytics");

    adminLayout->addWidget(tabWidget);
    QHBoxLayout *bottomAdminLayout = new QHBoxLayout;
    bottomAdminLayout->addWidget(changePasswordBtn);
    bottomAdminLayout->addWidget(themeToggle);
    bottomAdminLayout->addWidget(logoutBtn);
    adminLayout->addLayout(bottomAdminLayout);
    adminLayout->addStretch();

    setLayout(adminLayout);
}

AdminPage::~AdminPage()
{
}

void AdminPage::setProfile(const QString &username)
{
    adminProfileLabel->setText("Welcome, " + username + " (Admin)");
}

void AdminPage::loadProducts()
{
    productListWidget->clear();
    int count = 0;
    const Product *products = Product::getProducts(count);
    for (int i = 0; i < count; i++)
    {
        QString item = QString::number(products[i].getId()) + ". " + QString::fromStdString(products[i].getName()) + " - $" + QString::number(products[i].getPrice()) + " (qty: " + QString::number(products[i].getQuantity()) + ")\n" + QString::fromStdString(products[i].getDescription());
        productListWidget->addItem(item);
    }
}


void AdminPage::loadOrders(const QString &filter)
{
    // This would need the order loading logic but for now signal to UserWindow
    emit viewOrdersRequested();
}



void AdminPage::loadUsers()
{
    usersListWidget->clear();
    auto users = User::getAllUsers();
    for (const auto &u : users)
    {
        QString role = (u.second == 0) ? "Customer" : "Admin";
        usersListWidget->addItem(u.first + " (" + role + ")");
    }
}

// ============================================================================
// PURPOSE: Extract selected product name from the product list
// RETURNS: Product name if selected, empty string if none selected
// DESCRIPTION: Parses the selected product list item to extract the name.
//              The format in the list is "ID. Name - $Price (qty: X)\nDesc"
//              This extracts just the "Name" portion for product operations.
// ============================================================================
QString AdminPage::getSelectedProductName() const
{
    if (productListWidget->currentRow() >= 0)
    {
        QListWidgetItem *item = productListWidget->currentItem();
        if (item)
        {
            QString text = item->text();
            int dotIdx = text.indexOf('.');
            QString nameStart = text.mid(dotIdx + 2);
            int dashIdx = nameStart.indexOf(" - $");
            return nameStart.left(dashIdx);
        }
    }
    return QString();
}

// ============================================================================
// PURPOSE: Get the currently selected order status filter
// RETURNS: Selected filter value ("All", "Pending", "Confirmed", "Cancelled")
// DESCRIPTION: Returns the current text from the order status filter dropdown.
//              Used to determine which orders to display in the Orders tab.
// ============================================================================
QString AdminPage::getSelectedOrderFilter() const
{
    return orderStatusFilterCombo->currentText();
}

// ============================================================================
// PURPOSE: Get the index of the currently selected order
// RETURNS: Order index if selected, or -1 if no order is selected
// DESCRIPTION: Retrieves the order index stored in the Qt::UserRole data
//              of the selected list item. This index is used to access
//              order details for update operations.
// ============================================================================
int AdminPage::getSelectedOrderIndex() const
{
    if (ordersListWidget->currentRow() >= 0)
    {
        QListWidgetItem *item = ordersListWidget->currentItem();
        if (item)
        {
            return item->data(Qt::UserRole).toInt();
        }
    }
    return -1;
}


// PURPOSE: Extract selected username from the users list
// RETURNS: Username if selected, empty string if none selected
// DESCRIPTION: Parses the selected user list item to extract the username.
//              The format in the list is "Username (Role)"
//              This extracts just the username portion for user operations.
QString AdminPage::getSelectedUserName() const
{
    if (usersListWidget->currentRow() >= 0)
    {
        QListWidgetItem *item = usersListWidget->currentItem();
        if (item)
        {
            QString text = item->text();
            int pos = text.indexOf(" (");
            if (pos != -1)
            {
                return text.left(pos);
            }
        }
    }
    return QString();
}

// PURPOSE: Populate the orders list with admin's order view
// PARAMETERS: orders - Vector of pairs (order display text, order index)
// DESCRIPTION: Clears the orders list and adds each order with its display
//              text. Stores the order index in Qt::UserRole for retrieval.
//              Display format: "Order #ID: Products | Qty | Total | Status | City..."
void AdminPage::setOrderItems(const QVector<QPair<QString, int>> &orders)
{
    ordersListWidget->clear();
    for (const auto &order : orders)
    {
        QListWidgetItem *item = new QListWidgetItem(order.first);
        item->setData(Qt::UserRole, order.second);
        ordersListWidget->addItem(item);
    }
}

// PURPOSE: Display the top 5% most frequently ordered products
// PARAMETERS: products - List of popular product names with order counts
// DESCRIPTION: Populates the popular products display in the Analytics tab.
//              Each line shows "ProductName (X orders)" format.
void AdminPage::setPopularProducts(const QStringList &products)
{
    popularProductsList->clear();
    for (const QString &product : products)
        popularProductsList->addItem(product);
}

// PURPOSE: Update analytics display with weekly and yearly summaries
// PARAMETERS: weekSummary - Text showing current week stats
//             yearSummary - Text showing current year stats
// DESCRIPTION: Updates the analytics labels in the Analytics tab.
//              Example: "Orders this week: 5, revenue: $150.50"
void AdminPage::setOrderAnalysis(const QString &weekSummary, const QString &yearSummary)
{
    weeklySummaryLabel->setText(weekSummary);
    yearlySummaryLabel->setText(yearSummary);
}

// PURPOSE: Populate the users list with registered users
// PARAMETERS: users - List of user information strings
// DESCRIPTION: Clears the users list and adds each user entry.
//              Format typically: "Username (Customer/Admin)"
void AdminPage::setUserItems(const QStringList &users)
{
    usersListWidget->clear();
    for (const QString &user : users)
    {
        usersListWidget->addItem(user);
    }
}

void AdminPage::setTheme(bool isDark)
{
    themeToggle->setChecked(isDark);
}