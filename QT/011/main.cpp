#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDir mDir("d:/School/Anul II/Tehnici Avansate de Programare/QT/Test");

    foreach(QFileInfo mitm, mDir.entryInfoList())
    {

        if(mitm.isDir()) qDebug() << "Dir: " << mitm.absoluteFilePath() ;
        if(mitm.isFile()) qDebug() << "File: " << mitm.absoluteFilePath() ;

    }


    return a.exec();
}
