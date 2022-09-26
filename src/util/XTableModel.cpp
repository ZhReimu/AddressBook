//
// Created by Mr.X on 2022-05-11-0011.
//

#include "XTableModel.h"
#include "QDebug"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedParameter"

XTableModel::XTableModel(QObject *parent, const QSqlDatabase &db) {
    tableHeader = new QHeaderView(Qt::Horizontal);
    tableHeader->setModel(this);
    tableHeader->setSectionsClickable(true);
    tableHeader->setSectionResizeMode(QHeaderView::Stretch);
    this->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

#pragma clang diagnostic pop

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

void XTableModel::updateHeader(const QMap<QString, QString> &keyMap) {
    auto keys = keyMap.keys();
    auto size = keyMap.size();
    for (int i = 0; i < size; ++i) {
        auto key = keys[i];
        auto value = keyMap.find(key).value();
        this->setHeaderData(fieldIndex(value), Qt::Horizontal, key);
    }
}

