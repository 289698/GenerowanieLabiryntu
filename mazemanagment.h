/*! \file mazemanagment.h
 * Klasa zawierająca funkcje modyfikujące labirynt (rezerwowanie pamięci, usuwanie, generowanie labiryntu, wczytuwanie, zapisywanie...).
 */
#ifndef MAZEMANAGMENT_H
#define MAZEMANAGMENT_H

#include "generating.h"
#include "filemanagment.h"
#include "maze.h"
//! Klasa zawierająca funkcje modyfikujące labirynt (rezerwowanie pamięci, usuwanie, generowanie labiryntu, wczytuwanie, zapisywanie...).
class MazeManagment : public Maze
{
    Q_OBJECT
public:
    MazeManagment();
    ~MazeManagment();
    //! Tworzy nowy labirynt o zadanych właściwościach oraz zapisuje je w MaseStruct.
    void create(int height, int width, int difficulty);
    //! Wczytuje labirynt.
    void load();
    //! Zapisuje labirynt z nazwą zapisaną w MazeStruct, jeśli jej nie ma użytkownik ją podaje.
    void save();
    //! Zapisuje labirynt z nazwą wybraną przez użytkownika.
    void saveAs();
    //! Wyświetla okno z rankingami.
    void openLeader();
    //! Usuwa labirynt.
    void deleteMaze();
    //! \see void FileManagment::finish()
    void finish();

private slots:
    //! Rezerwuje pamięć na tablicę o wymiarach height x width.
    void loadSlot(int height, int width);

private:
    Generating* maze_gen;
    FileManagment* file;
    //! Generuje losowy labirynt.
    void generate();
    //! Rezerwuje pamięć na tablicę o wymiarach zapisanych w MazeStruct.
    void newMaze();
    //! Resetuje pola MazeStruct.
    void reset();
};

#endif // GAME_H
