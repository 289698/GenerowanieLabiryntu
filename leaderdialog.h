#ifndef LEADERDIALOG_H
#define LEADERDIALOG_H

#include <QDialog>

namespace Ui {
class LeaderDialog;
}

class LeaderDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LeaderDialog(QWidget *parent = 0);
    ~LeaderDialog();

    void setLabels(const QStringList &leaderInfo);

signals:
    void resetLeader();

private slots:
    void on_pushButton_close_clicked();
    void on_pushButton_reset_clicked();

private:
    Ui::LeaderDialog *ui;
};

#endif // LEADERDIALOG_H
