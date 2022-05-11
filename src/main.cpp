#include <QApplication>
#include "mainwindow.h"
#include "FileUtils.h"

int showWindow(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow window;
    window.show();
    return QApplication::exec();
}

int main(int argc, char *argv[]) {
    return showWindow(argc, argv);
}

