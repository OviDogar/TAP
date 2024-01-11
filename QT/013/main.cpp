#include <QtCore/QCoreApplication>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>

void Read(QString Filename)
{
    QFile mFile(Filename);

    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "could not open file for reading";
        return;
    }

    QTextStream in(&mFile);
    QString mText = in.readAll();

    qDebug() << mText;

    mFile.close();
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Read(":/School/Anul II/Tehnici Avansate de Programare/QT/013/Qt_13.pro");

    return a.exec();
}
