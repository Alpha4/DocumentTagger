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
    void addFile(Tag tag,QString f);
    void removeFile(Tag tag,QString f);
    TagGroup* getTagGroup(QString groupName);
    void insertTagGroup(TagGroup* tagGroup);
    void removeTag(Tag tag);
    void fillHashTable();
    void saveHashTable();
    QList<Tag> getKeys();
    QList<QString> getTagGroupKeys();
    QStandardItemModel* createModel();
    void addTag(Tag tag);

    QStandardItemModel *createOnlyListModel();
    QStandardItemModel *createFilteredModel(QString string);
private:
    QFile* tagFile;
    QFile* tagGroupFile;
    QHash<QString,TagGroup*> tagGroupHash;
    QHash<Tag,QList<QString>> tagHash;
};

#endif // TAGMANAGER_H
