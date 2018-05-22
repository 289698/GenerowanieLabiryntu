#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <cmath>
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
    void on_action_easy_triggered(){
        prepareMaze(20, 20, 1, 0);
    }
    void on_action_medium_triggered(){
        prepareMaze(30, 30, 2, 0);
    }
    void on_action_hard_triggered(){
        prepareMaze(40, 40, 3, 0);
    }
    void on_action_expert_triggered(){
        prepareMaze(50, 50, 4, 0);
    }
    void on_action_leader_triggered();
    void on_action_new_triggered();
    void on_action_load_triggered();
    void on_action_save_triggered();
    void on_action_saveAs_triggered();
    void on_action_close_triggered();

    void on_pushButton_easy_clicked(){
        on_action_easy_triggered();
    }
    void on_pushButton_medium_clicked(){
        on_action_medium_triggered();
    }
    void on_pushButton_hard_clicked(){
        on_action_hard_triggered();
    }
    void on_pushButton_expert_clicked(){
        on_action_expert_triggered();
    }
    void on_pushButton_leader_clicked(){
        on_action_leader_triggered();
    }
    void on_pushButton_new_clicked(){
        on_action_new_triggered();
    }
    void on_pushButton_load_clicked(){
        on_action_load_triggered();
    }
    void on_pushButton_exit_clicked(){
        this->close();
    }
    void on_pushButton_minus_clicked();
    void on_pushButton_plus_clicked();

    void measureTime();
    void prepareMaze(int height, int width, int difficulty, int blackout_size, bool is_default = 0);

private:
    Ui::MainWindow *ui;
    MazeManagment *game;
    SettingsDialog *setting;
    QTimer *timer = NULL, *for_time_timer = NULL;

    const int kTimeInterval = 100, kWindowWidth = 300, kWindowHeight = 280;
    int margin_top = 75, margin_bottom = 45, margin_left = 20;
    int maze_size = 8;
    bool is_painter_off = 0;
    int blackout_size = 0;

    void resizeWindow(){
        this->setFixedSize((game->maze->width-1) * maze_size*2 + margin_left*2,
                           (game->maze->height-1) * maze_size*2 + margin_top + margin_bottom);
    }
    void finish();
    void fillLabels();
    void hideLabels();
    void startGame();
    void pauseGame();

    void keyPressEvent(QKeyEvent *event);
    bool isMovePossible(int direction){
        return !(game->maze->array[game->maze->current_pos.y()][game->maze->current_pos.x()] & direction);
    }
    void paintEvent(QPaintEvent *);
    void drawSquare(QPainter *painter, QPoint pos, int borders);
    QPoint grid(int x, int y);
    QPoint grid(QPoint point);
};

#endif // MAINWINDOW_H
