#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game = new MazeManagment;

    hideLabels();
    this->setFixedSize(kWindowWidth, kWindowHeight);
    ui->pushButton_minus->setFixedSize(20, 20);
    ui->pushButton_plus->setFixedSize(20, 20);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(measureTime()));
}

MainWindow::~MainWindow(){
    delete timer;
    delete game;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if (game->maze->array == NULL)
        return;

    switch (event->key()){
    case Qt::Key_W:
    case Qt::Key_Up:
        if(isMovePossible(1))
            game->maze->current_pos.ry()--;
    break;
    case Qt::Key_A:
    case Qt::Key_Left:
        if(isMovePossible(8))
            game->maze->current_pos.rx()--;
    break;
    case Qt::Key_S:
    case Qt::Key_Down:
        if(isMovePossible(4))
            game->maze->current_pos.ry()++;
    break;
    case Qt::Key_D:
    case Qt::Key_Right:
        if(isMovePossible(2))
            game->maze->current_pos.rx()++;
    break;
    case Qt::Key_P:
        game->maze->current_pos.setX(game->maze->width-1);
        game->maze->current_pos.setY(game->maze->end);
    break;
    }
    if (game->maze->current_pos.x() == game->maze->width)
        finish();
    update();
}

void MainWindow::finish(){
    timer->stop();
    game->finish();
    this->setFixedSize(kWindowWidth, kWindowHeight);
    hideLabels();
}

void MainWindow::paintEvent(QPaintEvent *){
    if (game->maze->array == NULL || is_painter_off)
        return;

    QPainter painter(this);
    if(blackout_size == 0){
        for (int i=0; i<game->maze->height; ++i)
            for (int j=0; j<game->maze->width; j++)
                drawSquare(&painter, grid(j, i), game->maze->array[i][j]);
    }
    else{
        for (int i=0; i<game->maze->height; ++i)
            for (int j=0; j<game->maze->width; j++)
                if (abs(i - game->maze->current_pos.y()) < blackout_size &&
                        abs(j - game->maze->current_pos.x()) < blackout_size)
                    drawSquare(&painter, grid(j, i), game->maze->array[i][j]);
    }

    painter.setBrush(Qt::black);
    painter.drawEllipse(grid(game->maze->current_pos), int(maze_size/2), int(maze_size/2));

}

void MainWindow::drawSquare(QPainter *painter, QPoint point, int borders){
    if (borders & 1)
        painter->drawLine(point.x() - maze_size, point.y() - maze_size,
                          point.x() + maze_size, point.y() - maze_size);
    if (borders & 2)
        painter->drawLine(point.x() + maze_size, point.y() - maze_size,
                          point.x() + maze_size, point.y() + maze_size);
    if (borders & 4)
        painter->drawLine(point.x() + maze_size, point.y() + maze_size,
                          point.x() - maze_size, point.y() + maze_size);
    if (borders & 8)
        painter->drawLine(point.x() - maze_size, point.y() + maze_size,
                          point.x() - maze_size, point.y() - maze_size);
}

QPoint MainWindow::grid(int x, int y){
    QPoint point;
    point.setX(x * maze_size*2 + margin_left);
    point.setY(y * maze_size*2 + margin_top);
    return point;
}

QPoint MainWindow::grid(QPoint point){
    point.setX(point.x() * maze_size*2 + margin_left);
    point.setY(point.y() * maze_size*2 + margin_top);
    return point;
}

void MainWindow::prepareMaze(int height, int width, int difficulty, bool is_default){
    game->create(height, width, difficulty);
    game->maze->isDefault = is_default;
    fillLabels();
    resizeWindow();
    timer->start(kTimeInterval);
    update();
}

void MainWindow::measureTime(){
    game->maze->seconds += kTimeInterval;
    ui->lcd_time->display(game->maze->seconds/1000.0);
}

void MainWindow::fillLabels(){
    ui->label_name->setText(game->maze->name);
    ui->label_size->setText(QString::number(game->maze->height) + " x " + QString::number(game->maze->width));
    switch (game->maze->difficulty){
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
    ui->gameWidget->show();
    ui->infoWidget->show();
    ui->welcomeWidget->hide();
}

void MainWindow::hideLabels(){
    ui->gameWidget->hide();
    ui->infoWidget->hide();
    ui->welcomeWidget->show();
}

void MainWindow::pauseGame(){
    is_painter_off = 1;
    timer->stop();
    update();
}

void MainWindow::startGame(){
    is_painter_off = 0;
    if (game->maze->array != NULL)
        timer->start(kTimeInterval);
    update();
}

void MainWindow::on_pushButton_minus_clicked(){
    if(maze_size > 4)
        --maze_size;
    resizeWindow();
    update();
}

void MainWindow::on_pushButton_plus_clicked(){
    if(maze_size < 15)
        ++maze_size;
    resizeWindow();
    update();
}

void MainWindow::on_action_leader_triggered(){
    pauseGame();
    game->openLeader();
    startGame();
}

void MainWindow::on_action_new_triggered(){
    pauseGame();
    setting = new SettingsDialog;
    connect(setting, SIGNAL(mainSettings(int,int,int)), this, SLOT(prepareMaze(int,int,int)));
    setting->setModal(0);
    setting->exec();
    delete setting;
    startGame();
}

void MainWindow::on_action_load_triggered(){
    pauseGame();
    game->load();
    if (game->maze->array != NULL){
        fillLabels();
        resizeWindow();
    }
    startGame();
}

void MainWindow::on_action_save_triggered(){
    pauseGame();
    if (game->maze->array != NULL)
        game->save();
    startGame();
}

void MainWindow::on_action_saveAs_triggered(){
    pauseGame();
    if (game->maze->array != NULL)
        game->saveAs();
    startGame();
}

void MainWindow::on_action_close_triggered(){
    timer->stop();
    hideLabels();
    game->deleteMaze();
    update();
    this->setFixedSize(kWindowWidth, kWindowHeight);
}

void MainWindow::on_action_blackout_toggled(bool arg1){
    blackout_size = 4 * arg1;
    update();
}

void MainWindow::on_action_help_triggered(){
    QMessageBox *help = new QMessageBox();
    help->setText("STEROWANIE:\n\n"
                  "Strzałka w górę lub W- porusz się do góry\n"
                  "Strzałka w lewo lub A- porusz się w lewo\n"
                  "Strzałka w dół lub S- porusz się w dół\n"
                  "Strzałka w prawo lub D- porusz się w prawo\n"
                  "P- przenieś się przed wyjście z labiryntu\n\n"
                  "CEL GRY:\n\n"
                  "Znaleźć drogę do wyjścia- przerwy w ścianie po "
                  "prawej stronie- w jak najkrótszym czasie. Najlepsze "
                  "wyniki z szybkich gier mogą być zapisane w rankingu");
    help->exec();
    delete help;
}

void MainWindow::on_pushButton_help_clicked(){
    on_action_help_triggered();
}
