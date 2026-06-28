#include <iostream>
using namespace std;
#include "UserWindow.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QInputDialog>
#include <QComboBox>
#include "User.h"
#include "Admin.h"
#include "Customer.h"
#include "Product.h"
#include <QTabWidget>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QListWidget>
#include <QSpinBox>
#include <QCheckBox>
#include <QListWidgetItem>
#include <QTextEdit>
#include <QRegularExpressionValidator>
#include <QList>
#include <QStringList>
#include <fstream>
#include <QDate>

static const string ADMIN_REGISTRATION_CODE = "ADMIN2026";
int UserWindow::orderIdCounter = 1; // to count order ids

UserWindow::~UserWindow() // destructor saves all the data
{
    saveOrderCounter();
    Product::saveProducts();
    User::saveUsers();
}

void UserWindow::loadOrderCounter() // loads order id count from the file
{
    ifstream file("order_counter.txt");
    if (file.is_open())
    {
        file >> orderIdCounter;
        file.close();
    }
    else
    {
        orderIdCounter = 1;
    }
}

void UserWindow::saveOrderCounter() // writes updated order id to the file
{
    ofstream file("order_counter.txt");
    if (file.is_open())
    {
        file << orderIdCounter;
        file.close();
    }
}

static QList<Order> loadOrdersFromFile() // loads all the orders from the file
{
    OrderManager manager("orders.csv");
    return manager.loadOrders();
}

static bool saveOrdersToFile(const QList<Order> &orders) // saves the orders to the file
{
    OrderManager manager("orders.csv");
    return manager.saveOrders(orders);
}

static double getDeliveryFee(const string &city)
{
    if (city == "Karachi")
        return 15.0;
    if (city == "Lahore")
        return 10.0;
    if (city == "Islamabad")
        return 8.0;
    if (city == "Peshawar")
        return 12.0;
    if (city == "Multan")
        return 11.0;
    if (city == "Faisalabad")
        return 9.0;
    if (city == "Quetta")
        return 13.0;
    return 5.0;
}

