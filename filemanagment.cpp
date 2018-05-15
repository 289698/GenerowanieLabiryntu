#include "filemanagment.h"

FileManagment::FileManagment(){
    dirSaves = new QDir;

    if (!dirSaves->cd("saves"))
    {
        dirSaves->mkdir("saves");
        dirSaves->cd("saves");
    }
}

FileManagment::~FileManagment(){
    delete dirSaves;
}
//------------------------------------------------
void FileManagment::finish(){
    win = new WinDialog;
    win->fillLineEdits(maze);

    if (!maze->isDefault || !isBetter())
        win->hideLeader();

    connect(win, SIGNAL(fileName(QString)), this, SLOT(saveAfterFinish(QString)));
    connect(win, SIGNAL(nick(QString)), this, SLOT(saveToLeader(QString)));
    connect(win, SIGNAL(testFileName(QString)), this, SLOT(testLeaderName(QString)));
    connect(win, SIGNAL(testNick(QString)), this, SLOT(testNick(QString)));

    win->exec();
    delete win;
}

bool FileManagment::isBetter(){
    if (maze->difficulty > 4)
        return 0;

    QFile file("LeaderBoard.txt");
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

bool FileManagment::testLeaderName(const QString &fileName){
    if(fileName.isEmpty()){
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

void FileManagment::saveToLeader(const QString &nick){
    if(testNick(nick) || !isBetter())
        return;

    QFile file("LeaderBoard.txt");
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
}

void FileManagment::saveAfterFinish(const QString &fileName){
    if (testLeaderName(fileName))
        return;
    maze->name = fileName;
    maze->currentPos.setX(0);
    maze->currentPos.setY(maze->start);
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
    QFile file("LeaderBoard.txt");
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
    QFile file("LeaderBoard.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream outStream(&file);
    for (int i=0; i<4; ++i)
        outStream << "10000000" << endl;
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

bool FileManagment::testLoadName(const QString &fileName){
    if(fileName.isEmpty()){
        dialog->highlightLine();
        return 1;
    }

    QFile file(dirSaves->filePath(fileName + ".txt"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        dialog->highlightLine();
        return 1;
    }
    file.flush();
    file.close();

    dialog->unhighlightLine();
    return 0;
}

void FileManagment::load(const QString &fileName){
    if (testLoadName(fileName))
        return;
    QFile file(dirSaves->filePath(fileName + ".txt"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    int height, width;
    QTextStream inStream(&file);
    inStream >> height >> width;
    emit loadSignal(height, width);

    inStream >> maze->difficulty >> maze->seconds >> maze->start >> maze->end >> maze->currentPos.rx() >> maze->currentPos.ry();
    maze->name = fileName;
    for (int i=0; i<maze->height; ++i)
        for (int j=0; j<maze->width; j++)
            inStream >> maze->array[i][j];

    file.flush();
    file.close();
    dialog->close();
}
//------------------------------------------------
void FileManagment::save(){
    QFile file(dirSaves->filePath(maze->name + ".txt"));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream outStream(&file);
    outStream << maze->height << " " << maze->width << " " << maze->difficulty << " " << maze->seconds << " "
        << maze->start << " " << maze->end << " " << maze->currentPos.x() << " " << maze->currentPos.y();
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

bool FileManagment::testSaveName(const QString &fileName){
    if(fileName.isEmpty())
    {
        dialog->highlightLine();
        return 1;
    }

//    QFile file(dirSaves->filePath(fileName + ".txt"));
//    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        dialog->unhighlightLine();
//        return;
//    }
//    file.flush();
//    file.close();

    dialog->unhighlightLine();
    return 0;
}

void FileManagment::save(const QString &fileName){
    if (fileName.isEmpty() || testSaveName(fileName))
        return;
    maze->name = fileName;
    save();
    dialog->close();
}
//------------------------------------------------
void FileManagment::deleteFile(const QString &fileName){
    QFile file(dirSaves->filePath(fileName + ".txt"));

    if (file.remove())
        dialog->clearLine();
    else
        dialog->highlightLine();
    file.flush();
    file.close();// czy po usunięciu dalej muszę spłukać i zamknąć?

    fillFilesList();
}

void FileManagment::fillFilesList(){
    dialog->clearTree();

    QStringList filesList = dirSaves->entryList(QDir::Files, QDir::Time);

    for (int i=0; i<filesList.size(); ++i){
        QFile file(dirSaves->filePath(filesList.at(i)));
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

//bool FileManagment::isFine(QString fileName) // dluuuuuuga funkcja sprawdzajaca wszystkie glupoty
//{
//    QFile file(dir->filePath(fileName + ".txt"));
//    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
//        return 0;

//    QTextStream inStream(&file);
//    QString input;
//    bool ok;
//    int minfo[8]; // 0-height, 1-width, 2-difficulty, 3-seconds, 4-start, 5-end, 6-currentPos_x, 7-currentPos_y;

//    for (int i=0; i<8; ++i)
//    {
//        inStream >> input;
//        minfo[i] = input.toInt(&ok, 10);
//        if (!ok)
//            return 0;
//    }

//    if (minfo[0] < 20 || minfo[0] > 100 || minfo[1] < 20 || minfo[1] > 100)
//        return 0;
//    if (minfo[2] < 1 || minfo[2] > 4)
//        return 0;
//    if (minfo[3] < 0)
//        return 0;
//    if (minfo[4] < 0 || minfo[4] >= minfo[0] || minfo[5] < 0 || minfo[5] >= minfo[0])
//        return 0;
//    if (minfo[6] < 0 || minfo[6] >= minfo[1] || minfo[7] < 0 || minfo[7] >= minfo[0])
//        return 0;

//    int counter = 0;
//    while (!inStream.atEnd())
//    {
//        inStream >> input;
//        input.toInt(&ok, 10);
//        if (!ok)
//            return 0;
//        counter++;
//    }

//    if (counter != minfo[0]*minfo[1])
//        return 0;

//    file.flush();
//    file.close();
//    return 1;
//}
