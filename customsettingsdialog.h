#ifndef CUSTOMSETTINGSDIALOG_H
#define CUSTOMSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class CustomSettingsDialog;
}

class CustomSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomSettingsDialog(QWidget *parent = 0);
    ~CustomSettingsDialog();

private:
    Ui::CustomSettingsDialog *ui;
};

#endif // CUSTOMSETTINGSDIALOG_H