UserWindow::UserWindow(QWidget *parent) : QMainWindow(parent), currentUser(nullptr)
{
    bool initialThemeDark = false;
    ifstream themeFile("theme.txt");
    if (themeFile.is_open())
    {
        string theme;
        getline(themeFile, theme);
        if (theme == "dark")
        {
            initialThemeDark = true;
        }
        themeFile.close();
    }

    setWindowTitle("ShopBuddy");

    setMinimumSize(800, 600);

    loadOrderCounter();

    // Create central widget and layout
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    stack = new QStackedWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(stack);
    centralWidget->setLayout(mainLayout);

    // Create all page widgets
    mainPage = new MainPage;
    loginPage = new LoginPage;
    registerPage = new RegisterPage;
    customerPage = new CustomerPage;
    adminPage = new AdminPage;

    // Add pages to the stacked widget for navigation
    stack->addWidget(mainPage);
    stack->addWidget(loginPage);
    stack->addWidget(registerPage);
    stack->addWidget(customerPage);
    stack->addWidget(adminPage);

    // Set initial page
    stack->setCurrentWidget(mainPage);

    // Connect all signal-slot relationships for UI interactions
    connect(mainPage, &MainPage::loginRequested, this, [this]()
            { 
                loginPage->clearInputs();
                stack->setCurrentWidget(loginPage); });
    connect(mainPage, &MainPage::registerRequested, this, [this]()
            { stack->setCurrentWidget(registerPage); });
    connect(mainPage, &MainPage::themeToggled, this, &UserWindow::onToggleTheme);

    connect(loginPage, &LoginPage::loginSubmitted, this, &UserWindow::onLoginSubmitted);
    connect(loginPage, &LoginPage::backRequested, this, &UserWindow::onBackToMain);
    connect(loginPage, &LoginPage::themeToggled, this, &UserWindow::onToggleTheme);

    connect(registerPage, &RegisterPage::registerSubmitted, this, &UserWindow::onRegisterSubmitted);
    connect(registerPage, &RegisterPage::backRequested, this, &UserWindow::onBackToMain);
    connect(registerPage, &RegisterPage::themeToggled, this, &UserWindow::onToggleTheme);

    connect(customerPage, &CustomerPage::addToCartRequested, this, &UserWindow::onAddToCartRequested);
    connect(customerPage, &CustomerPage::removeFromCartRequested, this, &UserWindow::onRemoveFromCartClicked);
    connect(customerPage, &CustomerPage::cancelAllOrdersRequested, this, &UserWindow::onCancelAllOrdersClicked);
    connect(customerPage, &CustomerPage::completeAllOrdersRequested, this, &UserWindow::onCompleteAllOrdersClicked);
    connect(customerPage, &CustomerPage::buyRequested, this, &UserWindow::onBuyClicked);
    connect(customerPage, &CustomerPage::trackOrdersRequested, this, &UserWindow::onTrackOrdersClicked);
    connect(customerPage, &CustomerPage::cancelOrderRequested, this, &UserWindow::onCancelCustomerOrderClicked);
    connect(customerPage, &CustomerPage::changePasswordRequested, this, &UserWindow::onChangePasswordClicked);
    connect(customerPage, &CustomerPage::logoutRequested, this, &UserWindow::onLogout);
    connect(customerPage, &CustomerPage::themeToggled, this, &UserWindow::onToggleTheme);
    connect(customerPage, &CustomerPage::orderDetailsRequested, this, &UserWindow::onCustomerOrderDetailsClicked);

    connect(adminPage, &AdminPage::addProductRequested, this, &UserWindow::onAddProductRequested);
    connect(adminPage, &AdminPage::removeProductRequested, this, &UserWindow::onRemoveProductClicked);
    connect(adminPage, &AdminPage::viewOrdersRequested, this, &UserWindow::onViewOrdersClicked);
    connect(adminPage, &AdminPage::clearOrdersRequested, this, &UserWindow::onClearOrdersClicked);
    connect(adminPage, &AdminPage::cancelAllOrdersRequested, this, &UserWindow::onCancelAllOrdersClicked);
    connect(adminPage, &AdminPage::completeAllOrdersRequested, this, &UserWindow::onCompleteAllOrdersClicked);
    connect(adminPage, &AdminPage::confirmOrderRequested, this, &UserWindow::onConfirmOrderClicked);
    connect(adminPage, &AdminPage::completeOrderRequested, this, &UserWindow::onCompleteOrderClicked);
    connect(adminPage, &AdminPage::cancelOrderRequested, this, &UserWindow::onCancelOrderClicked);
    connect(adminPage, &AdminPage::deleteUserRequested, this, &UserWindow::onDeleteUserClicked);
    connect(adminPage, &AdminPage::changePasswordRequested, this, &UserWindow::onChangePasswordClicked);
    connect(adminPage, &AdminPage::logoutRequested, this, &UserWindow::onLogout);
    connect(adminPage, &AdminPage::themeToggled, this, &UserWindow::onToggleTheme);

    // ioad stored data from previous use
    Product::loadProducts();
    User::loadUsers();

    // check whcih user was logged in
    ifstream currentUserFile("current_user.txt");
    if (currentUserFile.is_open())
    {
        string username;
        getline(currentUserFile, username);
        currentUserFile.close();
        User *user = User::findUser(username);
        if (user)
        {
            currentUser = user;
            OrderManager manager("orders.csv");
            if (user->getRole() == 0)
            {
                // set up customer page
                customerPage->setProfile(QString::fromStdString(user->getUsername()));
                customerPage->loadCart(QString::fromStdString(username));
                customerPage->loadProducts();
                customerPage->setPopularProducts(manager.popularProducts(manager.loadOrders()));
                stack->setCurrentWidget(customerPage);
            }
            else
            {
                // set up admin page for logged  in admin
                adminPage->setProfile(QString::fromStdString(user->getUsername()));
                adminPage->loadProducts();
                adminPage->loadUsers();
                QList<Order> orderList = manager.loadOrders();
                auto popularProducts = manager.popularProducts(orderList);
                auto analysis = manager.analyticsThisWeekAndYear(orderList);
                adminPage->setPopularProducts(popularProducts);
                adminPage->setOrderAnalysis(analysis.first, analysis.second);
                adminPage->loadOrders();
                stack->setCurrentWidget(adminPage);
            }
        }
    }

    onToggleTheme(initialThemeDark);
}

