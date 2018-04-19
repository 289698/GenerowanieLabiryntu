#ifndef CUSTOMSETTINGSDIALOG_H
#define CUSTOMSETTINGSDIALOG_H

#include <QDialog>

#include <mainwindow.h>

namespace Ui {
class CustomSettingsDialog;
}

class CustomSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomSettingsDialog(QWidget *parent = 0);
    ~CustomSettingsDialog();

private slots:

private:
    Ui::CustomSettingsDialog *ui;
};

#endif // CUSTOMSETTINGSDIALOG_H
