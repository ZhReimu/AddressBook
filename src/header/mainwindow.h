//
// Created by Mr.X on 2022-05-10-0010.
//

#ifndef CLIONPROJECTS_MAINWINDOW_H
#define CLIONPROJECTS_MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include <QStandardItemModel>
#include <QSqlDatabase>
#include <QSqlTableModel>
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

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    Ui::MainWindow *ui;

    int sortColumn = -1;

    Qt::SortOrder sortOrder = Qt::AscendingOrder;

    QSqlTableModel *model;

    void initComponents();

    void openDataBase(const QString &path = "students.db");


public Q_SLOTS:

    void onAbout();

    void onTableClicked(const QItemSelection &selected, const QItemSelection &deselected);

    void onHeaderClicked(int index);

    void onSave();

    void initSignal(const QObject *selectionModel, const QObject *tableHeader);

    void onOpen();

    void onAdd();

    void onDel();
};


#endif //CLIONPROJECTS_MAINWINDOW_H
