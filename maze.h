/*! \file maze.h
 * Klasa abstrakcyjna, po której dziedziczą klasy MazeManagment i FileManagment.
 */
#ifndef MAZE_H
#define MAZE_H

#include <QObject>
#include <QPoint>
#include <QString>
//! Struktura przechowująca informacje o labiryncie.
struct MazeStruct{
    //! Wymiary labiryntu.
    int height, width;
    //! Początkowe położenie i wyjście labiryntu (tylko współrzędna Y,
    //! bo początek i wyjście są zawsze na odpowiednio lewej i prawej ścianie.
    int start, end;
    //! Trudność labiryntu, 1-Łatwy, 2-Średni, 3-Trudny, 4-Ekspert.
    int difficulty;
    //! Czas przechodzenia labiryntu w ms.
    int seconds;
    //! Tablica labiryntu.
    int **array;
    //! Obecna pozycja gracza.
    QPoint current_pos;
    //! Nazwa labiryntu.
    QString name;
    //! true- labirynt był stworzony z domyślnych ustawień.
    //! false- był stworzony za pomocą okienka SettingsDialog.
    bool isDefault;
};
//! Klasa abstrakcyjna, po której dziedziczą klasy MazeManagment i FileManagment.
class Maze : public QObject{
    Q_OBJECT
public:
    explicit Maze(QObject *parent = 0);

    MazeStruct *maze;

private:

};

#endif // MAZE_H
