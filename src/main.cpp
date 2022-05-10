#include <QApplication>
#include "mainwindow.h"
#include "FileUtils.h"

int main(int argc, char *argv[]) {

//    Student s[2];
//    s[0].setName("asd");
//    s[1].setName("bbb");
//    saveStudents(s, 2);
    int num = 0;
    FileUtils::readStudents(num);
    cout << num << endl;
}

int showWindow(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow window;
    window.show();
    return QApplication::exec();
}