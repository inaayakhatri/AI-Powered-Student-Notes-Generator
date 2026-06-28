#include "MainPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>

MainPage::MainPage(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    titleLabel = new QLabel("Welcome to ShopBuddy!");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 28px; font-weight: bold; margin: 50px;");

    loginBtn = new QPushButton("Login");
    registerBtn = new QPushButton("Register");

    loginBtn->setFixedSize(150, 50);
    registerBtn->setFixedSize(150, 50);

    themeToggle = new QCheckBox("Dark Theme");

    connect(loginBtn, &QPushButton::clicked, this, &MainPage::loginRequested);
    connect(registerBtn, &QPushButton::clicked, this, &MainPage::registerRequested);
    connect(themeToggle, &QCheckBox::toggled, this, &MainPage::themeToggled);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(loginBtn);
    btnLayout->addWidget(registerBtn);
    btnLayout->addStretch();

    layout->addStretch();
    layout->addWidget(titleLabel);
    layout->addLayout(btnLayout);
    layout->addWidget(themeToggle);
    layout->addStretch();

    setLayout(layout);
}

MainPage::~MainPage()
{
}

void MainPage::setTheme(bool isDark)
{
    themeToggle->setChecked(isDark);
}
