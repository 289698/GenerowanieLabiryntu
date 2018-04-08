#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    deleteIntArray(mazeArray, mazeHeight);

    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if (mazeArray == NULL)
    {
        generateMazeArray(50, 50, 3, "Custom");
    }

    QPainter painter(this);

    for (int i=0; i<mazeHeight; i++)
    {
        for (int j=0; j<mazeWidth; j++)
        {
            int w = 10, x = j*w + 50, y = i*w + 50;

            if (mazeArray[i][j] & 1)
                painter.drawLine(x, y, x+w, y);

            if (mazeArray[i][j] & 2)
                painter.drawLine(x+w, y, x+w, y+w);

            if (mazeArray[i][j] & 4)
                painter.drawLine(x, y+w, x+w, y+w);

            if (mazeArray[i][j] & 8)
                painter.drawLine(x, y, x, y+w);
        }
    }
}

void MainWindow::newIntArray(int **&adress, int w, int k)
{
    if (adress != NULL)
        return;

    adress = new int *[w];
        for (int i=0; i<w; i++)
    adress[i] = new int [k];
}

void MainWindow::deleteIntArray (int **&adress, int w)
{
    if (adress == NULL)
        return;

    for (int i=0; i<w; i++)
        delete[] adress[i];
    delete adress;

    adress = NULL;
}

void MainWindow::generateMazeArray(int mazeHeight, int mazeWidth, int difficulty, string fileName)
{
    deleteIntArray(mazeArray, this->mazeHeight);
    newIntArray(mazeArray, mazeHeight, mazeWidth);

    this->mazeHeight = mazeHeight; this->mazeWidth = mazeHeight;
    startingRow = 0; endingRow = 0;

    mazeGen = new Generating(mazeArray, mazeHeight, mazeWidth, difficulty);
    endingRow = mazeGen->generateMaze(startingRow);
    delete mazeGen;

    mazeSave = new FileManaging;
    mazeSave->saveMaze(mazeArray, mazeHeight, mazeWidth, fileName);
    delete mazeSave;
}

void MainWindow::on_actionEasy_triggered()
{
    generateMazeArray(20, 20, 1, "Easy");
    //paintEvent();
}

void MainWindow::on_actionMedium_triggered()
{
    generateMazeArray(30, 30, 2, "Medium");
}

void MainWindow::on_actionHard_triggered()
{
    generateMazeArray(40, 40, 3, "Hard");
}

void MainWindow::on_actionExpert_triggered()
{
    generateMazeArray(50, 50, 4, "Expert");
}

void MainWindow::on_actionCustomSettings_triggered()
{
    CustomSettingsDialog popUp;
    popUp.setModal(true);
    popUp.exec();
}
