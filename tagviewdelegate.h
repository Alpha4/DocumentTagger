#ifndef TAGVIEWDELEGATE_H
#define TAGVIEWDELEGATE_H

#include <QStyledItemDelegate>
#include "tagmanager.h"

class TagViewDelegate : public QStyledItemDelegate
{
public:
    TagViewDelegate(TagManager *tm, QWidget* parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                   const QModelIndex &index) const;

private:
    TagManager* tagManager;
};

#endif // TAGVIEWDELEGATE_H
