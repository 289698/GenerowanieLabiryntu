#include "filedialog.h"
#include "ui_filedialog.h"

FileDialog::FileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileDialog)
{
    ui->setupUi(this);
    unhighlightLine();
}

FileDialog::~FileDialog(){
    delete ui;
}

void FileDialog::on_pb_Accept_clicked(){
    emit fileName(ui->le_fileName->text());
}

void FileDialog::on_pb_Delete_clicked(){
    if (ui->le_fileName->text().isEmpty()){
        highlightLine();
        return;
    }
    emit deleteFile(ui->le_fileName->text());
}

void FileDialog::on_pb_Close_clicked(){
    this->close();
}

void FileDialog::on_le_fileName_textChanged(const QString &arg1){
    emit testFileName(arg1);
}

void FileDialog::addFileInfo(const QStringList &fileInfo){
    QTreeWidgetItem *fileInfoItem = new QTreeWidgetItem(ui->tw_filesList, fileInfo);
    ui->tw_filesList->addTopLevelItem(fileInfoItem);
}

void FileDialog::on_tw_filesList_itemClicked(QTreeWidgetItem *item, int column){
    ui->le_fileName->setText(item->text(0));
}

void FileDialog::clearTree(){
    ui->tw_filesList->clear();
}

void FileDialog::changeButtonText(const QString &name){
    ui->pb_Accept->setText(name);
}

void FileDialog::highlightLine(){
    ui->le_fileName->setStyleSheet("QLineEdit {"
                                   "border-width: 1px;"
                                   "border-style: solid;"
                                   "border-color: rgb(255, 70, 70); }");
}

void FileDialog::unhighlightLine(){
    ui->le_fileName->setStyleSheet("QLineEdit {"
                                   "border-width: 1px;"
                                   "border-style: solid; }");
}

void FileDialog::clearLine(){
    ui->le_fileName->setText("");
}
