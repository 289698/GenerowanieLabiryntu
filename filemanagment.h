#ifndef FILEMANAGMENT_H
#define FILEMANAGMENT_H

#include <QDir>
#include <QFile>
#include <QTextStream>
#include "filedialog.h"
#include "leaderdialog.h"
#include "windialog.h"
#include "maze.h"

#include <QDebug>

class FileManagment : public Maze
{
    Q_OBJECT
public:
    FileManagment();
    ~FileManagment();

    void load();
    void save();
    void saveAs();
    void openLeader();
    void finish();

signals:
    void loadSignal(int, int);

private slots:
    void save(const QString &fileName);
    bool testSaveName(const QString &fileName);
    void load(const QString &fileName);
    bool testLoadName(const QString &fileName);
    void deleteFile(const QString &fileName);
    void resetLeader();
    void saveToLeader(const QString &fileName, const QString &nick);
    bool testNick(const QString &nick);
    void saveAfterFinish(const QString &fileName);
    bool testLeaderName(const QString &fileName);

private:
    FileDialog *dialog;
    LeaderDialog *leader;
    WinDialog *win;
    QDir *dir_saves;

    void fillFilesList();
    void fillLeaderTable();
    bool isBetter();
    //    bool isFine(QString fileName);
};

#endif // FILEMANAGMENT_H
