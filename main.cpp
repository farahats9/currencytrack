#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("F9");
    QCoreApplication::setOrganizationDomain("farahats9.github.io");
    QCoreApplication::setApplicationName("Currency Track");
    MainWindow w;
    w.setAttribute(Qt::WA_TranslucentBackground);
    w.setWindowFlags(Qt::WindowStaysOnBottomHint | Qt::FramelessWindowHint | Qt::Tool);
    w.show();
    return a.exec();
}
