#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();
    ui->lcd_time->hide();
    ui->lcd_time->setFixedHeight(20);
    this->setFixedSize(350, 350);

    game = new MazeManagment;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(measureTime()));
}

MainWindow::~MainWindow()
{
    delete timer;
    delete game;
    delete ui;
}

void MainWindow::measureTime()
{
    game->maze.seconds += timeInterval/1000.0;
    ui->lcd_time->display(game->maze.seconds);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (game->maze.array == NULL)
        return;

    switch (event->key())
    {
    case Qt::Key_W:
        if(isMovePossible(1))
            game->maze.currentPos.ry()--;
        break;
    case Qt::Key_A:
        if(isMovePossible(8))
            game->maze.currentPos.rx()--;
        break;
    case Qt::Key_S:
        if(isMovePossible(4))
            game->maze.currentPos.ry()++;
        break;
    case Qt::Key_D:
        if(isMovePossible(2))
            game->maze.currentPos.rx()++;
        break;
    case Qt::Key_P:
        game->maze.currentPos.setX(game->maze.width-1);
        game->maze.currentPos.setY(game->maze.end);
        break;
    }

    if (game->maze.currentPos.x() == game->maze.width)
        finish();

//    QString text = "X:" + QString::number(game->currentPos.x()) + " Y:" + QString::number(game->currentPos.y()) + "   Usuń mnie";
//    ui->statusBar->showMessage(text);

    update();
}

bool MainWindow::isMovePossible(int direction)
{
    return !(game->maze.array[game->maze.currentPos.y()][game->maze.currentPos.x()] & direction);
}

void MainWindow::finish()
{
    //zrob cos fajnego
    //game->deleteMaze();
    timer->stop();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if (game->maze.array == NULL)
        return;

    QPainter painter(this);
    for (int i=0; i<game->maze.height; i++)
        for (int j=0; j<game->maze.width; j++)
            drawSquare(&painter, grid(j, i), game->maze.array[i][j]);

    painter.setBrush(Qt::black);
    painter.drawEllipse(grid(game->maze.currentPos), mazeSize/2, mazeSize/2);
}

void MainWindow::drawSquare(QPainter *painter, QPoint point, int borders)
{
    if (borders & 1)
        painter->drawLine(point.x() - mazeSize, point.y() - mazeSize, point.x() + mazeSize, point.y() - mazeSize);
    if (borders & 2)
        painter->drawLine(point.x() + mazeSize, point.y() - mazeSize, point.x() + mazeSize, point.y() + mazeSize);
    if (borders & 4)
        painter->drawLine(point.x() + mazeSize, point.y() + mazeSize, point.x() - mazeSize, point.y() + mazeSize);
    if (borders & 8)
        painter->drawLine(point.x() - mazeSize, point.y() + mazeSize, point.x() - mazeSize, point.y() - mazeSize);
}

QPoint MainWindow::grid(int x, int y)
{
    QPoint point;
    point.setX(x * mazeSize*2 + marginLeft);
    point.setY(y * mazeSize*2 + marginTop);
    return point;
}

QPoint MainWindow::grid(QPoint point)
{
    point.setX(point.x() * mazeSize*2 + marginLeft);
    point.setY(point.y() * mazeSize*2 + marginTop);
    return point;
}

void MainWindow::showAll()
{
    ui->groupBox_main->show();
    ui->groupBox_difficulty->show();
    ui->groupBox_options->show();
    ui->groupBox_text->show();
    ui->pushButton_play->show();
    ui->lcd_time->hide();
}

void MainWindow::hideAll()
{
    ui->groupBox_main->hide();
    ui->groupBox_difficulty->hide();
    ui->groupBox_options->hide();
    ui->groupBox_text->hide();
    ui->pushButton_play->hide();
    ui->lcd_time->show();
}

void MainWindow::on_actionEasy_triggered()
{
    prepareMaze(20, 20, 1);
}

void MainWindow::on_actionMedium_triggered()
{
    prepareMaze(30, 30, 2);
}

void MainWindow::on_actionHard_triggered()
{
    prepareMaze(40, 40, 3);
}

void MainWindow::on_actionExpert_triggered()
{
    prepareMaze(50, 50, 4);
}

void MainWindow::on_actionRankingi_triggered()//
{

}

void MainWindow::on_actionNew_triggered()//
{

}

void MainWindow::on_actionOpen_triggered()//
{
    //game->loadMaze(game->mazeName);
}

void MainWindow::on_actionSave_triggered()//
{
    //if (game->mazeName != "NULL")
        //game->saveMaze(game->mazeName);

    //else
        //on_actionSaveAs_triggered();
}

void MainWindow::on_actionSaveAs_triggered()//
{

}

void MainWindow::on_actionCloseMaze_triggered()
{
    game->deleteMaze();
    this->setFixedSize(350, 350);
    showAll();

    timer->stop();
}

void MainWindow::on_pushButton_play_clicked()
{
    mazeSize = ui->spinBox_size->value();

    int difficulty;
    if (ui->radioButton_Easy->isChecked())
        difficulty = 1;
    if (ui->radioButton_Medium->isChecked())
        difficulty = 2;
    if (ui->radioButton_Hard->isChecked())
        difficulty = 3;
    if (ui->radioButton_Expert->isChecked())
        difficulty = 4;

    prepareMaze(ui->spinBox_height->value(), ui->spinBox_width->value(), difficulty);
}

void MainWindow::prepareMaze(int height, int width, int difficulty)
{
    game->createMaze(height, width, difficulty);
    this->setFixedSize((game->maze.width-1) * mazeSize*2 + marginLeft*2, (game->maze.height-1) * mazeSize*2 + marginTop + marginLeft);
    hideAll();
    game->maze.seconds = 0;
    timer->start(timeInterval);
}

void MainWindow::on_checkBox_superUser_clicked()
{
    ui->spinBox_height->setMaximum(1000);
    ui->spinBox_width->setMaximum(1000);
    ui->spinBox_size->setMaximum(1000);

    ui->spinBox_height->setMinimum(0);
    ui->spinBox_width->setMinimum(0);
    ui->spinBox_size->setMinimum(0);

    ui->checkBox_superUser->hide();
}
