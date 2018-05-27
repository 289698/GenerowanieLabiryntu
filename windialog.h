/*! \file windialog.h
 * Klasa okna pojawiającego się po przejściu labiryntu.
 */
#ifndef WINDIALOG_H
#define WINDIALOG_H

#include <QDialog>
#include <maze.h>

#include <QDebug>

namespace Ui {
class WinDialog;
}
//! Klasa okna pojawiającego się po przejściu labiryntu.
class WinDialog : public QDialog{
    Q_OBJECT
public:
    explicit WinDialog(QWidget *parent = 0);
    ~WinDialog();
    //! Wypisuje w oknie informacje o labiryncie, który został zakończony.
    void fillLineEdits(MazeStruct *maze);
    //! Chowa widgety opowiedzialne za zapis wyniki do rankingu.
    void hideLeader();
    //! Podświetla pole wpisywania nazwy labiryntu.
    void highlightName();
    //! Resetuje podświetlenie pola wpisywania nazwy labiryntu.
    void unhighlightName();
    //! Podświetla pole wpisywania nicku.
    void highlightNick();
    //! Resetuje podświetlenie pola wpisywania nicku.
    void unhighlightNick();

signals:
    void fileName(QString);
    void nameAndNick(QString, QString);
    void testFileName(QString);
    void testNick(QString);

private slots:
    //! Chowa lub pokazuje pole wpisywania nicku.
    void on_cb_ranking_clicked(bool checked);
    //! Zapisuje labirynt (i ewentualnie rekord do rankingu).
    void on_pb_Save_clicked();
    //! Zamyka okno.
    void on_pb_Close_clicked();
    void on_le_name_textChanged(const QString &arg1);
    void on_le_nick_textChanged(const QString &arg1);

private:
    Ui::WinDialog *ui;
};

#endif // WINDIALOG_H
