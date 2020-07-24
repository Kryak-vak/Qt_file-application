#include "mainwindow.h"

#include <QApplication>


/**
  @fn main
  Главная функция
  Здесь создается само приложение, и его главное окно
*/
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;

    mainWindow.show();
    return app.exec();
}
