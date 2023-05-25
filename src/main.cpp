#include "GameWindow.h"
#include <QApplication>
#include <QFontDialog>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow game;
    game.show();
    return QApplication::exec();
}
