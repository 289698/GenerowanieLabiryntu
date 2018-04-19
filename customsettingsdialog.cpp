#include "customsettingsdialog.h"
#include "ui_customsettingsdialog.h"

CustomSettingsDialog::CustomSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomSettingsDialog)
{
    ui->setupUi(this);
}

CustomSettingsDialog::~CustomSettingsDialog()
{
    delete ui;
}