void UserWindow::onLoginSubmitted(const QString &username, const QString &password, const QString &role)
{
    string uname = username.toStdString(); // convert qstring to string
    string pass = password.toStdString();
    int selectedRole = (role == "Admin") ? 1 : 0;

    User *user = User::authenticate(uname, pass);
    if (user && user->getRole() == selectedRole)
    {
        currentUser = user;
        ofstream currentUserFile("current_user.txt");
        if (currentUserFile.is_open())
        {
            currentUserFile << uname;
            currentUserFile.close();
        }
        int userRole = user->getRole();
        OrderManager manager("orders.csv");

        // setting up
        if (userRole == 0)
        {
            customerPage->setProfile(username);
            customerPage->loadCart(username);
            customerPage->loadProducts();
            QStringList popular = manager.popularProducts(manager.loadOrders());
            for (QString &p : popular)
            {
                int idx = p.lastIndexOf(" (");
                if (idx != -1)
                    p = p.left(idx);
            }
            customerPage->setPopularProducts(popular);
            customerPage->loadOrders();
            stack->setCurrentWidget(customerPage);
        }
        else if (userRole == 1)
        {
            // Set up admin dashboard with analytics
            adminPage->setProfile(username);
            adminPage->loadProducts();
            adminPage->loadUsers();
            QList<Order> orderList = manager.loadOrders();
            auto popularProducts = manager.popularProducts(orderList);
            auto analysis = manager.analyticsThisWeekAndYear(orderList);
            adminPage->setPopularProducts(popularProducts);
            adminPage->setOrderAnalysis(analysis.first, analysis.second);
            adminPage->loadOrders();
            stack->setCurrentWidget(adminPage);
        }
        loginPage->clearInputs();
    }
    else
    {
        QMessageBox::warning(this, "Login Failed", "Invalid username, password, or role.");
    }
}

void UserWindow::onRegisterSubmitted(const QString &username, const QString &password, int role, const QString &adminCode)
{
    string uname = username.toStdString();
    string pass = password.toStdString();
    string code = adminCode.toStdString();

    if (!User::isStrongPassword(pass))
    {
        QMessageBox::warning(this, "Registration Failed", "Password is not strong enough. Use at least 8 characters with uppercase, lowercase, digit and special character.");
        return;
    }

    if (role == 1 && code != ADMIN_REGISTRATION_CODE)
    {
        QMessageBox::warning(this, "Registration Failed", "Admin registration requires a valid special passcode.");
        return;
    }

    User *newUser = nullptr;
    if (role == 1)
        newUser = new Admin(uname, pass);
    else
        newUser = new Customer(uname, pass);

    if (User::registerUser(uname, pass, newUser))
    {
        QMessageBox::information(this, "Success", "Registration successful!");
        stack->setCurrentWidget(loginPage);
    }
    else
    {
        QMessageBox::warning(this, "Registration Failed", "Username already exists or registration error.");
        delete newUser;
    }
}

void UserWindow::onChangePasswordClicked()
{
    if (!currentUser)
        return;

    bool ok;
    QString oldPass = QInputDialog::getText(this, "Change Password", "Enter current password:", QLineEdit::Password, "", &ok);
    if (!ok || oldPass.isEmpty())
        return;

    if (!currentUser->checkPassword(oldPass.toStdString()))
    {
        QMessageBox::warning(this, "Error", "Current password is incorrect.");
        return;
    }

    QString newPass = QInputDialog::getText(this, "Change Password", "Enter new password:", QLineEdit::Password, "", &ok);
    if (!ok || newPass.isEmpty())
        return;

    QString confirmPass = QInputDialog::getText(this, "Change Password", "Confirm new password:", QLineEdit::Password, "", &ok);
    if (!ok || confirmPass.isEmpty())
        return;

    if (newPass != confirmPass)
    {
        QMessageBox::warning(this, "Error", "Passwords do not match.");
        return;
    }

    string message;
    if (currentUser->changePassword(newPass.toStdString(), message))
    {
        QMessageBox::information(this, "Success", QString::fromStdString(message));
    }
    else
    {
        QMessageBox::warning(this, "Error", QString::fromStdString(message));
    }
}


void UserWindow::onToggleTheme(bool checked)
{
    ofstream themeFile("theme.txt");
    if (themeFile.is_open())
    {
        themeFile << (checked ? "dark" : "light");
        themeFile.close();
    }

    if (checked)
    { // dark theme
        qApp->setStyleSheet("QWidget { background-color: #2b2b2b; color: #ffffff; } "
                            "QPushButton { background-color: #555555; color: #ffffff; border: 1px solid #777777; } "
                            "QListWidget { background-color: #333333; color: #ffffff; } "
                            "QLineEdit { background-color: #444444; color: #ffffff; border: 1px solid #777777; } "
                            "QLabel { color: #ffffff; } "
                            "QCheckBox { color: #ffffff; } "
                            "QComboBox { background-color: #444444; color: #ffffff; border: 1px solid #777777; } "
                            "QSpinBox { background-color: #444444; color: #ffffff; border: 1px solid #777777; } "
                            "QToolBar { background-color: #2b2b2b; border: 1px solid #555555; }");
    }
    else
    { // light theme
        qApp->setStyleSheet("");
    }

    mainPage->setTheme(checked);
    loginPage->setTheme(checked);
    registerPage->setTheme(checked);
    customerPage->setTheme(checked);
    adminPage->setTheme(checked);
}

