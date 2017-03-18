#include "tagviewdelegate.h"
#include <QPainter>
#include <QApplication>

TagViewDelegate::TagViewDelegate(QWidget *parent):QStyledItemDelegate(parent)
{

}

void TagViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QFontMetrics fm(QApplication::font());
    if(!index.parent().data().isNull()){
        painter->setPen(QPen(Qt::red,2));
        QString text = index.data().toString();
        int textlen = fm.width(text);

        painter->drawRect(option.rect.x()+1,option.rect.y(),option.rect.y() +textlen,option.rect.height());
    }
    QStyledItemDelegate::paint(painter,option, index);
}
