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

    connect(dialog, SIGNAL(fileNameSignal(QString)), this, SLOT(loadSlot(QString)));

    dialog->exec();
    delete dialog;
}

void FileManagment::loadSlot(QString fileName)
{
    maze->name = fileName;

    QFile file(dir->filePath(maze->name + ".txt"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    in >> maze->height >> maze->width >> maze->difficulty >> maze->seconds
            >> maze->start >> maze->end >> maze->currentPos.rx() >> maze->currentPos.ry();

    /*   TEN FRAGMENT MI SIĘ NIE PODOBA   */

    maze->array = new int *[maze->height];
    for (int i=0; i<maze->height; i++)
        maze->array[i] = new int [maze->width];

    /*  BO TO POWINIEN ROBIC INNY OBIEKT  */

    for (int i=0; i<maze->height; i++)
        for (int j=0; j<maze->width; j++)
            in >> maze->array[i][j];

    file.flush();
    file.close();
}

void FileManagment::save()
{
    QFile file(dir->filePath(maze->name + ".txt"));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << maze->height << " " << maze->width << " " << maze->difficulty << " " << maze->seconds << " "
        << maze->start << " " << maze->end << " " << maze->currentPos.x() << " " << maze->currentPos.y();
    for (int i=0; i<maze->height; i++)
        for (int j=0; j<maze->width; j++)
            out << " " << maze->array[i][j];

    file.flush();
    file.close();
}

void FileManagment::saveAs()
{
    dialog = new FileDialog;
    fillFilesList();

    connect(dialog, SIGNAL(fileNameSignal(QString)), this, SLOT(saveSlot(QString)));

    dialog->exec();
    delete dialog;
}

void FileManagment::saveSlot(QString fileName)
{
    maze->name = fileName;
    save();
}

void FileManagment::fillFilesList()
{
    QStringList filesList = dir->entryList(QDir::Files, QDir::Time);

    for (int i=0; i<filesList.size(); i++)
    {
        QFile file(dir->filePath(filesList.at(i)));
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        int diffNumber;
        QString name = filesList.at(i), height, width, difficulty, seconds;

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
        fileInfo << name << height + " x " + width << difficulty << seconds;
        dialog->addFileInfo(fileInfo);
    }
}
