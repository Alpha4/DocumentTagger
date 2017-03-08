#ifndef TAGGROUP_H
#define TAGGROUP_H

#pragma once

#include <QList>
#include "tag.h"

class Tag;
class TagGroup
{
public:
    TagGroup(QString groupName);
    QList<Tag> getTagList();
    void insertTag(Tag tag);
    void removeTag(int index);
    void removeAllTags();
    Tag* getTagAtIndex(int index);
    int size();
    Tag* getTagByName(QString name);

private:
    QList<Tag> tagList;
    QString groupName;
};

#endif // TAGGROUP_H
