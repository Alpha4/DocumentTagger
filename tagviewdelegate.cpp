#include "tagviewdelegate.h"
#include <QPainter>
#include <QPen>
#include <QList>
#include <QApplication>
#include <iostream>

TagViewDelegate::TagViewDelegate(TagManager* tm,
                                 QWidget *parent):
    QStyledItemDelegate(parent),
    tagManager(tm)
{

}

void TagViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(!index.parent().data().isNull()){
        QString d = index.data().toString();
        QString groupName = index.parent().data().toString();
        //TagGroup* tgroup = tagManager->getTagGroup(groupName);
        QList<Tag> tags = tagManager->getKeys();
        //Tag* thisTag = NULL;
        for(int i = 0; i<tags.size(); i++){
            if(tags[i].getName() == d && tags[i].getParent()->getTagGroupName() == groupName){

                painter->setBackground(QBrush(*tags[i].getColor()));
                painter->setBackgroundMode(Qt::OpaqueMode);
                break;
            }
        }
        /*
        QColor* color = thisTag->getColor();
        std::cout<<"color finale: "<<color->name().toStdString()<<std::endl;
        painter->setPen(QPen(*color,2));
        painter->drawRect(option.rect.x()+1,option.rect.y(),option.rect.width(),option.rect.height());
        */
    }
    QStyledItemDelegate::paint(painter,option, index);
}
