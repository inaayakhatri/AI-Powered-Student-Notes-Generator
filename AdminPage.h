#ifndef ADMINPAGE_H
#define ADMINPAGE_H
#include <QWidget>
#include <QCheckBox>
#include <QPair>
#include <QVector>

class QPushButton;
class QLabel;
class QLineEdit;
class QListWidget;
class QComboBox;
class QTabWidget;

class AdminPage : public QWidget
{
private:
    QLabel *adminLabel;
    QLabel *adminProfileLabel;
    QLineEdit *productNameEdit;
    QLineEdit *productDescEdit;
    QLineEdit *productPriceEdit; // taking inputs
    QLineEdit *productQtyEdit;
    QListWidget *productListWidget;
    QListWidget *ordersListWidget; // displaying products
    QListWidget *usersListWidget;
    QComboBox *orderStatusFilterCombo; // dropdown filter
    QCheckBox *themeToggle;
    QPushButton *addProductBtn;
    QPushButton *removeProductBtn;
    QPushButton *viewOrdersBtn;
    QPushButton *clearOrdersBtn;
    QPushButton *cancelAllOrdersBtn;
    QPushButton *completeAllOrdersBtn; // buttons that perform actions
    QPushButton *confirmOrderBtn;
    QPushButton *completeOrderBtn;
    QPushButton *cancelOrderBtn;
    QPushButton *deleteUserBtn;
    QPushButton *changePasswordBtn;
    QPushButton *salesSummaryBtn;
    QPushButton *logoutBtn;
    QLabel *weeklySummaryLabel;
    QLabel *yearlySummaryLabel;
    QListWidget *popularProductsList;
    QTabWidget *tabWidget; //divides the gui into different tabs
    Q_OBJECT
public:
    explicit AdminPage(QWidget *parent = nullptr);
    ~AdminPage();

    void setProfile(const QString &username);
    void loadProducts();
    void loadOrders(const QString &filter = "All");
    void loadUsers();

    QString getSelectedProductName() const;
    QString getSelectedOrderFilter() const;
    int getSelectedOrderIndex() const;
    QString getSelectedUserName() const;
    void setOrderItems(const QVector<QPair<QString, int>> &orders);
    void setUserItems(const QStringList &users);
    void setPopularProducts(const QStringList &products);
    void setOrderAnalysis(const QString &weekSummary, const QString &yearSummary);

    void setTheme(bool isDark);

signals:
    void addProductRequested(const QString &name, const QString &desc, const QString &price, const QString &qty);
    void removeProductRequested(const QString &productName);
    void viewOrdersRequested();
    void clearOrdersRequested();
    void cancelAllOrdersRequested();
    void completeAllOrdersRequested();
    void confirmOrderRequested();
    void completeOrderRequested();
    void cancelOrderRequested();
    void deleteUserRequested();
    void changePasswordRequested();
    void viewSalesSummaryRequested();
    void logoutRequested();
    void themeToggled(bool checked);

};

#endif