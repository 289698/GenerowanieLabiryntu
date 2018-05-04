#include "filedialog.h"
#include "ui_filedialog.h"

FileDialog::FileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileDialog)
{
    ui->setupUi(this);
}

FileDialog::~FileDialog()
{
    delete ui;
}

void FileDialog::addFileInfo(QStringList fileInfo)
{
    QTreeWidgetItem *fileInfoItem = new QTreeWidgetItem(ui->tw_filesList, fileInfo);

    ui->tw_filesList->addTopLevelItem(fileInfoItem);
}

void FileDialog::on_tw_filesList_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->le_fileName->setText(item->text(0));
}

void FileDialog::hideOpenButton()
{
    ui->pb_Open->hide();
}

void FileDialog::hideSaveButton()
{
    ui->pb_Save->hide();
}

void FileDialog::hideDeleteButton()
{
    ui->pb_Delete->hide();
}

void FileDialog::clearTree()
{
    ui->tw_filesList->clear();
}

void FileDialog::on_pb_Open_clicked()
{
    if (ui->le_fileName->text().isEmpty())
    {
        ui->le_fileName->setStyleSheet("QLineEdit { background: rgb(255, 100, 100); }");
        return;
    }
    emit fileNameSignal(ui->le_fileName->text());

    this->close();
}

void FileDialog::on_pb_Save_clicked()
{
    if (ui->le_fileName->text().isEmpty())
    {
        ui->le_fileName->setStyleSheet("QLineEdit { background: rgb(255, 100, 100); }");
        return;
    }
    emit fileNameSignal(ui->le_fileName->text());
    this->close();
}

void FileDialog::on_pb_Delete_clicked()
{
    if (ui->le_fileName->text().isEmpty())
    {
        ui->le_fileName->setStyleSheet("QLineEdit { background: rgb(255, 100, 100); }");
        return;
    }
    emit deleteFileSignal(ui->le_fileName->text());
}

void FileDialog::on_pb_Close_clicked()
{
    this->close();
}
