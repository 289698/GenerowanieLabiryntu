/*! \file filemanagment.h
 * Klasa zapisująca, wczytująca i usuwająca labirynty.
 * Dodatkowo włącza odpowiednie okienka do zapisu, wczytywania, rankingów i zapisania po wygranej
 */
#ifndef FILEMANAGMENT_H
#define FILEMANAGMENT_H

#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include "filedialog.h"
#include "leaderdialog.h"
#include "windialog.h"
#include "maze.h"

//!Klasa zapisująca, wczytująca i usuwająca labirynty. Dodatkowo włącza odpowiednie okienka do zapisu, wczytywania, rankingów i zapisania po wygranej
class FileManagment : public Maze
{
    Q_OBJECT
public:
    //! Sprawdza, czy folder saves istnieje, jeśli nie tworzy go.
    FileManagment();
    ~FileManagment();
    /*! \brief Tworzy okienko FileDialog do wczytywania labiryntów.
     *
     * Włącza okienko FileDialog, zmienia nazwę przycisku "Accept" na "Wczytaj",
     * nazwę okna na "Wczytaj z pliku..." i tworzy trzy connect'y:
     * 1) kiedy zostanie zmieniony tekst w polu wpisywania, sprawdza, czy jest prawidłowy
     * 2) po wciśnięciu "Wczytaj" wczytuje labirynt
     * 3) po wciśnięciu "Usuń" usuwa labirynt.
     */
    void load();
    //! Zapisuje do pliku o nazwie zapisanej w MazeStruct.
    void save();
    /*! \brief Tworzy okienko do zapisywania plików.
     *
     * Włącza okienko FileDialog, zmienia nazwę przycisku "Accept" na "Zapisz",
     * nazwę okna na "Zapisz jako..." i tworzy trzy connect'y:
     * 1) kiedy zostanie zmieniony tekst w polu wpisywania, sprawdza, czy jest prawidłowy
     * 2) po wciśnięciu "Zapisz" zapisuje labirynt
     * 3) po wciśnięciu "Usuń" usuwa labirynt.
     */
    void saveAs();
    //! Tworzy okienko LeaderDialog i tworzy connect resetujący ranking.
    void openLeader();
    /*! \brief Tworzy okienko do zapisania labiryntu po zakończeniu gry.
     *
     * Włącza okienko WinDialog i tworzy cztery connect'y:
     * 1) zapisuje labirynt ze zresetowaną pozycją gracza i czasem
     * 2) zapisuje labirynt ze zresetowaną pozycją gracza i czasem oraz zapisuje nick do rankingu
     * 3) kiedy zostanie zmieniony tekst w polu wpisywania nazwy labiryntu, sprawdza, czy jest prawidłowy
     * 4) kiedy zostanie zmieniony tekst w polu wpisywania nicku, sprawdza, czy jest prawidłowy.
     */
    void finish();

signals:
    //! Wysyła rozmiar labiryntu do instancji klasy MazeManagment.
    //! \see void MazeManagment::loadSlot(int height, int width)
    void loadSignal(int, int);

private slots:
    //! Zmienia nazwę labiryntu w MazeStruct i zapisuje go, po wciśnięciu "Zapisz".
    void save(const QString &file_name);
    //! Sprawdza, czy tekst w polu wpisywania jest prawidłowy, po zmianie tekstu w polu wpisywania lub po wciśnięciu "Zapisz" \see void FileDialog::testFileName(QString);
    bool testSaveName(const QString &file_name);
    /*! \brief Wczytuje labirynt z pliku
     *
     * Sprawdza, czy nazwa i plik są prawidłowe, jeśli tak to wczytuje do struktury MazeStruct
     * utworzonej przez instancję MazeManagment (za pomocą emit loadSignal(height, width))
     * i zamyka okno.
     * \see void MazeManagment::load()
     */
    void load(const QString &file_name);
    //! Sprawdza, czy tekst w polu wpisywania jest prawidłowy, po zmianie tekstu w polu wpisywania lub po wciśnięciu "Wczytaj". \see void FileDialog::testFileName(QString);
    bool testLoadName(const QString &file_name);
    //! Usuwa labirynt, po wciśnięciu "Usuń".
    void deleteFile(const QString &file_name);
    //! Resetuje plik z rankingami.
    void resetLeader();
    //! Zapisuje nowy rekord do pliku z rankingami, a następnie zapisuje labirynt ze zresetowaną pozycją i czasem.
    void saveToLeader(const QString &file_name, const QString &nick);
    //! Sprawdza, czy nick jest prawidłowy.
    bool testNick(const QString &nick);
    //! Zapisuje labirynt ze zresetowaną pozycją i czasem.
    void saveAfterFinish(const QString &file_name);
    //! Sprawdza, czy nazwa w polu wpisywania jest prawidłowa.
    bool testLeaderName(const QString &file_name);

private:
    FileDialog *dialog;
    LeaderDialog *leader;
    WinDialog *win;
    QDir *dir_saves;

    //! Wypełnia okno FileDialog informacjami o plikach.
    void fillFilesList();
    //! Wypełnia okno LeaderDialog informacjami o rankingu.
    void fillLeaderTable();
    //! Sprawdza, czy nowy czas przejścia labiryntu jest lepszy od poprzedniego.
    bool isBetter();
    //! Sprawdza, czy plik zawiera poprawne dane.
    bool isFine(const QString &file_name);
    //! Wyświetla informację o uszkodzeniu pliku, z którego próbujemy wczytać labirynt.
    bool displayError(int error_num);
};

#endif // FILEMANAGMENT_H
