#ifndef FILEMANAGMENT_H
#define FILEMANAGMENT_H

#include <QDir>
#include <QFile>
#include <QTextStream>
#include "filedialog.h"
#include "maze.h"

class FileManagment : public Maze
{
    Q_OBJECT
public:
    FileManagment();
    ~FileManagment();

    void load();
    void save();
    void saveAs();

signals:
    void loadSignal(int, int);

private slots:
    void save(QString fileName);
    void load(QString fileName);
    void deleteFile(QString fileName);

private:
    FileDialog *dialog;
    QDir *dir;

    void fillFilesList();
//    bool isFine(QString fileName);
};

#endif // FILEMANAGMENT_H
