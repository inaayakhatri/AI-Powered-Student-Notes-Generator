#ifndef CHECKOUTDIALOG_H
#define CHECKOUTDIALOG_H

#include <QDialog>
#include <QString>

class QRadioButton;
class QButtonGroup;
class QLabel;
class QPushButton;

class CheckoutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CheckoutDialog(double totalAmount, QWidget *parent = nullptr);
    ~CheckoutDialog();

    QString getPaymentMethod() const;
    double getOrderTotal() const;

private:
    double total;
    QButtonGroup *paymentGroup;
    QRadioButton *creditCardRadio;
    QRadioButton *debitCardRadio;
    QRadioButton *paypalRadio;
    QRadioButton *cashRadio;
    QLabel *totalLabel;
    QPushButton *confirmBtn;
    QPushButton *cancelBtn;

    void setupUI();
};

#endif // CHECKOUTDIALOG_H
