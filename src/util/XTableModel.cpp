//
// Created by Mr.X on 2022-05-11-0011.
//

#include "XTableModel.h"

XTableModel::XTableModel(QObject *parent, const QSqlDatabase &db) : QSqlTableModel(parent, db) {
    tableHeader = nullptr;
}

XTableModel::XTableModel(QObject *parent, const QSqlDatabase &db, const QMap<QString, QString> &keyMap) : XTableModel(
        parent, db) {

    tableHeader = new QHeaderView(Qt::Horizontal);

    tableHeader->setModel(this);
    tableHeader->setSectionsClickable(true);
    tableHeader->setSectionResizeMode(QHeaderView::Stretch);

    auto keys = keyMap.keys();
    auto size = keyMap.size();
    for (int i = 0; i < size; ++i) {
        auto key = keys[i];
        auto value = keyMap.find(key).value();
        this->setHeaderData(fieldIndex(value), Qt::Horizontal, key);
    }
    this->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QVariant XTableModel::data(const QModelIndex &idx, int role) const {
    QVariant value = QSqlTableModel::data(idx, role);
    if (Qt::TextAlignmentRole == role) {
        value = int(Qt::AlignCenter | Qt::AlignHCenter);
        return value;
    }
    return value;
}

QHeaderView *XTableModel::getTableHeader() const {
    return tableHeader;
}
