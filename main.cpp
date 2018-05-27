/*! \mainpage
 * Projekt ZAP 2 "Generowanie Labiryntu"
 * \author Kamil Długosz
 * \date 27.05.2018
 *
 */
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
