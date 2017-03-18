#include "tag.h"


Tag::Tag(TagGroup* parent, QString name, QColor* color):parent(parent), name(name), color(color){

}

QColor* Tag::getColor() const{
    return this->color;
}

void Tag::setColor(QColor* color){
    this->color = color;
}

QString Tag::getName() const{
    return this->name;
}

void Tag::setName(QString name){
    this->name = name;
}

TagGroup* Tag::getParent() const{
    return this->parent;
}

bool Tag::operator==(const Tag& other) const
{
    if(other.color == this->color && other.parent->getTagGroupName() == parent->getTagGroupName() && other.name == name){
        return true;
    }
    return false;
}


void Tag::setParent(TagGroup* parent){
    this->parent = parent;
}
