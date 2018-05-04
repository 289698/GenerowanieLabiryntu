#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QTreeWidgetItem>

namespace Ui {
class FileDialog;
}

class FileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileDialog(QWidget *parent = 0);
    ~FileDialog();

    void addFileInfo(QStringList fileInfo);
    void hideSaveButton();
    void hideOpenButton();
    void hideDeleteButton();

    void clearTree();

private slots:
    void on_tw_filesList_itemClicked(QTreeWidgetItem *item, int column);

    void on_pb_Open_clicked();

    void on_pb_Save_clicked();

    void on_pb_Delete_clicked();

    void on_pb_Close_clicked();

signals:
    void fileNameSignal(QString);
    void deleteFileSignal(QString);

private:
    Ui::FileDialog *ui;
};

#endif // FILEDIALOG_H
