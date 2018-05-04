#include "filemanagment.h"

FileManagment::FileManagment()
{
    dir = new QDir;

    if (!dir->cd("saves"))
    {
        dir->mkdir("saves");
        dir->cd("saves");
    }
}

FileManagment::~FileManagment()
{
    delete dir;
}

void FileManagment::load()
{
    dialog = new FileDialog;
    fillFilesList();
    dialog->hideSaveButton();

    connect(dialog, SIGNAL(fileNameSignal(QString)), this, SLOT(load(QString)));
    connect(dialog, SIGNAL(deleteFileSignal(QString)), this, SLOT(deleteFile(QString)));

    dialog->exec();
    delete dialog;
}

void FileManagment::load(QString fileName)
{
    QFile file(dir->filePath(fileName + ".txt"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    int height, width;
    QTextStream inStream(&file);
    inStream >> height >> width;
    emit loadSignal(height, width);

    inStream >> maze->difficulty >> maze->seconds >> maze->start >> maze->end >> maze->currentPos.rx() >> maze->currentPos.ry();
    maze->name = fileName;
    for (int i=0; i<maze->height; i++)
        for (int j=0; j<maze->width; j++)
            inStream >> maze->array[i][j];

    file.flush();
    file.close();
}

void FileManagment::deleteFile(QString fileName)
{
    QFile file(dir->filePath(fileName + ".txt"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    file.remove(); // czy po usunięciu dalej muszę spłukać i zamknąć?

    fillFilesList();

    file.flush();
    file.close();

}

void FileManagment::save()
{
    QFile file(dir->filePath(maze->name + ".txt"));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream outStream(&file);
    outStream << maze->height << " " << maze->width << " " << maze->difficulty << " " << maze->seconds << " "
        << maze->start << " " << maze->end << " " << maze->currentPos.x() << " " << maze->currentPos.y();
    for (int i=0; i<maze->height; i++)
        for (int j=0; j<maze->width; j++)
            outStream << " " << maze->array[i][j];

    file.flush();
    file.close();
}

void FileManagment::saveAs()
{
    dialog = new FileDialog;
    fillFilesList();
    dialog->hideOpenButton();

    connect(dialog, SIGNAL(fileNameSignal(QString)), this, SLOT(save(QString)));

    dialog->exec();
    delete dialog;
}

void FileManagment::save(QString fileName)
{
    maze->name = fileName;
    save();
}

void FileManagment::fillFilesList()
{
    dialog->clearTree();

    QStringList filesList = dir->entryList(QDir::Files, QDir::Time);

    for (int i=0; i<filesList.size(); i++)
    {
        QFile file(dir->filePath(filesList.at(i)));
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QString name = filesList.at(i), difficulty;
        int height, width, diffNumber, seconds;

        QTextStream in(&file);
        in >> height >> width >> diffNumber >> seconds;

        file.flush();
        file.close();

        name.replace(".txt", "");

        switch (diffNumber)
        {
        case 1: difficulty = "Łatwa"; break;
        case 2: difficulty = "Średnia"; break;
        case 3: difficulty = "Trudna"; break;
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

//    for (int i=0; i<8; i++)
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
