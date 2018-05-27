/*! \file filedialog.h
 * Klasa okienka obsługującego zapisywanie, wczytywanie i usuwanie labiryntów.
 */
#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QTreeWidgetItem>

namespace Ui {
class FileDialog;
}
//! Klasa okienka obsługującego zapisywanie, wczytywanie i usuwanie labiryntów.
class FileDialog : public QDialog{
    Q_OBJECT
public:
    /*! Domyślny konstruktor klasy dziedziczącej po QDialog,
     * który dodatkowo tworzy ramkę wokół pola wpisywania
     */
    explicit FileDialog(QWidget *parent = 0);
    //!Domyślny destruktor klasy dziedziczącej po QDialog
    ~FileDialog();
    //! Dodaje nazwę i informacje o pliku do listy plików
    void addFileInfo(const QStringList &fileInfo);
    //! Zmienia nazwę przycisku pb_Accept (używane do zmiany na "Zapisz" lub "Wczytaj"
    void changeButtonText(const QString &name);
    //! Zmienia kolor ramki pola wpisywania na czerwony
    void highlightLine();
    //! Resetuje kolor ramki
    void unhighlightLine();
    //! Usuwa tekst z pola wpisywania
    void clearLine();
    //! Usuwa całą listę plików
    void clearTree();

private slots:
    //! Wpisuje nazwę pliku z listy do pola wpisywania, gdy zostanie kliknięty
    void on_tw_filesList_itemClicked(QTreeWidgetItem *item, int column);
    //! Wywołuje sygnał fileName(QString), gdy zostanie kliknięty przycisk Zapisz/Wczytaj
    void on_pb_Accept_clicked();
    //! Wywołuje sygnał deleteFile(QString), gdy zostanie kliknięty przycisk Usuń
    void on_pb_Delete_clicked();
    //! Zamyka okno, gdy zostanie kliknięty przycisk Zamknij
    void on_pb_Close_clicked();
    //! Wywołuje sygnał testFileName(QString), gdy zostanie zmieniony tekst w polu wpisywania
    void on_le_fileName_textChanged(const QString &arg1);

signals:
    /*! Wysyła tekst z pola wybierania do instakcji klasy FileManagment
     * \see bool FileManagment::testSaveName(const QString &file_name)
     * \see bool FileManagment::testLoadName(const QString &file_name)
     * \see bool FileManagment::testLeaderName(const QString &file_name)
     */
    void testFileName(QString);
    //! Wysyła tekst z pola wybierania do instakcji klasy FileManagment
    void fileName(QString);
    //! Wysyła tekst z pola wybierania do instakcji klasy FileManagment
    void deleteFile(QString);

private:
    Ui::FileDialog *ui;
};

#endif // FILEDIALOG_H
