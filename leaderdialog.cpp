#include "leaderdialog.h"
#include "ui_leaderdialog.h"

LeaderDialog::LeaderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LeaderDialog)
{
    ui->setupUi(this);
    this->setFixedSize(275, 200);
}

LeaderDialog::~LeaderDialog(){
    delete ui;
}

void LeaderDialog::setLabels(const QStringList &leaderInfo){
    int i = -1;

    ui->label_time1->setText(leaderInfo.at(++i) + "s");
    ui->label_time2->setText(leaderInfo.at(++i) + "s");
    ui->label_time3->setText(leaderInfo.at(++i) + "s");
    ui->label_time4->setText(leaderInfo.at(++i) + "s");

    ui->label_nick1->setText(leaderInfo.at(++i));
    ui->label_nick2->setText(leaderInfo.at(++i));
    ui->label_nick3->setText(leaderInfo.at(++i));
    ui->label_nick4->setText(leaderInfo.at(++i));
}

void LeaderDialog::on_pushButton_close_clicked(){
    this->close();
}

void LeaderDialog::on_pushButton_reset_clicked(){
    emit resetLeader();
}
