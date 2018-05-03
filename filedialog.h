#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QDialog>
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

private slots:
    void on_buttonBox_accepted();

    void on_tw_filesList_itemClicked(QTreeWidgetItem *item, int column);

signals:
    void fileNameSignal(QString);

private:
    Ui::FileDialog *ui;
};

#endif // FILEDIALOG_H
