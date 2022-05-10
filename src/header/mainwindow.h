//
// Created by Mr.X on 2022-05-10-0010.
//

#ifndef CLIONPROJECTS_MAINWINDOW_H
#define CLIONPROJECTS_MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include <QStandardItemModel>
#include "Student.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:

    Student *students{};

    unsigned int studentNum = 0;

    Ui::MainWindow *ui;

    static int sortColumn;

    static Qt::SortOrder sortOrder;

    static QStandardItemModel *model;

    void initComponents();

    void initStudentData();

    static void onTableClicked(const QItemSelection &selected, const QItemSelection &deselected);

    static void onHeaderClicked(int index);

    static void onSave();


public Q_SLOTS:

    void onAbout();

};


#endif //CLIONPROJECTS_MAINWINDOW_H
