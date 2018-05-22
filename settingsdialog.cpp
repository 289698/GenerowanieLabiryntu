#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->resize(360, 255);
    setAllToolTips();
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
    emit mainSettings(ui->spinBox_height->value(), ui->spinBox_width->value(), difficulty,
                      ui->spinBox_blackout->value() * ui->checkBox_blackout->isChecked());
    this->close();
}

void SettingsDialog::on_pushButton_close_clicked(){
    this->close();
}

void SettingsDialog::on_checkBox_superUser_clicked(bool checked){
    if(checked){
        ui->spinBox_height->setMinimum(0);
        ui->spinBox_height->setMaximum(999);
        ui->spinBox_height->setSingleStep(1);
        ui->spinBox_width->setMinimum(0);
        ui->spinBox_width->setMaximum(999);
        ui->spinBox_width->setSingleStep(1);
    }
    else{
        ui->spinBox_height->setMinimum(20);
        ui->spinBox_height->setMaximum(100);
        ui->spinBox_height->setSingleStep(5);
        ui->spinBox_width->setMinimum(20);
        ui->spinBox_width->setMaximum(100);
        ui->spinBox_width->setSingleStep(5);
    }
}

void SettingsDialog::setAllToolTips(){
    ui->groupBox_difficulty->setToolTip ("Im wyższy stopień studności, tym dłuższa będzie\n"
                                         "droga od startu do mety.");
    ui->checkBox_blackout->setToolTip   ("Ogranicza pole widzenia w labiryncie.\n"
                                         "Zaznacz, aby dostosować rozmiar.");
    ui->checkBox_time->setToolTip       ("Masz ograniczony czas na przejście labiryntu.\n"
                                         "Zaznacz, aby dostosować limit.");
    ui->checkBox_superUser->setToolTip  ("Usuń ograniczenia rozmiaru labiryntu.\n\n"
                                         "Może powodować nieoczekiwane zachowanie programu.\n"
                                         "Używać z rozwagą.");
}

void SettingsDialog::on_checkBox_blackout_clicked(bool checked){
    ui->spinBox_blackout->setEnabled(checked);
}

void SettingsDialog::on_checkBox_time_clicked(bool checked){
    ui->spinBox_time->setEnabled(checked);
}