void UserWindow::onBackToMain()
{
    stack->setCurrentWidget(mainPage);
}


void UserWindow::onLogout()
{
    if (currentUser && currentUser->getRole() == 0)
    {
        customerPage->saveCart(QString::fromStdString(currentUser->getUsername()));
        customerPage->clearCart();
    }
    currentUser = nullptr;
    loginPage->clearInputs();
    remove("current_user.txt");
    stack->setCurrentWidget(mainPage);
}


void UserWindow::onAddToCartRequested(const QString &productName, int quantity)
{
    customerPage->getCart().loadFromFile("cart_" + currentUser->getUsername() + ".csv");
    QList<QString> cartItems = customerPage->getCart().getItems();

    bool found = false;
    for (int i = 0; i < cartItems.size(); ++i)
    {
        QString line = cartItems[i];
        QString existingProduct = line.section(':', 0, 0).trimmed();
        if (existingProduct == productName)
        {
            int existingQty = line.section(':', 1, 1).trimmed().toInt();
            existingQty += quantity;
            cartItems[i] = productName + ": " + QString::number(existingQty);
            found = true;
            break;
        }
    }

    // add new item if not found
    if (!found)
    {
        cartItems.append(productName + ": " + QString::number(quantity));
    }

    customerPage->getCart().setItems(cartItems);
    customerPage->saveCart(QString::fromStdString(currentUser->getUsername()));
    customerPage->updateCartView();
    QMessageBox::information(this, "Cart", "Added " + QString::number(quantity) + " x " + productName + " to your cart.");
}

void UserWindow::onRemoveFromCartClicked(const QString &itemText)
{
    if (!currentUser || currentUser->getRole() != 0)
    {
        QMessageBox::warning(this, "Cart", "Only customers can remove items from the cart.");
        return;
    }

    auto &cart = customerPage->getCart();
    cart.loadFromFile("cart_" + currentUser->getUsername() + ".csv");
    cart.removeItem(itemText.toStdString());
    customerPage->saveCart(QString::fromStdString(currentUser->getUsername()));
    customerPage->updateCartView();
    QMessageBox::information(this, "Cart", "Item removed from your cart.");
}

