#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H
#include <QWidget>
#include <QCheckBox>

class QPushButton;
class QLineEdit;
class QLabel;
class QComboBox;

class RegisterPage : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterPage(QWidget *parent = nullptr);
    ~RegisterPage();

    void setTheme(bool isDark);

signals:
    void registerSubmitted(const QString &username, const QString &password, int role, const QString &adminCode);
    void backRequested();
    void themeToggled(bool checked);

private:
    QLabel *titleLabel;
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    QLabel *roleLabel;
    QLabel *adminCodeLabel;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QLineEdit *adminCodeEdit;
    QComboBox *roleCombo;
    QCheckBox *showPassword;
    QCheckBox *themeToggle;
    QPushButton *registerBtn;
    QPushButton *backBtn;
};

#endif