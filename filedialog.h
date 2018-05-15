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

    void addFileInfo(const QStringList &fileInfo);
    void changeButtonText(const QString &name);
    void highlightLine();
    void unhighlightLine();
    void clearLine();
    void clearTree();

private slots:
    void on_tw_filesList_itemClicked(QTreeWidgetItem *item, int column);
    void on_pb_Accept_clicked();
    void on_pb_Delete_clicked();
    void on_pb_Close_clicked();
    void on_le_fileName_textChanged(const QString &arg1);

signals:
    void testFileName(QString);
    void fileName(QString);
    void deleteFile(QString);

private:
    Ui::FileDialog *ui;
};

#endif // FILEDIALOG_H