void UserWindow::onBuyClicked()
{
    if (!currentUser || currentUser->getRole() != 0)
    {
        QMessageBox::warning(this, "Error", "Only customers can checkout.");
        return;
    }

    auto &cart = customerPage->getCart();
    if (cart.getItems().empty())
    {
        QMessageBox::information(this, "Cart", "Your cart is empty.");
        return;
    }

    QList<QPair<QString, int>> orderItems;
    double total = 0.0;

    for (const QString &item : cart.getItems())
    {
        QString line = item;
        QString productName = line.section(':', 0, 0).trimmed();
        int qty = line.section(':', 1, 1).trimmed().toInt();
        Product *product = Product::findProduct(productName.toStdString());
        if (!product)
        {
            QMessageBox::warning(this, "Error", "A product in your cart is no longer available.");
            return;
        }
        if (qty > product->getQuantity())
        {
            QMessageBox::warning(this, "Stock Error", productName + " only has " + QString::number(product->getQuantity()) + " left.");
            return;
        }
        total += product->getPrice() * qty;
        orderItems.append(qMakePair(productName, qty));
    }

    bool ok;
    QString address = QInputDialog::getText(this, "Delivery Address", "Enter your delivery address:", QLineEdit::Normal, "", &ok);
    if (!ok || address.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Delivery address is required.");
        return;
    }
    address.replace(',', ' '); // rmove commas to avoid CSV parsing issues

    QStringList cities = {"Karachi", "Lahore", "Islamabad", "Peshawar", "Multan", "Faisalabad", "Quetta"};
    QString city = QInputDialog::getItem(this, "Delivery City", "Select your city:", cities, 0, false, &ok);
    if (!ok || city.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Delivery city is required.");
        return;
    }

    double deliveryFee = getDeliveryFee(city.toStdString());
    double finalTotal = total + deliveryFee;

    QStringList paymentOptions = {"Credit Card", "Debit Card", "Cash on Delivery", "UPI"};
    QString paymentMethod = QInputDialog::getItem(this, "Payment Method", "Choose a payment option:", paymentOptions, 0, false, &ok);
    if (!ok || paymentMethod.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please select a payment method.");
        return;
    }


    if (paymentMethod == "Credit Card" || paymentMethod == "Debit Card")
    {
        QRegularExpression accountRegExp("\\d{16}");
        QRegularExpressionValidator accountValidator(accountRegExp, this);
        bool ok2;
        QString accountNumber = QInputDialog::getText(this, "Account Number", "Enter 16-digit account number:", QLineEdit::Normal, "", &ok2);
        if (!ok2 || accountNumber.isEmpty() || !accountRegExp.match(accountNumber).hasMatch())
        {
            QMessageBox::warning(this, "Error", "Valid 16-digit account number is required.");
            return;
        }
        QRegularExpression pinRegExp("\\d{4}");
        QRegularExpressionValidator pinValidator(pinRegExp, this);
        QString pin = QInputDialog::getText(this, "PIN Code", "Enter 4-digit PIN:", QLineEdit::Password, "", &ok2);
        if (!ok2 || pin.isEmpty() || !pinRegExp.match(pin).hasMatch())
        {
            QMessageBox::warning(this, "Error", "Valid 4-digit PIN is required.");
            return;
        }
    }

   
    for (const auto &entry : orderItems)
    {
        Product *product = Product::findProduct(entry.first.toStdString());
        if (product)
            product->setQuantity(product->getQuantity() - entry.second);
    }
    Product::saveProducts();

    QList<Order> newOrders;
    int orderId = orderIdCounter++;
    QDate orderDate = QDate::currentDate();
    for (const auto &entry : orderItems)
    {
        Product *product = Product::findProduct(entry.first.toStdString());
        Order order;
        order.orderId = orderId; // Same orderId for all items in this purchase
        order.username = currentUser->getUsername();
        order.product = entry.first.toStdString();
        order.quantity = entry.second;
        order.total = product ? product->getPrice() * entry.second : 0.0;
        order.status = "Pending"; // initial status until admin confirms
        order.address = address.toStdString();
        order.city = city.toStdString();
        order.deliveryFee = deliveryFee; // shared delivery fee for all items
        order.date = orderDate;
        order.paymentMethod = paymentMethod.toStdString();
        newOrders.append(order);
    }

    OrderManager manager("orders.csv");
    if (!manager.appendOrders(newOrders))
    {
        QMessageBox::warning(this, "Error", "Could not save order.");
        return;
    }

    saveOrderCounter();

    customerPage->clearCart();
    customerPage->saveCart(QString::fromStdString(currentUser->getUsername()));

    QDialog *billDialog = new QDialog(this);
    billDialog->setWindowTitle("Order Bill");
    QVBoxLayout *layout = new QVBoxLayout(billDialog);
    QTextEdit *textEdit = new QTextEdit();
    textEdit->setReadOnly(true);
    QString billText = "Order ID: " + QString::number(orderId) + "\n\n";
    for (const auto &entry : orderItems)
    {
        Product *p = Product::findProduct(entry.first.toStdString());
        if (p)
        {
            billText += "Product ID: " + QString::number(p->getId()) + "\n";
            billText += "Product: " + entry.first + "\n";
            billText += "Quantity: " + QString::number(entry.second) + "\n";
            billText += "Price: $" + QString::number(p->getPrice()) + "\n";
            billText += "Total: $" + QString::number(p->getPrice() * entry.second) + "\n\n";
        }
    }
    billText += "Delivery Address: " + address + "\n";
    billText += "Delivery City: " + city + "\n";
    billText += "Delivery Fee: $" + QString::number(deliveryFee) + "\n";
    billText += "Payment Method: " + paymentMethod + "\n";
    billText += "Order Date: " + orderDate.toString(Qt::ISODate) + "\n";
    billText += "Grand Total: $" + QString::number(finalTotal);
    textEdit->setText(billText);
    layout->addWidget(textEdit);
    QPushButton *okButton = new QPushButton("OK");
    connect(okButton, &QPushButton::clicked, billDialog, &QDialog::accept);
    layout->addWidget(okButton);
    billDialog->exec();

    customerPage->loadOrders();
}

void UserWindow::onAddProductRequested(const QString &name, const QString &desc, const QString &price, const QString &qty)
{
    string n = name.toStdString();
    string d = desc.toStdString();
    string p = price.toStdString();
    string q = qty.toStdString();

    if (n.empty() || p.empty() || q.empty())
    {
        QMessageBox::warning(this, "Error", "Please fill all fields.");
        return;
    }

    try
    {
        double pr = stod(p);
        int qt = stoi(q);
        string message;
        if (Product::addProduct(n, d, pr, qt, message))
        {
            Product::saveProducts();
            QMessageBox::information(this, "Success", "Product added successfully!");
            adminPage->loadProducts();
        }
        else
        {
            QMessageBox::warning(this, "Error", QString::fromStdString(message));
        }
    }
    catch (...)
    {
        QMessageBox::warning(this, "Error", "Invalid input format.");
    }
}

