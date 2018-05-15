#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->setFixedSize(350, 300);
}

SettingsDialog::~SettingsDialog(){
    delete ui;
}

void SettingsDialog::on_pushButton_play_clicked(){
    int difficulty;
    if (ui->radioButton_easy->isChecked())
        difficulty = 1;
    if (ui->radioButton_medium->isChecked())
        difficulty = 2;
    if (ui->radioButton_hard->isChecked())
        difficulty = 3;
    if (ui->radioButton_expert->isChecked())
        difficulty = 4;

    emit mazeInfo(ui->spinBox_height->value(), ui->spinBox_width->value(), difficulty);
    this->close();
}

void SettingsDialog::on_pushButton_close_clicked(){
    this->close();
}
