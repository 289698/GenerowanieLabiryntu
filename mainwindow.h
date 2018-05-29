/*! \file mainwindow.h
 * Klasa głównego okienka, wyświetlającego opcje labiryntu i umożliwiająca granie.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>
#include <cmath>
#include "mazemanagment.h"
#include "settingsdialog.h"

namespace Ui {
class MainWindow;
}
//! Klasa głównego okienka, wyświetlającego opcje labiryntu i umożliwiająca granie.
class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //! Tworzy łatwy labirynt 20x20.
    void on_action_easy_triggered(){
        prepareMaze(20, 20, 1, 1);
    }
    //! Tworzy średni labirynt 30x30.
    void on_action_medium_triggered(){
        prepareMaze(30, 30, 2, 1);
    }
    //! Tworzy trudny labirynt 40x40.
    void on_action_hard_triggered(){
        prepareMaze(40, 40, 3, 1);
    }
    //! Tworzy bardzo trudny labirynt 50x50.
    void on_action_expert_triggered(){
        prepareMaze(50, 50, 4, 1);
    }
    //! Zatrzymuje grę na czas otwarcia okna z rankingami.
    void on_action_leader_triggered();
    //! Otwiera okno umożliwiające utworzenie własnego labiryntu.
    void on_action_new_triggered();
    //! Umożliwia wczytanie labiryntu, otwierając odpowiednie okno.
    void on_action_load_triggered();
    //! Umożliwia zapisanie labiryntu, używając nazwy zapisanej w MazeStruct lub otwierając odpowiednie okno jeśli potrzeba.
    void on_action_save_triggered();
    //! Umożliwia zapisanie labiryntu, otwierając odpowiednie okno.
    void on_action_saveAs_triggered();
    //! Usuwa labirynt i wraca do początkowych ustawień okna.
    void on_action_close_triggered();
    //! Wyświetla okno z pomocą.
    void on_action_help_triggered();
    //! Tworzy łatwy labirynt 20x20.
    void on_pushButton_easy_clicked(){
        on_action_easy_triggered();
    }
    //! Tworzy średni labirynt 30x30.
    void on_pushButton_medium_clicked(){
        on_action_medium_triggered();
    }
    //! Tworzy trudny labirynt 40x40.
    void on_pushButton_hard_clicked(){
        on_action_hard_triggered();
    }
    //! Tworzy bardzo trudny labirynt 50x50.
    void on_pushButton_expert_clicked(){
        on_action_expert_triggered();
    }
    //! Zatrzymuje grę na czas otwarcia okna z rankingami.
    void on_pushButton_leader_clicked(){
        on_action_leader_triggered();
    }
    //! Otwiera okno umożliwiające utworzenie własnego labiryntu.
    void on_pushButton_new_clicked(){
        on_action_new_triggered();
    }
    //! Umożliwia wczytanie labiryntu, otwierając odpowiednie okno.
    void on_pushButton_load_clicked(){
        on_action_load_triggered();
    }
    //! Zamyka program.
    void on_pushButton_exit_clicked(){
        this->close();
    }
    //! Wyświetla okno z pomocą.
    void on_pushButton_help_clicked();
    //! Zmniejsza rozmiar okna i labiryntu.
    void on_pushButton_minus_clicked();
    //! Zwiększa rozmiar okna i labiryntu.
    void on_pushButton_plus_clicked();
    //! Mierzy czas przechodzenia labiryntu.
    void measureTime();
    /*! \brief Rozpoczyna grę.
     *
     * Tworzy labirynt, ustawia odpowiednią wartość MazeStruct::isDefault, zmienia informacje o labiryncie wyświetlane na dole, zmienia rozmiar okna,
     * chowa i wyświetla odpowiednie widgety,
     * \see void MazeManagment::create(int height, int width, int difficulty)
     * \see fillLabels()
     * \see
     */
    void prepareMaze(int height, int width, int difficulty, bool is_default = 0);
    //! Przełącza funkcję ograniczania widoku w labiryncie
    void on_action_blackout_toggled(bool arg1);

