#ifndef MAINPAGE_H
#define MAINPAGE_H
#include <QWidget>
#include <QCheckBox>

class QPushButton;
class QLabel;

class MainPage : public QWidget
{
private:
    QLabel *titleLabel;
    QPushButton *loginBtn;
    QPushButton *registerBtn;
    QCheckBox *themeToggle;
    Q_OBJECT
public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();
    void setTheme(bool isDark);

signals:
    void loginRequested();
    void registerRequested();
    void themeToggled(bool checked);
};

#endif // MAINPAGE_H