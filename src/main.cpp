#include <QtGui/QApplication>
#include <QTextCodec>
#include <QFile>
#include <QDebug>
#include <QLibraryInfo>
#include <QTranslator>
#include <QIcon>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load("qt_ru",
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    QCoreApplication::setOrganizationName("Валерий Харитонов");
    QCoreApplication::setApplicationName("KVNShuffle");
    QCoreApplication::setApplicationVersion("0.1");

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));

    QFile style("style.css");

    if (style.open(QIODevice::ReadOnly | QIODevice::Text)) {
        a.setStyleSheet(style.readAll());
    } else {
        qDebug() << "CSS file not found";
    }

    QIcon appIcon;
    appIcon.addPixmap(QPixmap(":/icons/icon128.png"));
    appIcon.addPixmap(QPixmap(":/icons/icon64.png"));
    appIcon.addPixmap(QPixmap(":/icons/icon48.png"));
    appIcon.addPixmap(QPixmap(":/icons/icon32.png"));
    a.setWindowIcon(appIcon);
    MainWindow w;
    w.show();

    return a.exec();
}
