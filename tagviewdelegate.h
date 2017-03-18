#ifndef TAGVIEWDELEGATE_H
#define TAGVIEWDELEGATE_H

#include <QStyledItemDelegate>

class TagViewDelegate : public QStyledItemDelegate
{
public:
    TagViewDelegate(QWidget* parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                   const QModelIndex &index) const;

};

#endif // TAGVIEWDELEGATE_H
