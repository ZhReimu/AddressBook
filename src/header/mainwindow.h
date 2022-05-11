//
// Created by Mr.X on 2022-05-10-0010.
//

#ifndef CLIONPROJECTS_MAINWINDOW_H
#define CLIONPROJECTS_MAINWINDOW_H

#include "iostream"
#include "QMessageBox"
#include "QFileDialog"
#include "QDataWidgetMapper"
#include "QSqlRecord"
#include "QDebug"
#include "QMainWindow"
#include "QItemSelection"
#include "QStandardItemModel"
#include "QSqlDatabase"
#include "QSqlTableModel"
#include "QInputDialog"

#include "ReadOnlyDelegate.h"
#include "XTableModel.h"

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

    XTableModel *model;

    QMap<QString, QString> map;

    void initComponents();

    void openDataBase(const QString &path = "students.db");


public Q_SLOTS:

    void onAbout();

    void onHeaderClicked(int index);

    void onSave();

    void initSignal();

    void onOpen();

    void onAdd();

    void onDel();

    void onRevert();

    void onFind();

    void onRevertSearch();
};


#endif //CLIONPROJECTS_MAINWINDOW_H
