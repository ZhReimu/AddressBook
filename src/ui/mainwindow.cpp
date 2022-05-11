//
// Created by Mr.X on 2022-05-10-0010.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "FileUtils.h"
#include <QStandardItemModel>
#include <iostream>
#include <QMessageBox>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
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
    tableHeader->setSectionResizeMode(QHeaderView::Stretch);
    model->setColumnCount(5);
    model->setHeaderData(0, Qt::Horizontal, "姓名");
    model->setHeaderData(1, Qt::Horizontal, "地址");
    model->setHeaderData(2, Qt::Horizontal, "电话");
    model->setHeaderData(3, Qt::Horizontal, "邮编");
    model->setHeaderData(4, Qt::Horizontal, "E-Mail");
    tb->setModel(model);
    tb->setSelectionModel(selectionModel);
    tb->setHorizontalHeader(tableHeader);
    initSignal(selectionModel, tableHeader);
}

void MainWindow::initSignal(const QObject *selectionModel, const QObject *tableHeader) {
    connect(selectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            this, SLOT(onTableClicked(QItemSelection, QItemSelection)));
    connect(tableHeader, SIGNAL(sectionClicked(int)), this, SLOT(onHeaderClicked(int)));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(onSave()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(onAbout()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(onOpen()));
}

void MainWindow::initStudentData() {
//    studentNum = 100;
//    students = new Student[studentNum];
//    for (int i = 0; i < studentNum; i++) {
//        students[i].setName(QString(i % 26 + 65));
//        students[i].setAddress(QString(i % 26 + 48));
//        students[i].setPhone("123456");
//        students[i].setPostCode("奥里给");
//        students[i].setEMail("123@qq.com");
//    }
    for (int i = 0; i < studentNum; i++) {
        model->setItem(i, 0, new QStandardItem(students[i].getName()));
        model->setItem(i, 1, new QStandardItem(students[i].getAddress()));
        model->setItem(i, 2, new QStandardItem(students[i].getPhone()));
        model->setItem(i, 3, new QStandardItem(students[i].getPostCode()));
        model->setItem(i, 4, new QStandardItem(students[i].getEMail()));
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

void MainWindow::onOpen() {
    auto *fileDialog = new QFileDialog(this);
    QStringList filter;
    filter.append("保存的文件(*.json)");
    filter.append("所有文件(*.*)");
    fileDialog->setWindowTitle(tr("读取文件"));
    fileDialog->setNameFilters(filter);
    if (fileDialog->exec() == QDialog::Accepted) {
        QString path = fileDialog->selectedFiles().first();
        if (FileUtils::verifyFile(path)) {
            // 重新打开时释放掉之前的 students
            delete[] students;
            students = FileUtils::readStudents(studentNum, path);
            initStudentData();
            QMessageBox::information(this, tr("提示"), tr("打开文件: ") + path);
        } else {
            QMessageBox::critical(this, tr("错误"), tr("文件不是有效的格式!!"));
        }
    } else {
        QMessageBox::warning(this, tr("警告"), tr("取消打开文件"));
    }
}

void MainWindow::onSave() {
    FileUtils::saveStudents(students, studentNum);
    QMessageBox::information(this, QString("提示"), "学生信息已经保存!");
}

void MainWindow::onAbout() {
    QMessageBox::information(this, QString("关于"), QString("C++ 课程设计专用捏"));
}
