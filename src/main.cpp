#include <QApplication>
#include "mainwindow.h"
#include "FileUtils.h"

int main(int argc, char *argv[]) {
    test();
    QApplication a(argc, argv);
    MainWindow window;
    window.show();
    return QApplication::exec();
}
