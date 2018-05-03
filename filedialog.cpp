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

void FileDialog::on_buttonBox_accepted()
{
    emit fileNameSignal(ui->le_fileName->text());
}

void FileDialog::on_tw_filesList_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->le_fileName->setText(item->text(0));
}
