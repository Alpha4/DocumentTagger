#include "tag.h"


Tag::Tag(TagGroup* parent, QString name, QColor* color):parent(parent), name(name), color(color){

}

QColor* Tag::getColor(){
    return this->color;
}

void Tag::setColor(QColor* color){
    this->color = color;
}

QString Tag::getName(){
    return this->name;
}

void Tag::setName(QString name){
    this->name = name;
}

TagGroup* Tag::getParent(){
    return this->parent;
}

void Tag::setParent(TagGroup* parent){
    this->parent = parent;
}