void UserWindow::onRemoveProductClicked(const QString &productName)
{
    string message;
    if (Product::removeProduct(productName.toStdString(), message))
    {
        Product::saveProducts();
        QMessageBox::information(this, "Success", "Product removed!");
        adminPage->loadProducts();
    }
    else
    {
        QMessageBox::warning(this, "Error", QString::fromStdString(message));
    }
}

void UserWindow::onViewProductsClicked()
{
    adminPage->loadProducts();
}

void UserWindow::onViewOrdersClicked()
{
    QVector<QPair<QString, int>> orders;
    OrderManager manager("orders.csv");
    QList<Order> orderList = manager.loadOrders();

    auto popularProducts = manager.popularProducts(orderList);
    auto analysis = manager.analyticsThisWeekAndYear(orderList);
    adminPage->setPopularProducts(popularProducts);
    adminPage->setOrderAnalysis(analysis.first, analysis.second);


    sort(orderList.begin(), orderList.end(), [](const Order &a, const Order &b)
              { return QString::fromStdString(a.city).toLower() < QString::fromStdString(b.city).toLower(); });

    QMap<int, QList<Order>> groupedOrders;
    for (const Order &order : orderList)
    {
        groupedOrders[order.orderId].append(order);
    }

    QString filter = adminPage->getSelectedOrderFilter();
    for (auto it = groupedOrders.constBegin(); it != groupedOrders.constEnd(); ++it)
    {
        int orderId = it.key();
        const QList<Order> &group = it.value();
        if (group.isEmpty())
            continue;
        const Order &first = group.first();
        if (filter != "All" && QString::fromStdString(first.status) != filter)
            continue;

        QString productsStr;
        int totalQty = 0;
        double totalPrice = 0.0;
        for (const Order &o : group)
        {
            if (!productsStr.isEmpty())
                productsStr += ", ";
            productsStr += QString::fromStdString(o.product) + " x" + QString::number(o.quantity);
            totalQty += o.quantity;
            totalPrice += o.total;
        }

        QString orderText = "Order #" + QString::number(orderId) + ": " + QString::fromStdString(first.username) + " | Products: " + productsStr + " | Total Qty: " + QString::number(totalQty) + " | Total: $" + QString::number(totalPrice, 'f', 2) + " | Status: " + QString::fromStdString(first.status) + " | City: " + QString::fromStdString(first.city) + " | Delivery: $" + QString::number(first.deliveryFee, 'f', 2) + " | Date: " + first.date.toString(Qt::ISODate) + " | Payment: " + QString::fromStdString(first.paymentMethod) + " | Address: " + QString::fromStdString(first.address);
        orders.append(qMakePair(orderText, orderId));
    }
    adminPage->setOrderItems(orders);
    if (orders.isEmpty())
        QMessageBox::information(this, "Orders", "No valid orders found.");
}

void UserWindow::onTrackOrdersClicked()
{
    QVector<QPair<QString, int>> orders;
    if (!currentUser || currentUser->getRole() != 0)
        return;

    OrderManager manager("orders.csv");
    QList<Order> orderList = manager.loadOrders();

    sort(orderList.begin(), orderList.end(), [](const Order &a, const Order &b)
              { return QString::fromStdString(a.city).toLower() < QString::fromStdString(b.city).toLower(); });

    //FILTERING
    QMap<int, QList<Order>> groupedOrders;
    for (const Order &order : orderList)
    {
        if (order.username == currentUser->getUsername())
        {
            groupedOrders[order.orderId].append(order);
        }
    }

    //STATUS FILTER
    QString filter = customerPage->getSelectedOrderFilter();
    for (auto it = groupedOrders.constBegin(); it != groupedOrders.constEnd(); ++it)
    {
        int orderId = it.key();
        const QList<Order> &group = it.value();
        if (group.isEmpty())
            continue;
        const Order &first = group.first();
        if (filter != "All" && QString::fromStdString(first.status) != filter)
            continue;

        //AGGREGATION
        QString productsStr;
        int totalQty = 0;
        double totalPrice = 0.0;
        for (const Order &o : group)
        {
            if (!productsStr.isEmpty())
                productsStr += ", ";
            productsStr += QString::fromStdString(o.product) + " x" + QString::number(o.quantity);
            totalQty += o.quantity;
            totalPrice += o.total;
        }

        //display
        QString orderText = "Order #" + QString::number(orderId) + ": Products: " + productsStr + " | Total Qty: " + QString::number(totalQty) + " | Total: $" + QString::number(totalPrice, 'f', 2) + " | Status: " + QString::fromStdString(first.status) + " | City: " + QString::fromStdString(first.city) + " | Delivery: $" + QString::number(first.deliveryFee, 'f', 2) + " | Date: " + first.date.toString(Qt::ISODate) + " | Payment: " + QString::fromStdString(first.paymentMethod) + " | Address: " + QString::fromStdString(first.address);
        orders.append(qMakePair(orderText, orderId));
    }
    customerPage->setOrderItems(orders);
    if (orders.isEmpty())
        QMessageBox::information(this, "Orders", "You have no orders yet.");
}


