/*! \file generating.h
 * Klasa generująca losowy labirynt o danych właściwościach.
 */
#ifndef GENERATING_H
#define GENERATING_H

#include <ctime>
#include <cstdlib>
//! Struktura przechowująca informacje o ścianach w danej kratce labiryntu.
struct Borders{
    bool *N;
    bool *E;
    bool *S;
    bool *W;
};
struct Point{
    int row;
    int col;
};
//! Klasa generująca losowy labirynt o danych właściwościach.
class Generating{
public:
    //! Ustala wartości pól tej klasy, rezerwuje pamięć na tablice bordersArray i visitedArray oraz rozpoczyna losowanie.
    Generating(int **adress, int mazeHeight, int mazeWidth, int difficulty);
    //! Zwalnia pamięć bordersArray i visitedArray.
    ~Generating();
    //! \brief Generuje losowy labirynt.
    int generateMaze(int &startingRow, int &endingRow);

private:
    Borders **bordersArray; //!< Tablica przechowująca informacje o ścianach w labiryncie.
    bool **visitedArray; //!< Tablica przechowująca informacje o tym, czy dane pole zostało odwiedzone przez generator.
    int **mazeArray; //!< Tablica wynikowa, zostanie przekazana poza klasę.

    int mazeHeight,//!< Wysokość labiryntu.
    mazeWidth, //!< Szerokość labiryntu.
    minLength, //!< Minimalna odległość od początku labiryntu do końca.
    maxLength; //!< Maksymalna odległość od początku labiryntu do końca.
    /*! Szukając wierszami znajduje pierwszy nieodwiedzony punkt, mający odwiedzonego sąsiada.
     * Zwraca 1, gry punkt został znaleziony, 0 gdy nie istnieje taki punkt.
     */
    bool findNextPoint(Point &currentPos);
    //! Tworzy ścieżkę od początkowego punktu licząc jej długość.
    void makeStartingPath(Point &currentPos, int &counter, bool &a);
    //! Tworzy losową ścieżkę.
    void makeRandomPath(Point &currentPos, char direction);
    //! Losuje kierunek, w którym może się ruszyć generator. Zwraca N-góra, E-prawo, S-dół, W-lewo lub X-brak kierunków.
    char randomDirection(Point currentPos);
    //! Przepisuje tablicę typu Borders na tablicę int. (Pierwszą łatwiej edytować, druga zajmuje mniej pamięci).
    void rewriteArray();
    //! Na podstawie difficulty ustala wartości minLength i maxLength.
    void tempDiff(int difficulty);
    /*! \brief Rezerwuje pamięć na tablicę bordersArray.
     *
     * Rezerwuje pamięć w taki sposób, że [i][j].N == [i-1][j].S oraz [i][j].W == [i][j-1].E (kiedy to możliwe).
     * Dzięki temu dodanie/usunięcie ściany w komórce [i][j] spowoduje odpowiednią zmianę u sąsiedniej komórki.
     */
    void reserveBordersMemory ();
    //! Usuwa pamięć zarezerwowaną na tablicę bordersArray.
    void clearBordersMemory ();
    //! Rezerwuje pamięć na tablicę visitedArray.
    void reserveBoolMemory (int w, int k);
    //! Usuwa pamięć zarezerwowaną na tablicę visitedArray.
    void clearBoolMemory (int w);
    //! Resetuje stan ścian w bordersArray.
    void resetbordersArray();
    //! Resetuje stan komórek w visitedArray.
    void resetvisitedArray();
};

#endif // GENERATING_H
