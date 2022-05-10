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
    int a = 0;
    cout << FileUtils::readStudents(a)[0] << endl;
    return showWindow(argc, argv);
}