void UserWindow::onCustomerOrderDetailsClicked(QListWidgetItem *item)
{
    if (!item)
        return;

    QString details = item->text();
    QMessageBox::information(this, "Order Details", details);
}


void UserWindow::onCancelCustomerOrderClicked()
{
    if (!currentUser || currentUser->getRole() != 0)
    {
        QMessageBox::warning(this, "Cancel Order", "Only customers can cancel orders.");
        return;
    }

    int index = customerPage->getSelectedOrderIndex();
    if (index == -1)
    {
        QMessageBox::warning(this, "Cancel Order", "Please select an order to cancel.");
        return;
    }

    QList<Order> orders = loadOrdersFromFile();
    if (index < 0 || index >= orders.size())
        return;

    Order &order = orders[index];
    if (order.username != currentUser->getUsername())
    {
        QMessageBox::warning(this, "Cancel Order", "You can only cancel your own orders.");
        return;
    }
    if (order.status != "Pending")
    {
        QMessageBox::warning(this, "Cancel Order", "Only pending orders can be canceled.");
        return;
    }

    if (QMessageBox::question(this, "Cancel Order", "Are you sure you want to cancel this pending order?") != QMessageBox::Yes)
        return;

    Product *product = Product::findProduct(order.product);
    if (product)
    {
        product->setQuantity(product->getQuantity() + order.quantity);
        Product::saveProducts();
    }

    order.status = "Cancelled";
    if (saveOrdersToFile(orders))
    {
        QMessageBox::information(this, "Cancel Order", "Order canceled successfully.");
        customerPage->loadOrders();
    }
    else
    {
        QMessageBox::warning(this, "Cancel Order", "Failed to save order changes.");
    }
}

void UserWindow::onConfirmOrderClicked()
{
    int index = adminPage->getSelectedOrderIndex();
    if (index == -1)
    {
        QMessageBox::warning(this, "Confirm Order", "Please select an order to confirm.");
        return;
    }
    QList<Order> orders = loadOrdersFromFile();
    if (index < 0 || index >= orders.size())
        return;
    if (orders[index].status != "Pending")
    {
        QMessageBox::warning(this, "Confirm Order", "Only pending orders can be confirmed.");
        return;
    }
    orders[index].status = "Confirmed";
    if (saveOrdersToFile(orders))
    {
        QMessageBox::information(this, "Confirm Order", "Order confirmed.");
        onViewOrdersClicked();
    }
}


void UserWindow::onCompleteOrderClicked()
{
    int index = adminPage->getSelectedOrderIndex();
    if (index == -1)
    {
        QMessageBox::warning(this, "Complete Order", "Please select an order to complete.");
        return;
    }
    QList<Order> orders = loadOrdersFromFile();
    if (index < 0 || index >= orders.size())
        return;
    if (orders[index].status != "Confirmed")
    {
        QMessageBox::warning(this, "Complete Order", "Only confirmed orders can be completed.");
        return;
    }
    orders[index].status = "Completed";
    if (saveOrdersToFile(orders))
    {
        QMessageBox::information(this, "Complete Order", "Order marked as completed.");
        onViewOrdersClicked();
    }
}

void UserWindow::onCancelOrderClicked() //admin cancelling orders
{
    int index = adminPage->getSelectedOrderIndex();
    if (index == -1)
    {
        QMessageBox::warning(this, "Cancel Order", "Please select an order to cancel.");
        return;
    }
    QList<Order> orders = loadOrdersFromFile();
    if (index < 0 || index >= orders.size())
        return;
    if (orders[index].status != "Pending")
    {
        QMessageBox::warning(this, "Cancel Order", "Only pending orders can be canceled.");
        return;
    }
    Product *product = Product::findProduct(orders[index].product);
    if (product)
    {
        product->setQuantity(product->getQuantity() + orders[index].quantity);
        Product::saveProducts();
    }
    orders[index].status = "Cancelled";
    if (saveOrdersToFile(orders))
    {
        QMessageBox::information(this, "Cancel Order", "Order canceled.");
        onViewOrdersClicked();
    }
}


