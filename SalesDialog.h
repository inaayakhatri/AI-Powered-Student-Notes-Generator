#ifndef SALESDIALOG_H
#define SALESDIALOG_H

#include <QDialog>

class QLabel;
class QPushButton;

class SalesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SalesDialog(QWidget *parent = nullptr);
    ~SalesDialog();

private:
    void loadSalesData();
    void setupUI();

    QLabel *totalRevenueLabel;
    QLabel *totalOrdersLabel;
    QLabel *pendingOrdersLabel;
    QLabel *completedOrdersLabel;
    QLabel *averageOrderLabel;
    QPushButton *refreshBtn;
    QPushButton *closeBtn;
};

#endif
