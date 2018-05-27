#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->resize(360, 155);
    ui->groupBox_difficulty->setToolTip ("Im wyższy stopień studności, tym dłuższa będzie\n"
                                         "droga od startu do mety.");
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
    emit mainSettings(ui->spinBox_height->value(), ui->spinBox_width->value(), difficulty);
    this->close();
}
