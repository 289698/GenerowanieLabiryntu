#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();
    marginTop = mazeSize + 25;
    marginLeft = mazeSize + 5;
}

MainWindow::~MainWindow()
{
    deleteIntArray();
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(mazeArray == NULL)
    {
        this->resize(350, 300);
        showAll();
        return;
    }

    QPainter painter(this);
    drawMaze(&painter);
    hideAll();
}

void MainWindow::showAll()
{
    ui->groupBox_main->show();
    ui->groupBox_difficulty->show();
    ui->groupBox_options->show();
    ui->groupBox_text->show();
    ui->pushButton_play->show();
}

void MainWindow::hideAll()
{
    ui->groupBox_main->hide();
    ui->groupBox_difficulty->hide();
    ui->groupBox_options->hide();
    ui->groupBox_text->hide();
    ui->pushButton_play->hide();
}

void MainWindow::drawMaze(QPainter *painter)
{
    int x = marginLeft, y = marginTop;

    for (int i=0; i<mazeHeight; i++)
    {
        x = marginLeft;

        for (int j=0; j<mazeWidth; j++)
        {
            if (mazeArray[i][j] & 1)
                painter->drawLine(x, y, x + mazeSize, y);

            if (mazeArray[i][j] & 2)
                painter->drawLine(x + mazeSize, y, x + mazeSize, y + mazeSize);

            if (mazeArray[i][j] & 4)
                painter->drawLine(x, y + mazeSize, x + mazeSize, y + mazeSize);

            if (mazeArray[i][j] & 8)
                painter->drawLine(x, y, x, y + mazeSize);

            x += mazeSize + 1;
        }

        y += mazeSize + 1;
    }

    painter->drawRect(marginLeft-1, marginTop-1, x-marginLeft+1, y-marginTop+1);

    painter->eraseRect(marginLeft-1, startingPoint*(mazeSize+1) + marginTop, 2, mazeSize);
    painter->eraseRect(x, endingPoint*(mazeSize+1) + marginTop, 2, mazeSize);

    painter->drawRect(marginLeft, startingPoint*(mazeSize+1) + marginTop, -mazeSize/2, -1);
    painter->drawRect(marginLeft, (startingPoint+1)*(mazeSize+1) + marginTop, -mazeSize/2, -1);

    painter->drawRect(x, endingPoint*(mazeSize+1) + marginTop, mazeSize/2, -1);
    painter->drawRect(x, (endingPoint+1)*(mazeSize+1) + marginTop, mazeSize/2, -1);

    this->resize(x + marginLeft, y + marginLeft);
}

void MainWindow::newIntArray()
{
    if (mazeArray != NULL)
        return;

    mazeArray = new int *[mazeHeight];
        for (int i=0; i<mazeHeight; i++)
    mazeArray[i] = new int [mazeWidth];
}

void MainWindow::deleteIntArray ()
{
    if (mazeArray == NULL)
        return;

    for (int i=0; i<mazeHeight; i++)
        delete[] mazeArray[i];
    delete mazeArray;

    mazeArray = NULL;
}

void MainWindow::setMazeProperties(int mazeHeight, int mazeWidth, int mazeDifficulty)
{
    this->mazeHeight = mazeHeight;
    this->mazeWidth = mazeWidth;
    this->mazeDifficulty = mazeDifficulty;
}

void MainWindow::generateMazeArray()
{
    mazeGen = new Generating(mazeArray, mazeHeight, mazeWidth, mazeDifficulty);
    mazeGen->generateMaze(startingPoint, endingPoint);
    delete mazeGen;
}

void MainWindow::on_actionEasy_triggered()
{
    deleteIntArray();

    setMazeProperties(20, 20, 1);

    newIntArray();

    generateMazeArray();

    update();
}

void MainWindow::on_actionMedium_triggered()
{
    deleteIntArray();

    setMazeProperties(30, 30, 2);

    newIntArray();

    generateMazeArray();

    update();
}

void MainWindow::on_actionHard_triggered()
{
    deleteIntArray();

    setMazeProperties(40, 40, 3);

    newIntArray();

    generateMazeArray();

    update();
}

void MainWindow::on_actionExpert_triggered()
{
    deleteIntArray();

    setMazeProperties(50, 50, 4);

    newIntArray();

    generateMazeArray();

    update();
}

void MainWindow::on_actionRankingi_triggered()
{

}

void MainWindow::on_actionOpen_triggered()
{

}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionSaveAs_triggered()
{

}

void MainWindow::on_actionCloseMaze_triggered()
{
    deleteIntArray();

    update();
}

void MainWindow::on_actionNew_triggered()
{
    deleteIntArray();

    update();
}

void MainWindow::on_pushButton_play_clicked()
{
    deleteIntArray();

    mazeHeight = ui->spinBox_height->value();
    mazeWidth = ui->spinBox_width->value();
    mazeSize = ui->spinBox_size->value();

    if (ui->radioButton_Easy->isChecked())
        mazeDifficulty = 1;
    if (ui->radioButton_Medium->isChecked())
        mazeDifficulty = 2;
    if (ui->radioButton_Hard->isChecked())
        mazeDifficulty = 3;
    if (ui->radioButton_Expert->isChecked())
        mazeDifficulty = 4;

    newIntArray();

    generateMazeArray();

    update();
}
