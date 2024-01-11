#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString mStr = "hello world";

    qDebug() << "hello world";
    qDebug() << mStr;

    return a.exec();
}
