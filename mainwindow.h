#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

#include <generating.h>
#include <dialog.h>
//#include <filemanaging.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//    int posX = 50, posY = 50;

private slots:
    void on_actionEasy_triggered();

    void on_actionMedium_triggered();

    void on_actionHard_triggered();

    void on_actionExpert_triggered();

    void on_actionRankingi_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionCloseMaze_triggered();

    void on_actionNew_triggered();

    void on_pushButton_play_clicked();

    void on_checkBox_superUser_clicked();

private:
    Ui::MainWindow *ui;
    Generating *mazeGen;
    //FileManaging *mazeSave;

    int **mazeArray = NULL;
    int mazeHeight, mazeWidth, mazeSize = 15, mazeDifficulty = 1;
    int marginTop, marginLeft;
    int startingPoint, endingPoint;

    void generateMazeArray();
    void setMazeProperties(int mazeHeight, int mazeWidth, int mazeDifficulty);
    void newIntArray();
    void deleteIntArray();

    void paintEvent (QPaintEvent *);
    void drawMaze (QPainter *painter);
    void hideAll();
    void showAll();
};

#endif // MAINWINDOW_H
