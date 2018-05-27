/*! \file settingdialog.h
 * Klasa okna z ustawieniami nowego labiryntu.
 */
#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}
//! Klasa okna z ustawieniami nowego labiryntu.
class SettingsDialog : public QDialog{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

signals:
    //! Wysyła informacje o labiryncie do void MainWindow::prepareMaze(int height, int width, int difficulty, bool is_default = 0).
    void mainSettings(int,int,int);

private slots:
    //! Wysyła informacje o labiryncie do void MainWindow::prepareMaze(int height, int width, int difficulty, bool is_default = 0).
    void on_pushButton_play_clicked();
    //! Zamyka okno.
    void on_pushButton_close_clicked(){
        this->close();
    }

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