void UserWindow::onCancelAllOrdersClicked()
{
    if (!currentUser)
    {
        QMessageBox::warning(this, "Cancel Orders", "No user is currently logged in.");
        return;
    }

    QList<Order> orders = loadOrdersFromFile();
    bool changed = false;
    for (auto &order : orders)
    {
        if (order.status == "Pending")
        {
            if (currentUser->getRole() == 1 || order.username == currentUser->getUsername())
            {
                Product *product = Product::findProduct(order.product);
                if (product)
                    product->setQuantity(product->getQuantity() + order.quantity);
                order.status = "Cancelled";
                changed = true;
            }
        }
    }
    if (!changed)
    {
        QMessageBox::information(this, "Cancel Orders", "No pending orders were available to cancel.");
        return;
    }

    Product::saveProducts();
    if (saveOrdersToFile(orders))
    {
        if (currentUser->getRole() == 1)
            onViewOrdersClicked();
        else
            customerPage->loadOrders();
        if (currentUser->getRole() == 1)
            QMessageBox::information(this, "Cancel Orders", "All pending orders have been canceled.");
        else
            QMessageBox::information(this, "Cancel Orders", "All your pending orders have been canceled.");
    }
    else
    {
        QMessageBox::warning(this, "Cancel Orders", "Failed to save order changes.");
    }
}

void UserWindow::onCompleteAllOrdersClicked() // complete all the orders
{
    if (!currentUser)
    {
        QMessageBox::warning(this, "Complete Orders", "No user is currently logged in.");
        return;
    }

    QList<Order> orders = loadOrdersFromFile();
    bool changed = false;
    for (auto &order : orders)
    {
        if (order.status == "Confirmed")
        {
            if (currentUser->getRole() == 1 || order.username == currentUser->getUsername())
            {
                order.status = "Completed";
                changed = true;
            }
        }
    }
    if (!changed)
    {
        QMessageBox::information(this, "Complete Orders", "No confirmed orders were available to complete.");
        return;
    }
    if (saveOrdersToFile(orders))
    {
        if (currentUser->getRole() == 1)
            onViewOrdersClicked();
        else
            customerPage->loadOrders();
        if (currentUser->getRole() == 1)
            QMessageBox::information(this, "Complete Orders", "All confirmed orders have been completed.");
        else
            QMessageBox::information(this, "Complete Orders", "All your confirmed orders have been completed.");
    }
    else
    {
        QMessageBox::warning(this, "Complete Orders", "Failed to save order changes.");
    }
}

/*
removes all cancelled and completed orders from the system, admin can do this.
 */
void UserWindow::onClearOrdersClicked()
{
    QList<Order> orders = loadOrdersFromFile();
    QList<Order> keptOrders;
    for (const auto &order : orders)
    {
        if (order.status == "Pending")
            keptOrders.append(order);
    }
    if (saveOrdersToFile(keptOrders))
    {
        onViewOrdersClicked();
        QMessageBox::information(this, "Clear Orders", "Cancelled and completed orders have been removed.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to clear orders.");
    }
}

void UserWindow::onViewUsersClicked() // the admin can view the users thru this function
{
    QStringList users;
    auto userList = User::getAllUsers();
    for (const auto &u : userList)
    {
        QString role = (u.second == 0) ? "Customer" : "Admin";
        users.append(u.first + " (" + role + ")");
    }
    adminPage->setUserItems(users);
    if (users.isEmpty())
        QMessageBox::information(this, "Users", "No users found.");
}

void UserWindow::onDeleteUserClicked() // deletes users
{
    QString uname = adminPage->getSelectedUserName();
    if (uname.isEmpty())
    {
        QMessageBox::warning(this, "Delete User", "Please select a user to delete.");
        return;
    }

    User *userToDelete = User::findUser(uname.toStdString());
    if (!userToDelete)
    {
        QMessageBox::warning(this, "Delete User", "User not found.");
        return;
    }

    if (userToDelete->getRole() == 1)
    {
        QMessageBox::warning(this, "Delete User", "Admins can only delete customers, not other admins.");
        return;
    }

    if (uname == QString::fromStdString(currentUser->getUsername()))
    {
        QMessageBox::warning(this, "Delete User", "Cannot delete yourself.");
        return;
    }
    if (QMessageBox::question(this, "Delete User", "Are you sure you want to delete user '" + uname + "'?") == QMessageBox::Yes)
    {
        if (User::deleteUser(uname.toStdString()))
        {
            // If customer, remove cart file
            string cartFile = "cart_" + uname.toStdString() + ".csv";
            remove(cartFile.c_str());
            adminPage->loadUsers();
            QMessageBox::information(this, "Delete User", "User deleted successfully.");
        }
        else
        {
            QMessageBox::warning(this, "Delete User", "Failed to delete user.");
        }
    }
}
