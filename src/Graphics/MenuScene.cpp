#include "MenuScene.h"
#include "QGraphicsProxyWidget"
#include "QSettings"
#include <QCoreApplication>
#include <QProcess>
#include <QPainter>

MenuScene::MenuScene(QWidget* parent) : QGraphicsScene(parent) {
    int width = 400;
    int height = 400;
    QFont f("Times", 14);
    setSceneRect(0, 0, 1536, 864);
    QSize imgSize(48, 35);
    imgSize *= 2.5;
    startButton = new QPushButton(QObject::tr("Start"));
    startButton->setFixedSize(imgSize);
    startButton->setFont(f);
    startButton->setStyleSheet("QPushButton {border-image: url(:/button.png); background: transparent; color : rgb(242, 242, 242);} QPushButton:pressed {border-image: url(:/button_p.png);}");

    QSettings settings;
    soundButton = new QPushButton(QObject::tr("Sound : ") + (settings.value("sound").toBool() ? QObject::tr("On") : QObject::tr("Off")));
    soundButton->setFixedSize(imgSize);
    soundButton->setFont(f);
    soundButton->setStyleSheet("QPushButton {border-image: url(:/button.png); background: transparent; color : rgb(242, 242, 242);} QPushButton:pressed {border-image: url(:/button_p.png);}");

    languageButton = new QPushButton(settings.value("lang").toString());
    languageButton->setFixedSize(imgSize);
    languageButton->setFont(f);
    languageButton->setStyleSheet("QPushButton {border-image: url(:/button.png); background: transparent; color : rgb(242, 242, 242);} QPushButton:pressed {border-image: url(:/button_p.png);}");

    exitButton = new QPushButton(QObject::tr("Exit"));
    exitButton->setFixedSize(imgSize);
    exitButton->setFont(f);
    exitButton->setStyleSheet("QPushButton {border-image: url(:/button_e.png); background: transparent; color : rgb(242, 242, 242);}");

    auto* start = addWidget(startButton);
    start->setPos(width - start->size().width() / 2, height);
    auto* sound = addWidget(soundButton);
    sound->setPos(width - sound->size().width() / 2, height + start->size().height() + 10);
    auto* language = addWidget(languageButton);
    language->setPos(width - sound->size().width() / 2, height + 2 * (start->size().height() + 10));
    auto* exit =addWidget(exitButton);
    exit->setPos(width - exit->size().width() / 2, height + 3 * (start->size().height() + 10));

    auto* label = addText("Hades Survivors");
    f.setPointSize(25);
    label->setFont(f);
    label->setDefaultTextColor(QColor(242, 242, 242));
    QFontMetrics fm(f);
    label->setPos(width - fm.horizontalAdvance(label->toPlainText()) / 2, height / 2);

    connect(startButton, &QPushButton::clicked, [this](){emit MenuScene::start();});
    connect(soundButton, &QPushButton::clicked, [this](){
        QSettings settings;
        bool old = settings.value("sound", true).toBool();
        settings.setValue("sound", !old);
        soundButton->setText(QObject::tr("Sound : ") + (!old ? QObject::tr("On") : QObject::tr("Off")));
    });
    connect(languageButton, &QPushButton::clicked, [this]() {
       QSettings settings;
       QString old = settings.value("lang", "English").toString();
       settings.setValue("lang", old == "English" ? "Russian" : "English");
       languageButton->setText(settings.value("lang").toString());
       qApp->quit();
       QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    });
    connect(exitButton, &QPushButton::clicked, [this](){emit MenuScene::exit();});
}

void MenuScene::drawBackground(QPainter* painter, const QRectF& rect) {
    QPixmap bg(":/menu.png");
    painter->drawPixmap(sceneRect().topLeft(), bg);
}
