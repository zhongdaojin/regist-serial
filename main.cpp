#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QFile>
#include <QDebug>
#define QT_DEBUG_COMPONENT

int main(int argc, char *argv[])
{
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
