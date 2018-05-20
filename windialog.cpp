#include "windialog.h"
#include "ui_windialog.h"

WinDialog::WinDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinDialog)
{
    ui->setupUi(this);
    unhighlightName();
    unhighlightNick();
    this->setFixedSize(280, 300);
    ui->label_hxw->setFixedWidth(70);
    ui->label_difficulty->setFixedWidth(70);
    ui->label_seconds->setFixedWidth(70);
}

WinDialog::~WinDialog(){
    delete ui;
}

void WinDialog::on_cb_ranking_clicked(bool checked){
    if (checked){
        ui->label_nick->show();
        ui->le_nick->show();
        this->setFixedSize(280, 300);
    }
    else{
        ui->label_nick->hide();
        ui->le_nick->hide();
        this->setFixedSize(280, 255);
    }
}

void WinDialog::hideLeader(){
    ui->cb_ranking->hide();
    ui->cb_ranking->setChecked(0);
    ui->label_nick->hide();
    ui->le_nick->hide();
    this->setFixedSize(280, 200);
}

void WinDialog::fillLineEdits(MazeStruct *maze){
    ui->le_name->setText(maze->name);
    ui->label_hxw->setText(QString::number(maze->height) + " x " + QString::number(maze->width));
    ui->label_seconds->setText(QString::number(maze->seconds/1000.0) + "s");

    switch (maze->difficulty){
    case 1:
        ui->label_difficulty->setText("Łatwy");
    break;
    case 2:
        ui->label_difficulty->setText("Średni");
    break;
    case 3:
        ui->label_difficulty->setText("Trudny");
    break;
    case 4:
        ui->label_difficulty->setText("Ekspert");
    break;
    default:
        ui->label_difficulty->setText(QString::number(maze->difficulty));
    }
}

void WinDialog::on_pb_Save_clicked(){
    if (ui->cb_ranking->isChecked())
        emit nameAndNick(ui->le_name->text(), ui->le_nick->text());
    else
        emit fileName(ui->le_name->text());
}

void WinDialog::on_pb_Close_clicked(){
    this->close();
}

void WinDialog::highlightName(){
    ui->le_name->setStyleSheet("QLineEdit {"
                               "border-width: 1px;"
                               "border-style: solid;"
                               "border-color: rgb(255, 70, 70); }");
}

void WinDialog::unhighlightName(){
    ui->le_name->setStyleSheet("QLineEdit {"
                               "border-width: 1px;"
                               "border-style: solid; }");
}

void WinDialog::highlightNick(){
    ui->le_nick->setStyleSheet("QLineEdit {"
                               "border-width: 1px;"
                               "border-style: solid;"
                               "border-color: rgb(255, 70, 70); }");
}

void WinDialog::unhighlightNick(){
    ui->le_nick->setStyleSheet("QLineEdit {"
                               "border-width: 1px;"
                               "border-style: solid; }");
}

void WinDialog::on_le_name_textChanged(const QString &arg1){
    emit testFileName(arg1);
}

void WinDialog::on_le_nick_textChanged(const QString &arg1){
    if (ui->cb_ranking->isChecked())
        emit testNick(arg1);
}
