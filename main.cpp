#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QFile>
#if QT_VERSION >= 0x050000
#else
#include <QTextCodec>
#endif
#include <QDebug>
#define QT_DEBUG_COMPONENT

int main(int argc, char *argv[])
{
#if QT_VERSION >= 0x050000
#else
    QTextCodec::setCodecForTr( QTextCodec::codecForName("utf8") );
#endif

    QApplication a(argc, argv);

    QFile file( ":/css/stylesheet/mainwindow.css" );
    file.open( QFile::ReadOnly );
    QString strStyles = QLatin1String( file.readAll() );
    a.setStyleSheet( strStyles );

    int id = QFontDatabase::addApplicationFont( ":/font/font/meiryo.ttc" );
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    a.setFont(family);

    MainWindow w;
    w.show();

    return a.exec();
}
