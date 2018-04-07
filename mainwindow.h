#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

#include <generating.h>
#include <drawing.h>
#include <filemanaging.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent*);

private:
    Ui::MainWindow *ui;
    void drawMaze();


};

#endif // MAINWINDOW_H
