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
    db->setDatabaseName(dbFile);
    model = new QSqlTableModel(this, *db);
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
    model->setTable("students");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
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
