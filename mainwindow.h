#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include "mazemanagment.h"
#include "settingsdialog.h"

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
//    void alterMazeSize();

    void on_pushButton_new_clicked();
    void on_pushButton_load_clicked();
    void on_pushButton_leader_clicked();
    void on_pushButton_exit_clicked();
    void on_pushButton_easy_clicked();
    void on_pushButton_medium_clicked();
    void on_pushButton_hard_clicked();
    void on_pushButton_expert_clicked();
    void on_pushButtonMinus_clicked();
    void on_pushButtonPlus_clicked();

private:
    Ui::MainWindow *ui;
    MazeManagment *game;
    SettingsDialog *setting;
    QTimer *timer = NULL;

    const int kTimeInterval = 100, kWindowWidth = 300, kWindowHeight = 280;
    int margin_top = 75, margin_bottom = 45, margin_left = 20;
    int maze_size = 8;
    bool is_painter_off = 0;

    inline void resizeWindow(){
        this->setFixedSize((game->maze->width-1) * maze_size*2 + margin_left*2, (game->maze->height-1) * maze_size*2 + margin_top + margin_bottom);}

    void finish();
    void fillLabels();
    void hideLabels();
    void startGame();
    void pauseGame();

    void keyPressEvent(QKeyEvent *event);
    bool isMovePossible(int direction);

    void paintEvent(QPaintEvent *);
    void drawSquare(QPainter *painter, QPoint pos, int borders);
    QPoint grid(int x, int y);
    QPoint grid(QPoint point);

    //void resizeEvent(QResizeEvent* event);
};

#endif // MAINWINDOW_H
