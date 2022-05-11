//
// Created by Mr.X on 2022-05-11-0011.
//

#ifndef QTSTUCOMM_XTABLEMODEL_H
#define QTSTUCOMM_XTABLEMODEL_H


#include "QSqlTableModel"

class XTableModel : public QSqlTableModel {

public:
    explicit XTableModel(QObject *parent = nullptr, const QSqlDatabase &db = QSqlDatabase());

    QVariant data(const QModelIndex &idx, int role) const override;
};


#endif //QTSTUCOMM_XTABLEMODEL_H
