#include "LoginPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>

LoginPage::LoginPage(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    titleLabel = new QLabel("Login");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

    usernameLabel = new QLabel("Username:");
    usernameEdit = new QLineEdit;

    passwordLabel = new QLabel("Password:");
    passwordEdit = new QLineEdit;
    passwordEdit->setEchoMode(QLineEdit::Password);

    showPassword = new QCheckBox("Show Password");
    connect(showPassword, &QCheckBox::toggled, this, [this](bool checked)
            { passwordEdit->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password); });

    roleLabel = new QLabel("Login as:");
    roleCombo = new QComboBox;
    roleCombo->addItem("Customer");
    roleCombo->addItem("Admin");

    themeToggle = new QCheckBox("Dark Theme");
    connect(themeToggle, &QCheckBox::toggled, this, &LoginPage::themeToggled);

    loginBtn = new QPushButton("Login");
    backBtn = new QPushButton("Back");

    connect(loginBtn, &QPushButton::clicked, this, [this]()
            { emit loginSubmitted(usernameEdit->text(), passwordEdit->text(), roleCombo->currentText()); });
    connect(backBtn, &QPushButton::clicked, this, &LoginPage::backRequested);

    layout->addWidget(titleLabel);
    layout->addWidget(usernameLabel);
    layout->addWidget(usernameEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordEdit);
    layout->addWidget(showPassword);
    layout->addWidget(roleLabel);
    layout->addWidget(roleCombo);
    layout->addWidget(themeToggle);
    layout->addWidget(loginBtn);
    layout->addWidget(backBtn);
    layout->addStretch();

    setLayout(layout);
}

LoginPage::~LoginPage()
{
}

void LoginPage::setTheme(bool isDark)
{
    themeToggle->setChecked(isDark);
}

void LoginPage::clearInputs()
{
    usernameEdit->clear();
    passwordEdit->clear();
    roleCombo->setCurrentIndex(0);
    showPassword->setChecked(false);
    passwordEdit->setEchoMode(QLineEdit::Password);
}