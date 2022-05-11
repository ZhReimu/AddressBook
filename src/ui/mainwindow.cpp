//
// Created by Mr.X on 2022-05-10-0010.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_MainWindow.h"

// NOLINT
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    initComponents();
    initSignal();
}

MainWindow::~MainWindow() {
    delete ui;
    delete model;
}

void MainWindow::initComponents() {
    openDataBase();

    auto *selectionModel = new QItemSelectionModel(model);
    auto *tableHeader = new QHeaderView(Qt::Horizontal);
    auto *readOnlyDelegate = new ReadOnlyDelegate(this);


    tableHeader->setModel(model);
    tableHeader->setSectionsClickable(true);
    tableHeader->setSectionResizeMode(QHeaderView::Stretch);

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(model->fieldIndex("sid"), Qt::Horizontal, "编号");
    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, "姓名");
    model->setHeaderData(model->fieldIndex("address"), Qt::Horizontal, "地址");
    model->setHeaderData(model->fieldIndex("phone"), Qt::Horizontal, "电话");
    model->setHeaderData(model->fieldIndex("postCode"), Qt::Horizontal, "邮编");
    model->setHeaderData(model->fieldIndex("E-mail"), Qt::Horizontal, "邮件");


    ui->tbStudent->setItemDelegateForColumn(0, readOnlyDelegate);
    ui->tbStudent->setModel(model);
    ui->tbStudent->verticalHeader()->hide();
    ui->tbStudent->setSelectionModel(selectionModel);
    ui->tbStudent->setHorizontalHeader(tableHeader);

}

void MainWindow::initSignal() {
    connect(ui->tbStudent->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(onHeaderClicked(int)));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(onSave()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(onAbout()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(onOpen()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->btAdd, SIGNAL(clicked()), this, SLOT(onAdd()));
    connect(ui->btDel, SIGNAL(clicked()), this, SLOT(onDel()));
}

void MainWindow::openDataBase(const QString &path) {
    db.setDatabaseName(path);
    if (!db.open()) {
        QMessageBox::critical(this, tr("错误"), tr("数据库打开失败!!"));
        qDebug() << "打开数据库失败!" << endl;
        return;
    }
    qDebug() << "打开数据库: " + path << endl;
    model = new QSqlTableModel(this, db);
    model->setTable("students");
    if (!model->select()) {
        QMessageBox::critical(this, tr("错误"), tr("查询数据失败!!"));
        qDebug() << "查询数据失败!" << endl;
    }
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
    filter.append("数据库文件(*.db,*.sqlite)");
    filter.append("所有文件(*.*)");
    fileDialog->setWindowTitle(tr("读取文件"));
    fileDialog->setNameFilters(filter);
    if (fileDialog->exec() == QDialog::Accepted) {
        openDataBase(fileDialog->selectedFiles().first());
    } else {
        QMessageBox::warning(this, tr("警告"), tr("取消打开文件"));
    }
}

void MainWindow::onSave() {
    if (model->submitAll()) {
        QMessageBox::information(this, QString("提示"), "学生信息已经保存!");
    } else {
        QMessageBox::critical(this, QString("错误"), "学生信息保存失败!");
    }
}

void MainWindow::onAbout() {
    QMessageBox::information(this, QString("关于"), QString("C++ 课程设计专用捏"));
}

void MainWindow::onAdd() {
    QSqlRecord record;
    for (int i = 0; i < 6; ++i) {
        record.setNull(i);
    }
    model->insertRecord(0, record);
    qDebug() << "添加学生信息" << endl;
}

void MainWindow::onDel() {
    int row = ui->tbStudent->currentIndex().row();
    if (row == -1) {
        QMessageBox::critical(this, "错误", "请选择需要删除的记录所在单元格!");
    }
    auto value = model->record(row);
    bool res = model->removeRow(row);
    qDebug() << "删除一行: " << row << ", " << res << endl;
    if (value.isNull(0)) {
        return;
    }
    auto btRes = QMessageBox::question(this, "删除", tr("真的要删除 ") + value.value(1).toString() + tr(" 吗?"));
    if (btRes == QMessageBox::Yes) {
        model->submitAll();
        QMessageBox::information(this, "提示", "删除成功!");
    } else {
        QMessageBox::warning(this, "提示", "取消删除!");
    }
}