//
// Created by Mr.X on 2022-05-11-0011.
//

#ifndef QTSTUCOMM_XTABLEMODEL_H
#define QTSTUCOMM_XTABLEMODEL_H


#include "QSqlTableModel"
#include "QHeaderView"
#include "QHeaderView"
#include "ReadOnlyDelegate.h"

class XTableModel : public QSqlTableModel {

private:
    QHeaderView *tableHeader;

public:
    explicit XTableModel(QObject *parent = nullptr, const QSqlDatabase &db = QSqlDatabase());

    QVariant data(const QModelIndex &idx, int role) const override;

    QHeaderView *getTableHeader() const;

    void updateHeader(const QMap<QString, QString> &keyMap);
};


#endif //QTSTUCOMM_XTABLEMODEL_H
