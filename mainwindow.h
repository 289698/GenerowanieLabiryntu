#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include "mazemanagment.h"
#include "settingsdialog.h"

#include "warningdialog.h"

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
    void on_actionClose_triggered();

    void measureTime();
    void prepareMaze(int height, int width, int difficulty, bool isDefault = 0);
    void alterMazeSize();

    void on_pushButton_new_clicked();
    void on_pushButton_load_clicked();
    void on_pushButton_leader_clicked();
    void on_pushButton_exit_clicked();
    void on_pushButton_easy_clicked();
    void on_pushButton_medium_clicked();
    void on_pushButton_hard_clicked();
    void on_pushButton_expert_clicked();

private:
    Ui::MainWindow *ui;
    MazeManagment *game;
    SettingsDialog *setting;
    QTimer *timer = NULL;

    const int timeInterval = 100;
    int marginTop = 65, marginLeft = 20;
    double mazeSize = 7;
    bool isPainterOff = 0;

    void keyPressEvent(QKeyEvent *event);
    bool isMovePossible(int direction);
    void finish();
    void fillLabels();
    void hideLabels();
    void pauseGame();
    void startGame();

    void paintEvent(QPaintEvent *);
    void drawSquare(QPainter *painter, QPoint pos, int borders);
    QPoint grid(int x, int y);
    QPoint grid(QPoint point);

    void resizeEvent(QResizeEvent* event);
};

#endif // MAINWINDOW_H
