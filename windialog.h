#ifndef WINDIALOG_H
#define WINDIALOG_H

#include <QDialog>
#include <maze.h>

#include <QDebug>

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
    void hideLeader();
    void highlightName();
    void unhighlightName();
    void highlightNick();
    void unhighlightNick();

signals:
    void fileName(QString);
    void nameAndNick(QString, QString);
    void testFileName(QString);
    void testNick(QString);

private slots:
    void on_cb_ranking_clicked(bool checked);
    void on_pb_Save_clicked();
    void on_pb_Close_clicked();
    void on_le_name_textChanged(const QString &arg1);
    void on_le_nick_textChanged(const QString &arg1);

private:
    Ui::WinDialog *ui;
};

#endif // WINDIALOG_H
