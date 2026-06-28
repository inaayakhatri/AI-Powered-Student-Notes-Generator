#include "RegisterPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>

RegisterPage::RegisterPage(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    titleLabel = new QLabel("Register");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

    usernameLabel = new QLabel("Username:");
    usernameEdit = new QLineEdit;

    passwordLabel = new QLabel("Password:");
    passwordEdit = new QLineEdit;
    passwordEdit->setEchoMode(QLineEdit::Password);

    showPassword = new QCheckBox("Show Password");
    connect(showPassword, &QCheckBox::toggled, this, [this](bool checked)
            {
        passwordEdit->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
        adminCodeEdit->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password); });

    roleLabel = new QLabel("Select Role:");
    roleCombo = new QComboBox;
    roleCombo->addItem("Customer", 0);
    roleCombo->addItem("Admin", 1);

    adminCodeLabel = new QLabel("Admin Passcode:");
    adminCodeEdit = new QLineEdit;
    adminCodeEdit->setEchoMode(QLineEdit::Password);
    adminCodeEdit->setVisible(false);
    adminCodeLabel->setVisible(false);
    connect(roleCombo, &QComboBox::currentTextChanged, this, [this](const QString &text)
            {
        adminCodeEdit->setVisible(text == "Admin");
        adminCodeLabel->setVisible(text == "Admin"); });

    registerBtn = new QPushButton("Register");
    backBtn = new QPushButton("Back");

    themeToggle = new QCheckBox("Dark Theme");
    connect(themeToggle, &QCheckBox::toggled, this, &RegisterPage::themeToggled);

    connect(registerBtn, &QPushButton::clicked, this, [this]()
            { emit registerSubmitted(usernameEdit->text(), passwordEdit->text(), roleCombo->currentData().toInt(), adminCodeEdit->text()); });
    connect(backBtn, &QPushButton::clicked, this, &RegisterPage::backRequested);

    layout->addWidget(titleLabel);
    layout->addWidget(usernameLabel);
    layout->addWidget(usernameEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordEdit);
    layout->addWidget(showPassword);
    layout->addWidget(roleLabel);
    layout->addWidget(roleCombo);
    layout->addWidget(adminCodeLabel);
    layout->addWidget(adminCodeEdit);
    layout->addWidget(registerBtn);
    layout->addWidget(themeToggle);
    layout->addWidget(backBtn);

    setLayout(layout);
}

RegisterPage::~RegisterPage()
{
}

void RegisterPage::setTheme(bool isDark)
{
    themeToggle->setChecked(isDark);
}