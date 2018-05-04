#include "windialog.h"
#include "ui_windialog.h"

WinDialog::WinDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinDialog)
{
    ui->setupUi(this);

    this->setFixedSize(280, 300);
    ui->le_hxw->setFixedWidth(70);
    ui->le_hxw->setReadOnly(1);
    ui->le_difficulty->setFixedWidth(70);
    ui->le_difficulty->setReadOnly(1);
    ui->le_seconds->setFixedWidth(70);
    ui->le_seconds->setReadOnly(1);
}

WinDialog::~WinDialog()
{
    delete ui;
}

void WinDialog::on_cb_ranking_clicked(bool checked)
{
    if (checked)
    {
        ui->label_nick->show();
        ui->le_nick->show();
        this->setFixedSize(280, 300);
    }
    else
    {
        ui->label_nick->hide();
        ui->le_nick->hide();
        this->setFixedSize(280, 255);
    }
}

void WinDialog::fillLineEdits(MazeStruct *maze)
{
    ui->le_name->setText(maze->name);
    ui->le_hxw->setText(QString::number(maze->height) + " x " + QString::number(maze->width));
    ui->le_seconds->setText(QString::number(maze->seconds/1000.0) + "s");

    switch (maze->difficulty)
    {
    case 1:
        ui->le_difficulty->setText("Łatwy");
        break;
    case 2:
        ui->le_difficulty->setText("Średni");
        break;
    case 3:
        ui->le_difficulty->setText("Trudny");
        break;
    case 4:
        ui->le_difficulty->setText("Ekspert");
        break;
    default:
        ui->le_difficulty->setText(QString::number(maze->difficulty));
    }
}

void WinDialog::on_pb_Save_clicked()
{
    if (ui->le_name->text().isEmpty())
    {
        ui->le_name->setStyleSheet("QLineEdit { background: rgb(255, 100, 100); }");
        ui->le_name->setPlaceholderText("Musisz wpisać nazwę, aby zapisać");
        return;
    }

    emit fileNameSignal(ui->le_name->text());

    this->close();
}

void WinDialog::on_pb_Close_clicked()
{
    this->close();
}
