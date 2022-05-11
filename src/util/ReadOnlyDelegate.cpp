//
// Created by Administrator on 2022/5/11/011.
//

#include "ReadOnlyDelegate.h"

QWidget *ReadOnlyDelegate::createEditor(
        QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index
) const {
    Q_UNUSED(parent)
    Q_UNUSED(option)
    Q_UNUSED(index)
    return nullptr;
}
