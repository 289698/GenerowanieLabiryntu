#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    WarningDialog *warning = new WarningDialog;
    warning->exec();
    delete warning;

    ui->setupUi(this);
    ui->mainToolBar->hide();
    game = new MazeManagment;

    hideLabels();
    this->resize(250, 250);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(measureTime()));
}

MainWindow::~MainWindow(){
    delete timer;
    delete game;
    delete ui;
}

void MainWindow::measureTime(){
    game->maze->seconds += timeInterval;
    ui->lcd_time->display(game->maze->seconds/1000.0);
}

void MainWindow::resizeEvent(QResizeEvent* event){
//    QMainWindow::resizeEvent(event);
//    if (game->maze->array != NULL)
//    {
//        mazeSize = (this->size().width() - marginLeft*2.0) / game->maze->width / 2;
//        marginTop = 50 + mazeSize*2;
//        marginLeft = 25 + mazeSize*2;
//    }

//    QString text = QString::number(this->size().width()) + " x " + QString::number(this->size().height()) + "   " + QString::number(mazeSize);
//    ui->statusBar->showMessage(text);
}
void MainWindow::alterMazeSize(){
    //mazeSize = (this->size().width() - marginLeft*2) / game->maze->width;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if (game->maze->array == NULL)
        return;

    switch (event->key()){
    case Qt::Key_W:
        if(isMovePossible(1))
            game->maze->currentPos.ry()--;
        break;
    case Qt::Key_A:
        if(isMovePossible(8))
            game->maze->currentPos.rx()--;
        break;
    case Qt::Key_S:
        if(isMovePossible(4))
            game->maze->currentPos.ry()++;
        break;
    case Qt::Key_D:
        if(isMovePossible(2))
            game->maze->currentPos.rx()++;
        break;
    case Qt::Key_P:
        game->maze->currentPos.setX(game->maze->width-1);
        game->maze->currentPos.setY(game->maze->end);
        break;
    }

    if (game->maze->currentPos.x() == game->maze->width)
        finish();

    //QString text = "X:" + QString::number(game->maze->currentPos.x()) + " Y:" + QString::number(game->maze->currentPos.y()) + "   Usuń mnie";
    //ui->statusBar->showMessage(text);

    update();
}

bool MainWindow::isMovePossible(int direction){
    return !(game->maze->array[game->maze->currentPos.y()][game->maze->currentPos.x()] & direction);
}

void MainWindow::finish(){
    timer->stop();
    game->finish();
    this->resize(250, 250);
    hideLabels();
}

void MainWindow::paintEvent(QPaintEvent *){
    if (game->maze->array == NULL || isPainterOff)
        return;

    QPainter painter(this);
    for (int i=0; i<game->maze->height; ++i)
        for (int j=0; j<game->maze->width; j++)
            drawSquare(&painter, grid(j, i), game->maze->array[i][j]);

    painter.setBrush(Qt::black);
    painter.drawEllipse(grid(game->maze->currentPos), int(mazeSize/2), int(mazeSize/2));
}

void MainWindow::drawSquare(QPainter *painter, QPoint point, int borders){
    if (borders & 1)
        painter->drawLine(point.x() - mazeSize, point.y() - mazeSize, point.x() + mazeSize, point.y() - mazeSize);
    if (borders & 2)
        painter->drawLine(point.x() + mazeSize, point.y() - mazeSize, point.x() + mazeSize, point.y() + mazeSize);
    if (borders & 4)
        painter->drawLine(point.x() + mazeSize, point.y() + mazeSize, point.x() - mazeSize, point.y() + mazeSize);
    if (borders & 8)
        painter->drawLine(point.x() - mazeSize, point.y() + mazeSize, point.x() - mazeSize, point.y() - mazeSize);
}

QPoint MainWindow::grid(int x, int y){
    QPoint point;
    point.setX(x * mazeSize*2 + marginLeft);
    point.setY(y * mazeSize*2 + marginTop);
    return point;
}

QPoint MainWindow::grid(QPoint point){
    point.setX(point.x() * mazeSize*2 + marginLeft);
    point.setY(point.y() * mazeSize*2 + marginTop);
    return point;
}

