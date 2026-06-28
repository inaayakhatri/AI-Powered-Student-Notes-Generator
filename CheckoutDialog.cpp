#include "CheckoutDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QGroupBox>

CheckoutDialog::CheckoutDialog(double totalAmount, QWidget *parent)
    : QDialog(parent), total(totalAmount)
{
    setWindowTitle("Select Payment Method");
    setModal(true);
    setMinimumWidth(300);
    setupUI();
}

CheckoutDialog::~CheckoutDialog()
{
}

void CheckoutDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Total display
    totalLabel = new QLabel("Order Total: $" + QString::number(total, 'f', 2));
    totalLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
    mainLayout->addWidget(totalLabel);

    mainLayout->addSpacing(10);

    // Payment method group
    QGroupBox *paymentGroupBox = new QGroupBox("Payment Method");
    QVBoxLayout *paymentLayout = new QVBoxLayout(paymentGroupBox);

    paymentGroup = new QButtonGroup(this);

    creditCardRadio = new QRadioButton("Credit Card");
    debitCardRadio = new QRadioButton("Debit Card");
    paypalRadio = new QRadioButton("PayPal");
    cashRadio = new QRadioButton("Cash on Delivery");

    paymentGroup->addButton(creditCardRadio, 0);
    paymentGroup->addButton(debitCardRadio, 1);
    paymentGroup->addButton(paypalRadio, 2);
    paymentGroup->addButton(cashRadio, 3);

    paymentLayout->addWidget(creditCardRadio);
    paymentLayout->addWidget(debitCardRadio);
    paymentLayout->addWidget(paypalRadio);
    paymentLayout->addWidget(cashRadio);

    creditCardRadio->setChecked(true);

    mainLayout->addWidget(paymentGroupBox);
    mainLayout->addSpacing(10);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    confirmBtn = new QPushButton("Confirm");
    cancelBtn = new QPushButton("Cancel");
    buttonLayout->addWidget(confirmBtn);
    buttonLayout->addWidget(cancelBtn);
    mainLayout->addLayout(buttonLayout);

    connect(confirmBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

QString CheckoutDialog::getPaymentMethod() const
{
    int selectedId = paymentGroup->checkedId();
    switch (selectedId)
    {
    case 0:
        return "Credit Card";
    case 1:
        return "Debit Card";
    case 2:
        return "PayPal";
    case 3:
        return "Cash on Delivery";
    default:
        return "Credit Card";
    }
}

double CheckoutDialog::getOrderTotal() const
{
    return total;
}
