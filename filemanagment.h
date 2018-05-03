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

private slots:
    void saveSlot(QString fileName);
    void loadSlot(QString fileName);

private:
    FileDialog *dialog;
    QDir *dir;

    void fillFilesList();
};

#endif // FILEMANAGMENT_H