void MainWindow::on_actionEasy_triggered(){
    prepareMaze(20, 20, 1, 1);
}

void MainWindow::on_actionMedium_triggered(){
    prepareMaze(30, 30, 2, 1);
}

void MainWindow::on_actionHard_triggered(){
    prepareMaze(40, 40, 3, 1);
}

void MainWindow::on_actionExpert_triggered(){
    prepareMaze(50, 50, 4, 1);
}

void MainWindow::on_actionRankingi_triggered(){
    pauseGame();

    game->openLeader();

    startGame();
}

void MainWindow::on_actionNew_triggered(){
    pauseGame();

    setting = new SettingsDialog;
    connect(setting, SIGNAL(mazeInfo(int,int,int)), this, SLOT(prepareMaze(int,int,int)));
    setting->setModal(0);
    setting->exec();
    delete setting;

    startGame();
}

void MainWindow::on_actionOpen_triggered(){
    pauseGame();

    game->load();
    if (game->maze->array != NULL)
    {
        fillLabels();
        this->resize((game->maze->width-1) * mazeSize*2 + marginLeft*2, (game->maze->height-1) * mazeSize*2 + marginTop + marginLeft);
    }

    startGame();
}

void MainWindow::on_actionSave_triggered(){
    pauseGame();

    if (game->maze->array != NULL)
        game->save();

    startGame();
}

void MainWindow::on_actionSaveAs_triggered(){
    pauseGame();

    if (game->maze->array != NULL)
        game->saveAs();

    startGame();
}

void MainWindow::on_actionClose_triggered(){
    timer->stop();
    hideLabels();
    game->deleteMaze();
    update();
    this->resize(250, 250);
}

void MainWindow::prepareMaze(int height, int width, int difficulty, bool isDefault){
    game->create(height, width, difficulty);
    game->maze->isDefault = isDefault;
    fillLabels();
    this->resize((game->maze->width-1) * mazeSize*2 + marginLeft*2, (game->maze->height-1) * mazeSize*2 + marginTop + marginLeft);
    timer->start(timeInterval);
    update();
}

void MainWindow::fillLabels(){
    ui->label_name->setText(game->maze->name);
    ui->label_size->setText(QString::number(game->maze->height) + " x " + QString::number(game->maze->width));
    switch (game->maze->difficulty)    {
    case 1:
        ui->label_difficulty->setText("Łatwy");
        break;
    case 2:
        ui->label_difficulty->setText("Średni");
        break;
    case 3:
        ui->label_difficulty->setText("Trudny");
        break;
    case 4:
        ui->label_difficulty->setText("Ekspert");
        break;
    default:
        ui->label_difficulty->setText(QString::number(game->maze->difficulty));
    }
    ui->line->show();
    ui->line_2->show();
    ui->lcd_time->show();
    ui->frame->hide();
}

void MainWindow::hideLabels(){
    ui->line->hide();
    ui->line_2->hide();
    ui->lcd_time->hide();
    ui->label_difficulty->setText("");
    ui->label_size->setText("");
    ui->label_name->setText("");
    ui->frame->show();
}

void MainWindow::pauseGame(){
    isPainterOff = 1;
    timer->stop();
    update();
}

void MainWindow::startGame(){
    isPainterOff = 0;
    if (game->maze->array != NULL)
        timer->start(timeInterval);
    update();
}

void MainWindow::on_pushButton_new_clicked(){
    on_actionNew_triggered();
}

void MainWindow::on_pushButton_load_clicked(){
    on_actionOpen_triggered();
}

void MainWindow::on_pushButton_leader_clicked(){
    on_actionRankingi_triggered();
}

void MainWindow::on_pushButton_exit_clicked(){
    this->close();
}

void MainWindow::on_pushButton_easy_clicked(){
    on_actionEasy_triggered();
}

void MainWindow::on_pushButton_medium_clicked(){
    on_actionMedium_triggered();
}

void MainWindow::on_pushButton_hard_clicked(){
    on_actionHard_triggered();
}

void MainWindow::on_pushButton_expert_clicked(){
    on_actionExpert_triggered();
}
