//
// Created by Mr.X on 2022-05-10-0010.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    model = new XTableModel(this, db);
    openDataBase();
    initComponents();
    initSignal();
}

MainWindow::~MainWindow() {
    delete ui;
    delete model;
}

void MainWindow::initComponents() {
    auto *readOnlyDelegate = new ReadOnlyDelegate(this);
    ui->tbStudent->setItemDelegateForColumn(0, readOnlyDelegate);
    ui->tbStudent->setModel(model);
    ui->tbStudent->verticalHeader()->hide();
    ui->tbStudent->setHorizontalHeader(model->getTableHeader());

}

void MainWindow::initSignal() {
    connect(ui->tbStudent->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(onHeaderClicked(int)));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(onSave()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(onAbout()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(onOpen()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionFind, SIGNAL(triggered()), this, SLOT(onFind()));
    connect(ui->btAdd, SIGNAL(clicked()), this, SLOT(onAdd()));
    connect(ui->btDel, SIGNAL(clicked()), this, SLOT(onDel()));
    connect(ui->btRevert, SIGNAL(clicked()), this, SLOT(onRevert()));
    connect(ui->btRevertSearch, SIGNAL(clicked()), this, SLOT(onRevertSearch()));
    connect(ui->actionAdd, SIGNAL(triggered()), this, SLOT(onAdd()));
    connect(ui->actionDel, SIGNAL(triggered()), this, SLOT(onDel()));
    connect(ui->actionRevert, SIGNAL(triggered()), this, SLOT(onRevertSearch()));
}

void MainWindow::openDataBase(const QString &path) {
    if (!QFile(path).exists()) {
        QMessageBox::critical(this, tr("错误"), tr("数据库不存在!!"));
        exit(-1);
    }
    db.setDatabaseName(path);
    if (!db.open()) {
        QMessageBox::critical(this, tr("错误"), tr("数据库打开失败!!"));
        qDebug() << "打开数据库失败!" << endl;
        return;
    }
    qDebug() << "打开数据库: " + path << endl;
    model->setTable("students");
    if (!model->select()) {
        QMessageBox::critical(this, tr("错误"), tr("查询数据失败!!"));
        qDebug() << "查询数据失败!" << endl;
    }
    map.insert("编号", "sid");
    map.insert("姓名", "name");
    map.insert("地址", "address");
    map.insert("电话", "phone");
    map.insert("邮编", "postCode");
    map.insert("邮件", "email");
    model->updateHeader(map);
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
    filter.append("数据库文件(*.db)");
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
        QMessageBox::critical(this, QString("错误"), "学生信息保存失败, 请检查数据是否合法");
    }
    // 刷新数据
    model->select();
}

void MainWindow::onAbout() {
    QMessageBox msg(this);
    msg.setWindowTitle(tr("关于 学生通讯录 Made By Mr.X"));
    msg.setText(tr("C++ 课程设计专用捏, Powered By Qt5.12.10"));
    msg.setIconPixmap(QPixmap(":/icon/1.png"));
    msg.exec();
}

void MainWindow::onAdd() {
    model->insertRow(0);
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

void MainWindow::onRevert() {
    model->revertAll();
    QMessageBox::information(this, QString("提示"), QString("放弃更改"));
}

void MainWindow::onFind() {
    QString dlgTitle = "搜索字段";
    QString txtLabel = "请选择按哪个字段搜索";
    bool ok = false;
    auto key = QInputDialog::getItem(
            this, dlgTitle, txtLabel, map.keys(), 0, false, &ok,
            Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint
    );
    if (ok) {
        auto value = QInputDialog::getText(this, "搜索", "请输入搜索内容",
                                           QLineEdit::Normal, nullptr, &ok,
                                           Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint
        );
        if (ok) {
            if (value.isEmpty()) {
                QMessageBox::critical(this, QString("错误"), QString("请输入搜索内容!"));
                return;
            }
            auto filter = map.value(key) + " = '" + value + "'";
            model->setFilter(filter);
            qDebug() << filter << endl;
        }
    }
}

void MainWindow::onRevertSearch() {
    model->setFilter(nullptr);
    model->select();
}