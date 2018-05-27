#include "filemanagment.h"

FileManagment::FileManagment(){
    dir_saves = new QDir;

    if (!dir_saves->cd("saves")){
        dir_saves->mkdir("saves");
        dir_saves->cd("saves");
    }
}

FileManagment::~FileManagment(){
    delete dir_saves;
}
//------------------------------------------------
void FileManagment::finish(){
    win = new WinDialog;
    win->fillLineEdits(maze);
    if (!maze->isDefault || !isBetter())
        win->hideLeader();

    connect(win, SIGNAL(fileName(QString)), this, SLOT(saveAfterFinish(QString)));
    connect(win, SIGNAL(nameAndNick(QString, QString)), this, SLOT(saveToLeader(QString, QString)));
    connect(win, SIGNAL(testFileName(QString)), this, SLOT(testLeaderName(QString)));
    connect(win, SIGNAL(testNick(QString)), this, SLOT(testNick(QString)));

    win->exec();
    delete win;
}

bool FileManagment::isBetter(){
    if (maze->difficulty > 4)
        return 0;
    QFile file(dir_saves->filePath("LeaderBoard.txt"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;
    QTextStream inStream(&file);
    QString oldSecs;
    for (int i=0; i<maze->difficulty; ++i)
        oldSecs = inStream.readLine();
    file.flush();
    file.close();
    if (oldSecs.toInt() < maze->seconds)
        return 0;
    return 1;
}

bool FileManagment::testLeaderName(const QString &file_name){
    if(file_name.isEmpty()){
        win->highlightName();
        return 1;
    }
    win->unhighlightName();
    return 0;
}

bool FileManagment::testNick(const QString &nick){
    if(nick.isEmpty()){
        win->highlightNick();
        return 1;
    }
    win->unhighlightNick();
    return 0;
}

void FileManagment::saveToLeader(const QString &file_name, const QString &nick){
    if(testNick(nick) || testLeaderName(file_name))
        return;

    QFile file(dir_saves->filePath("LeaderBoard.txt"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        resetLeader();
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
    }

    QTextStream stream(&file);
    QString leaderInfo[8];
    for (int i=0; i<8; ++i)
        leaderInfo[i] = stream.readLine();

    file.flush();
    file.close();

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        resetLeader();
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    }

    leaderInfo[maze->difficulty - 1] = QString::number(maze->seconds);
    leaderInfo[maze->difficulty + 3] = nick;

    for (int i=0; i<8; ++i)
        stream << leaderInfo[i] << endl;

    file.flush();
    file.close();
    saveAfterFinish(file_name);
}

void FileManagment::saveAfterFinish(const QString &file_name){
    if (testLeaderName(file_name))
        return;
    maze->name = file_name;
    maze->current_pos.setX(0);
    maze->current_pos.setY(maze->start);
    maze->seconds = 0;
    save();
    win->close();
}
//------------------------------------------------
void FileManagment::openLeader(){
    leader = new LeaderDialog;
    fillLeaderTable();
    connect(leader, SIGNAL(resetLeader()), this, SLOT(resetLeader()));
    leader->exec();
    delete leader;
}

void FileManagment::fillLeaderTable(){
    QFile file(dir_saves->filePath("LeaderBoard.txt"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream inStream(&file);
    QStringList leaderInfo;
    for (int i=0; i<4; ++i){
        double temp = inStream.readLine().toDouble() / 1000;
        leaderInfo << QString::number(temp);
    }
    for (int i=0; i<4; ++i){
        QString temp = inStream.readLine();
        leaderInfo << temp;
    }

    file.flush();
    file.close();

    leader->setLabels(leaderInfo);
}

void FileManagment::resetLeader(){
    QFile file(dir_saves->filePath("LeaderBoard.txt"));
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream outStream(&file);
    for (int i=0; i<4; ++i)
        outStream << "100000000" << endl;
    for (int i=0; i<4; ++i)
        outStream << "----" << endl;

    file.flush();
    file.close();

    fillLeaderTable();
}
//------------------------------------------------
void FileManagment::load()
{
    dialog = new FileDialog;
    fillFilesList();
    dialog->setWindowTitle("Wczytaj z pliku...");
    dialog->changeButtonText("Wczytaj");

    connect(dialog, SIGNAL(testFileName(QString)), this, SLOT(testLoadName(QString)));
    connect(dialog, SIGNAL(fileName(QString)), this, SLOT(load(QString)));
    connect(dialog, SIGNAL(deleteFile(QString)), this, SLOT(deleteFile(QString)));

    dialog->exec();
    delete dialog;
}

bool FileManagment::testLoadName(const QString &file_name){
    if(file_name.isEmpty()){
        dialog->highlightLine();
        return 1;
    }
    QFile file(dir_saves->filePath(file_name + ".txt"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        dialog->highlightLine();
        return 1;
    }
    file.flush();
    file.close();

    dialog->unhighlightLine();
    return 0;
}

void FileManagment::load(const QString &file_name){
    if (testLoadName(file_name))
        return;
    if (!isFine(file_name))
        return;
    QFile file(dir_saves->filePath(file_name + ".txt"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    int height, width;
    QTextStream inStream(&file);
    inStream >> height >> width;
    emit loadSignal(height, width);

    inStream >> maze->difficulty >> maze->seconds >> maze->start >> maze->end >> maze->current_pos.rx() >> maze->current_pos.ry();
    maze->name = file_name;
    for (int i=0; i<maze->height; ++i)
        for (int j=0; j<maze->width; j++)
            inStream >> maze->array[i][j];

    file.flush();
    file.close();
    dialog->close();
}
//------------------------------------------------
void FileManagment::save(){
    QFile file(dir_saves->filePath(maze->name + ".txt"));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream outStream(&file);
    outStream << maze->height << " " << maze->width << " " << maze->difficulty << " " << maze->seconds << " "
              << maze->start << " " << maze->end << " " << maze->current_pos.x() << " " << maze->current_pos.y();
    for (int i=0; i<maze->height; ++i)
        for (int j=0; j<maze->width; j++)
            outStream << " " << maze->array[i][j];

    file.flush();
    file.close();
}

void FileManagment::saveAs(){
    dialog = new FileDialog;
    fillFilesList();
    dialog->setWindowTitle("Zapisz jako...");
    dialog->changeButtonText("Zapisz");

    connect(dialog, SIGNAL(testFileName(QString)), this, SLOT(testSaveName(QString)));
    connect(dialog, SIGNAL(fileName(QString)), this, SLOT(save(QString)));
    connect(dialog, SIGNAL(deleteFile(QString)), this, SLOT(deleteFile(QString)));

    dialog->exec();
    delete dialog;
}

bool FileManagment::testSaveName(const QString &file_name){
    if(file_name.isEmpty()){
        dialog->highlightLine();
        return 1;
    }
    dialog->unhighlightLine();
    return 0;
}

void FileManagment::save(const QString &file_name){
    if (testSaveName(file_name))
        return;
    maze->name = file_name;
    save();
    dialog->close();
}
//------------------------------------------------
void FileManagment::deleteFile(const QString &file_name){
    QFile file(dir_saves->filePath(file_name + ".txt"));

    if (file.remove())
        dialog->clearLine();
    else
        dialog->highlightLine();
    file.flush();
    file.close();
    fillFilesList();
}

void FileManagment::fillFilesList(){
    dialog->clearTree();
    QStringList filesList = dir_saves->entryList(QDir::Files, QDir::Time);
    filesList.removeOne("LeaderBoard.txt");
    for (int i=0; i<filesList.size(); ++i){
        QFile file(dir_saves->filePath(filesList.at(i)));
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QString name = filesList.at(i), difficulty;
        int height, width, diffNumber, seconds;

        QTextStream in(&file);
        in >> height >> width >> diffNumber >> seconds;

        file.flush();
        file.close();
        name.replace(".txt", "");

        switch (diffNumber){
        case 1: difficulty = "Niski"; break;
        case 2: difficulty = "Średni"; break;
        case 3: difficulty = "Wysoki"; break;
        case 4: difficulty = "Ekspert"; break;
        default: difficulty = QString::number(diffNumber);
        }

        QStringList fileInfo;
        fileInfo << name << QString::number(height) + " x " + QString::number(width) << difficulty << QString::number(seconds/1000.0);
        dialog->addFileInfo(fileInfo);
    }
}
//------------------------------------------------
bool FileManagment::isFine(const QString &file_name){
    QFile file(dir_saves->filePath(file_name + ".txt"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return displayError(1);
    QTextStream inStream(&file);
    QString input;
    bool ok;
    int maze_info[8]; // 0-height, 1-width, 2-difficulty, 3-seconds, 4-start, 5-end, 6-current_pos_x, 7-current_pos_y;

    for (int i=0; i<8; ++i){
        inStream >> input;
        maze_info[i] = input.toInt(&ok, 10);
        if (!ok)
            return displayError(2);
    }
    if (maze_info[0] < 20 || maze_info[0] > 100 || maze_info[0] % 5 != 0 ||
            maze_info[1] < 20 || maze_info[1] > 100 || maze_info[1] % 5 != 0)
        return displayError(3);
    if (maze_info[2] < 1 || maze_info[2] > 4)
        return displayError(4);
    if (maze_info[3] < 0)
        return displayError(5);
    if (maze_info[4] < 0 || maze_info[4] >= maze_info[0] || maze_info[5] < 0 || maze_info[5] >= maze_info[0])
        return displayError(6);
    if (maze_info[6] < 0 || maze_info[6] >= maze_info[1] || maze_info[7] < 0 || maze_info[7] >= maze_info[0])
        return displayError(7);

    int counter = 0;
    while (!inStream.atEnd()){
        inStream >> input;
        int array_value = input.toInt(&ok, 10);
        if (!ok || array_value < 0 || array_value > 14)
            return displayError(8 + array_value*100);
        counter++;
    }
    if (counter != maze_info[0]*maze_info[1])
        return displayError(9);

    file.flush();
    file.close();
    return 1;
}

bool FileManagment::displayError(int error_num){
    QMessageBox *pop_up = new QMessageBox;
    pop_up->setText("Plik nie istnieje, jest uszkodzony lub zawiera niepoprawne dane.\nZalecane usunięcie.\n\n"
                    "Kod błędu: "
                    + QString::number(error_num));
    pop_up->exec();
    return 0;
}