private:
    Ui::MainWindow *ui;
    MazeManagment *game; //!< Wskażnik na klasę obsługującą labirynt
    SettingsDialog *setting; //!< Wskaźnik na klasę okna zawierającego opcje nowego labiryntu
    QTimer *timer = NULL; //!< Wskaźnik na QTimer mierzący czas przechodzenia

    const int kTimeInterval = 100, //!< Czas po jakim aktualizowany jest czas przechodzenia
    kWindowWidth = 300, kWindowHeight = 320;
    int margin_top = 75, margin_bottom = 45, margin_left = 20; //!< Marginesy pozwalające pozycjonować labirynt
    int maze_size = 8; //!< Rozmiar pojedyńczego kwadracika
    bool is_painter_off = 0; //!< 0- labirynt jest rysowany; 1- nie jest rysowany
    int blackout_size = 4; //!< 0- nie ograniczony widok; n- widok ograniczony do n kratek w każdą stronę
    //! Zmienia rozmiar okna w zależności od wielkości labiryntu
    void resizeWindow(){
        this->setFixedSize((game->maze->width-1) * maze_size*2 + margin_left*2,
                           (game->maze->height-1) * maze_size*2 + margin_top + margin_bottom);
    }
    //! Funkcja kończąca grę. Zatrzymuje odliczanie, umożliwia zapisanie labiryntu i rekordu oraz usuwa labirynt. Resetuje okno do podstawowych ustawień.
    void finish();
    //! Zmienia tekst na dole okna na "nazwa labiryntu" "Wysokość" x "Szerokość" "Trudność".
    void fillLabels();
    //! Chowa napis na dole okna
    void hideLabels();
    //! Włącza odliczanie czasu gry i rysowanie (jeśli gra jest włączona) oraz aktualizuje okno.
    void startGame();
    //! Wyłącza odliczanie czasu gry i rysowanie oraz aktualizuje okno.
    void pauseGame();
    /*! \brief Obsługuje klawiaturę
     *
     * Klawisz 'W' lub strzałka do góry przemieszcza kropkę do góry.
     * Klawisz 'A' lub strzałka w lewo przemieszcza kropkę w lewo.
     * Klawisz 'S' lub strzałka w dół przemieszcza kropkę w dół.
     * Klawisz 'D' lub strzałka w prawo przemieszcza kropkę w prawo.
     * Klawisz 'P' przemieszcza kropkę tuż przed wyjście.
     */
    void keyPressEvent(QKeyEvent *event);
    //! Sprawdza czy jest możliwy ruch w zadanym kierunku. Zwraca 0 gdy ruch jest niemożliwy, 1 gdy jest możliwy. \param direction 1-góra, 2-prawo, 4-dół, 8-lewo
    bool isMovePossible(int direction){
        return !(game->maze->array[game->maze->current_pos.y()][game->maze->current_pos.x()] & direction);
    }
    /*! \brief Rysuje labirynt.
     *
     * Rysuje labirynt jeśli wskaźnik na MazeStruct::array nie wynosi NULL oraz is_painter_off nie wynosi 1.
     * Jeśli blackout_size nie wynosi 0 rysuje tylko kratki w odległości blackout_size.
     * W przeciwnym razie wysuje cały labirynt.
     * Następnie rysuje pozycję gracza jako kropkę.
     */
    void paintEvent(QPaintEvent *);
    //! Rysuje pojedyńczą kratkę labiryntu. \param pos Pozycja kratki na oknie. \param borders Liczba określająca położenie ścian.
    void drawSquare(QPainter *painter, QPoint pos, int borders);
    //! Zamienia pozycję kratki w labiryncie (x,y) na pozycję QPoint na oknie i ją zwraca.
    QPoint grid(int x, int y);
    //! Zamienia pozycję kratki w labiryncie QPoint na pozycję QPoint na oknie i ją zwraca.
    QPoint grid(QPoint point);
};

#endif // MAINWINDOW_H
