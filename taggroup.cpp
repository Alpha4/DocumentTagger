#include "taggroup.h"

TagGroup::TagGroup()
{
    groupName = "Default";
}

TagGroup::TagGroup(QString groupName): groupName(groupName)
{

}

QList<Tag> TagGroup::getTagList(){
    return this->tagList;
}

void TagGroup::insertTag(Tag tag){
    tagList.append(tag);
}

void TagGroup::removeTag(int index){
    tagList.removeAt(index);
}

void TagGroup::removeAllTags(){
    tagList.clear();
}

Tag* TagGroup::getTagAtIndex(int index){
    if(index<0 || index>=tagList.size()) return nullptr ;
    return &tagList[index];
}

int TagGroup::size(){
    return tagList.size();
}

Tag* TagGroup::getTagByName(QString name){
    for(int i=0; i<tagList.size(); i++){
        if(tagList[i].getName() == name){
            return &tagList[i];
        }
    }
    return nullptr;
}

QString TagGroup::getTagGroupName() const{
    return this->groupName;
}

