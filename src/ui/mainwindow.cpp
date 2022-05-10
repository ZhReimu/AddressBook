//
// Created by Mr.X on 2022-05-10-0010.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_MainWindow.h"
#include <QStandardItemModel>
#include <iostream>

QStandardItemModel *MainWindow::model = new QStandardItemModel(); // NOLINT

int MainWindow::sortColumn = -1;

Qt::SortOrder MainWindow::sortOrder = Qt::AscendingOrder;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    initStudentData();
    initComponents();
}

MainWindow::~MainWindow() {
    delete ui;
    delete[] students;
}

void MainWindow::initComponents() {
    QTableView *tb = ui->tbStudent;
    auto *selectionModel = new QItemSelectionModel(model);
    auto *tableHeader = new QHeaderView(Qt::Horizontal);
    tableHeader->setModel(model);
    tableHeader->setSectionsClickable(true);
    model->setColumnCount(5);
    model->setHeaderData(0, Qt::Horizontal, "姓名");
    model->setHeaderData(1, Qt::Horizontal, "地址");
    model->setHeaderData(2, Qt::Horizontal, "电话");
    model->setHeaderData(3, Qt::Horizontal, "邮编");
    model->setHeaderData(4, Qt::Horizontal, "E-Mail");
    for (int i = 0; i < studentNum; i++) {
        model->setItem(i, 0, new QStandardItem(students[i].getName()));
        model->setItem(i, 1, new QStandardItem(students[i].getAddress()));
        model->setItem(i, 2, new QStandardItem(students[i].getPhone()));
        model->setItem(i, 3, new QStandardItem(students[i].getPostCode()));
        model->setItem(i, 4, new QStandardItem(students[i].getEMail()));
    }

    tb->setModel(model);
    tb->setSelectionModel(selectionModel);
    tb->setHorizontalHeader(tableHeader);

    connect(selectionModel, &QItemSelectionModel::selectionChanged, MainWindow::onTableClicked);
    connect(tableHeader, &QHeaderView::sectionClicked, MainWindow::onHeaderClicked);
}

void MainWindow::initStudentData() {
    studentNum = 100;
    students = new Student[studentNum];
    for (int i = 0; i < studentNum; i++) {
        students[i].setName(QString(i % 26 + 65));
        students[i].setAddress(QString(i % 26 + 48));
        students[i].setPhone("123456");
        students[i].setPostCode("999988");
        students[i].setEMail("123@qq.com");
    }
}

void MainWindow::onTableClicked(const QItemSelection &selected, const QItemSelection &deselected) {
    using namespace std;
//    cout << "selected " << selected.count() << " " << deselected.count() << endl;
}

void MainWindow::onHeaderClicked(int index) {
    // 如果本次排序列与上次不相同, 那就更新以下 sortColumn
    if (sortColumn != index) {
        sortColumn = index;
    } else {
        // 如果是第二次点击本列, 那就修改排序顺序
        sortOrder = sortOrder == Qt::AscendingOrder ? Qt::DescendingOrder : Qt::AscendingOrder;
    }
    model->sort(sortColumn, sortOrder);
}