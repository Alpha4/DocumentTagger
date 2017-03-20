#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include <QFile>
#include <QList>
#include <QHash>
#include <QStandardItemModel>
#include "tag.h"

class TagManager
{
public:
    TagManager(QFile* tagFile, QFile* tagGroupFile);
    ~TagManager();
    void addFile(Tag tag,QFile* f);
    void removeFile(Tag tag,QFile* f);
    TagGroup* getTagGroup(QString groupName);
    void insertTagGroup(TagGroup* tagGroup);
    void removeTag(Tag tag);
    void fillHashTable();
    void saveHashTable();
    QList<Tag> getKeys();
    QList<QString> getTagGroupKeys();
    QStandardItemModel* createModel();
    void addTag(Tag tag);

private:
    QFile* tagFile;
    QFile* tagGroupFile;
    QHash<QString,TagGroup*> tagGroupHash;
    QHash<Tag,QList<QFile*>> tagHash;
};

#endif // TAGMANAGER_H
