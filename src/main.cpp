#include "GameWindow.h"
#include <QApplication>
#include <QSettings>
#include <QTranslator>
int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("rycbar");
    QCoreApplication::setApplicationName("Hades Survivors");
    QApplication a(argc, argv);
    QSettings settings;
    QTranslator translator;
    translator.load(QString(":/translations/%1.qm").arg(settings.value("lang", "English").toString() == "Russian" ? "ru" : "en"));
    QApplication::installTranslator(&translator);
    GameWindow game;
    game.showFullScreen();
    return QApplication::exec();
}
