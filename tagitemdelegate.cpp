#include "tagitemdelegate.h"
#include <QStyledItemDelegate>

void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
    if (index.data().canConvert<StarRating>()) {
        Tag tag = qvariant_cast<Tag>(index.data());

        if (option.state)
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override {

}
QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override{

}
void setEditorData(QWidget *editor, const QModelIndex &index) const override {

}
void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override {

}
