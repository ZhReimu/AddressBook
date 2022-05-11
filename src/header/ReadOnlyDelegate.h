//
// Created by Administrator on 2022/5/11/011.
//

#ifndef QTSTUCOMM_READONLYDELEGATE_H
#define QTSTUCOMM_READONLYDELEGATE_H

#include "QItemDelegate"

class ReadOnlyDelegate : public QItemDelegate {

public:
    explicit ReadOnlyDelegate(QWidget *parent = nullptr) : QItemDelegate(parent) {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};


#endif //QTSTUCOMM_READONLYDELEGATE_H
