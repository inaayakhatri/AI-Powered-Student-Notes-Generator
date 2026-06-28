#ifndef CUSTOMERPAGE_H
#define CUSTOMERPAGE_H

#include <QWidget>
#include <QPair>
#include <QVector>
#include <QCheckBox>
#include <QLineEdit>
#include "Cart.h"

class QPushButton;
class QLabel;
class QListWidget;
class QListWidgetItem;
class QSpinBox;
class QComboBox;
class QTabWidget;

class CustomerPage : public QWidget
{
    Q_OBJECT
public:
    explicit CustomerPage(QWidget *parent = nullptr);
    ~CustomerPage();

    void setProfile(const QString &username);
    void loadProducts();
    void loadOrders();
    void updateCartView();
    void loadCart(const QString &username);
    void saveCart(const QString &username);
    void clearCart();
    Cart &getCart();
    void applyProductFilters();

    QString getSelectedProductName() const;
    int getSelectedOrderIndex() const;
    QString getSelectedOrderFilter() const;
    void setOrderItems(const QVector<QPair<QString, int>> &orders);
    void setPopularProducts(const QStringList &products);

    void setTheme(bool isDark);

signals:
    void addToCartRequested(const QString &productName, int quantity);
    void removeFromCartRequested(const QString &itemText);
    void cancelAllOrdersRequested();
    void completeAllOrdersRequested();
    void buyRequested();
    void trackOrdersRequested();
    void cancelOrderRequested();
    void changePasswordRequested();
    void logoutRequested();
    void themeToggled(bool checked);
    void orderDetailsRequested(QListWidgetItem *item);

private:
    QLabel *profileLabel;
    QLineEdit *searchProductEdit;
    QComboBox *categoryFilterCombo;
    QListWidget *productList;
    QListWidget *popularProductsList;
    QListWidget *cartList;
    QListWidget *ordersList;
    QSpinBox *quantitySpinBox;
    QComboBox *orderStatusFilterCombo;
    QPushButton *removeCartBtn;
    QPushButton *cancelAllOrdersBtn;
    QPushButton *completeAllOrdersBtn;
    QCheckBox *themeToggle;
    QPushButton *addBtn;
    QPushButton *buyBtn;
    QPushButton *trackOrdersBtn;
    QPushButton *cancelOrderBtn;
    QPushButton *refreshOrdersBtn;
    QPushButton *changePasswordBtn;
    QPushButton *logoutBtn;
    QTabWidget *tabWidget;
    Cart cart;
};

#endif // CUSTOMERPAGE_H