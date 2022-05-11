//
// Created by Mr.X on 2022-05-11-0011.
//

#include "XTableModel.h"

XTableModel::XTableModel(QObject *parent, const QSqlDatabase &db) : QSqlTableModel(parent, db) {

}

QVariant XTableModel::data(const QModelIndex &idx, int role) const {
    QVariant value = QSqlTableModel::data(idx, role);
    if (Qt::TextAlignmentRole == role) {
        value = int(Qt::AlignCenter | Qt::AlignHCenter);
        return value;
    }
    return value;
}
