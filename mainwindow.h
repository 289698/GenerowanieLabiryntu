#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

#include <generating.h>
#include <filemanaging.h>

#include <customsettingsdialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionEasy_triggered();

    void on_actionMedium_triggered();

    void on_actionHard_triggered();

    void on_actionExpert_triggered();

    void on_actionCustomSettings_triggered();

private:
    Ui::MainWindow *ui;
    Generating *mazeGen;
    FileManaging *mazeSave;

    int **mazeArray = NULL;
    int mazeHeight = -1, mazeWidth = -1, startingRow = -1, endingRow = -1;

    void generateMazeArray(int mazeHeight, int mazeWidth, int difficulty, string fileName);
    void newIntArray (int **&adress, int w, int k);
    void deleteIntArray (int **&adress, int w);

    void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H
