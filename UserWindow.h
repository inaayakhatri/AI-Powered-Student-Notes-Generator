#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "User.h"
#include "Admin.h"
#include "Customer.h"
#include "Product.h"
#include "Cart.h"
#include "MainPage.h"
#include "LoginPage.h"
#include "RegisterPage.h"
#include "CustomerPage.h"
#include "AdminPage.h"
#include "OrderManager.h"

class QPushButton;
class QLineEdit;
class QLabel;
class QCheckBox;
class QComboBox;
class QListWidget;
class QListWidgetItem;
class QSpinBox;
class QWidget;

class UserWindow : public QMainWindow
{
private:
    Q_OBJECT
    QWidget *centralWidget;
    QStackedWidget *stack;
    MainPage *mainPage;
    LoginPage *loginPage;
    RegisterPage *registerPage;
    CustomerPage *customerPage;
    AdminPage *adminPage;
    User *currentUser;
    OrderManager orderManager;
    void loadOrderCounter();
    void saveOrderCounter();
    static int orderIdCounter;

public:
    explicit UserWindow(QWidget *parent = nullptr); // initialises and creates gui
    ~UserWindow();

private slots:
    void onLoginSubmitted(const QString &username, const QString &password, const QString &role);
    void onRegisterSubmitted(const QString &username, const QString &password, int role, const QString &adminCode);
    void onChangePasswordClicked();
    void onToggleTheme(bool checked);
    void onBackToMain();
    void onLogout();
    void onAddProductRequested(const QString &name, const QString &desc, const QString &price, const QString &qty);
    void onRemoveProductClicked(const QString &productName);
    void onRemoveFromCartClicked(const QString &itemText);
    void onViewProductsClicked();
    void onViewOrdersClicked();
    void onClearOrdersClicked();
    void onConfirmOrderClicked();
    void onCompleteOrderClicked();
    void onCancelOrderClicked();
    void onCancelAllOrdersClicked();
    void onCompleteAllOrdersClicked();
    void onViewUsersClicked();
    void onDeleteUserClicked();
    void onAddToCartRequested(const QString &productName, int quantity);
    void onBuyClicked();
    void onTrackOrdersClicked();
    void onCancelCustomerOrderClicked();
    void onCustomerOrderDetailsClicked(QListWidgetItem *item);
};

#endif
