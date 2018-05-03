#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include "mazemanagment.h"

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
    void on_actionRankingi_triggered();
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_pushButton_play_clicked();
    void on_checkBox_superUser_clicked();
    void measureTime();

private:
    Ui::MainWindow *ui;
    MazeManagment *game;
    QTimer *timer = NULL;

    const int marginTop = 65, marginLeft = 20, timeInterval = 100;
    int mazeSize = 7;

    void keyPressEvent(QKeyEvent *event);
    bool isMovePossible(int direction);
    void finish();

    void paintEvent(QPaintEvent *);
    void drawSquare(QPainter *painter, QPoint pos, int borders);
    QPoint grid(int x, int y);
    QPoint grid(QPoint point);
    void hideAll();
    void showAll();

    void prepareMaze(int height, int width, int difficulty);
};

#endif // MAINWINDOW_H
