#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include <QFile>
#include <QList>
#include <QHash>
#include "tag.h"

class TagManager
{
public:
    TagManager(QFile* tagFile, QFile* tagGroupFile);
    ~TagManager();
    void addFile(Tag tag,QFile* f);
    void removeFile(Tag tag,QFile* f);
    void addTag(Tag tag);
    void removeTag(Tag tag);
    void fillHashTable();
    void saveHashTable();
private:
    QFile* tagFile;
    QFile* tagGroupFile;
    QHash<QString,TagGroup>* tagGroupHash;
    QHash<Tag,QList<QFile*>>* tagHash;
};

#endif // TAGMANAGER_H
