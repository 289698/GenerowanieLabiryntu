#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

signals:
    void mainSettings(int,int,int,int);

private slots:
    void on_pushButton_play_clicked();
    void on_pushButton_close_clicked();
    void on_checkBox_superUser_clicked(bool checked);
    void on_checkBox_blackout_clicked(bool checked);
    void on_checkBox_time_clicked(bool checked);

private:
    Ui::SettingsDialog *ui;
    void setAllToolTips();
};

#endif // SETTINGSDIALOG_H
