/*! \file leaderdialog.h
 * Klasa zawierająca definicję okienka z rankingami.
 */
#ifndef LEADERDIALOG_H
#define LEADERDIALOG_H

#include <QDialog>

namespace Ui {
class LeaderDialog;
}
//! Klasa zawierająca definicję okienka z rankingami.
class LeaderDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LeaderDialog(QWidget *parent = 0);
    ~LeaderDialog();
    //! Zmienia tekst wyświetlany w okienku na podstawie argumentu. \param leaderInfo {Lista danych typu QString, 1-4 to czasy, 5-8 to nicki}
    void setLabels(const QStringList &leaderInfo);

signals:
    //! Resetuje rankingi. \see void FileManagment::resetLeader()
    void resetLeader();

private slots:
    //! Zamyka okno.
    void on_pushButton_close_clicked();
    //! Wysyła sygnał resetLeader().
    void on_pushButton_reset_clicked();

private:
    Ui::LeaderDialog *ui;
};

#endif // LEADERDIALOG_H
