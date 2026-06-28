#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include <QCheckBox>

class QPushButton;
class QLineEdit;
class QLabel;
class QComboBox;

class LoginPage : public QWidget
{
    Q_OBJECT
public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

    void clearInputs();

    void setTheme(bool isDark);

signals:
    void loginSubmitted(const QString &username, const QString &password, const QString &role);
    void backRequested();
    void themeToggled(bool checked);

private:
    QLabel *titleLabel;
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    QLabel *roleLabel;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QComboBox *roleCombo;
    QCheckBox *showPassword;
    QCheckBox *themeToggle;
    QPushButton *loginBtn;
    QPushButton *backBtn;
};

#endif