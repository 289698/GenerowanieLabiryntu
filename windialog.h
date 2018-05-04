#ifndef WINDIALOG_H
#define WINDIALOG_H

#include <QDialog>
#include <maze.h>

namespace Ui {
class WinDialog;
}

class WinDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WinDialog(QWidget *parent = 0);
    ~WinDialog();
    void fillLineEdits(MazeStruct *maze);

signals:
    void fileNameSignal(QString);

private slots:
    void on_cb_ranking_clicked(bool checked);
    void on_pb_Save_clicked();
    void on_pb_Close_clicked();

private:
    Ui::WinDialog *ui;
};

#endif // WINDIALOG_H
