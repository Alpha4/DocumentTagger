#include "tagmanager.h"
#include <iostream>
#include <QTextStream>
#include <QList>


TagManager::TagManager(QFile* tagFile, QFile* tagGroupFile)
{
    this->tagFile = tagFile;
    this->tagGroupFile = tagGroupFile;
    /*
    this->tagHash = new QHash<Tag,QList<QFile*>>();
    this->tagGroupHash = new QHash<QString,TagGroup>();
    */
}

TagManager::~TagManager(){
    delete tagFile;
    delete tagGroupFile;
    /*
    delete tagHash;
    delete tagGroupHash;
    */
}

void TagManager::addFile(Tag tag,QString f){
    std::cout<<"before adding element in list"<<std::endl;
    tagHash[tag].push_back(f);
    std::cout<<"after adding elem in list"<<std::endl;
}

void TagManager::removeFile(Tag tag, QString f){
    tagHash[tag].removeOne(f);
}

TagGroup *TagManager::getTagGroup(QString groupName)
{
    return tagGroupHash[groupName];
}

void TagManager::insertTagGroup(TagGroup *tagGroup)
{
    QString name = tagGroup->getTagGroupName();
    tagGroupHash.insert(name,tagGroup);
}

void TagManager::addTag(Tag tag){
    QList<QString> list;
    tagHash.insert(tag,list);
}

void TagManager::removeTag(Tag tag){
    tagHash.remove(tag);
}

void TagManager::fillHashTable(){
    if(!tagGroupFile->open(QIODevice::ReadOnly)){
        std::cout<<"error: "<<tagGroupFile->errorString().toStdString()<<std::endl;
    }
    QTextStream in(tagGroupFile);

    while(!in.atEnd()){
        QString tagGroupName = in.readLine();
        TagGroup* tagGroup = new TagGroup(tagGroupName);
        tagGroupHash.insert(tagGroupName,tagGroup);
    }
    tagGroupFile->close();

    //open the second file and read the tags
    if(!tagFile->open(QIODevice::ReadOnly)){
        std::cout<<"error: "<<tagFile->errorString().toStdString()<<std::endl;
    }
    QTextStream iin(tagFile);
    while(!iin.atEnd()){
        QString line = iin.readLine();
        QStringList fields = line.split(",");
        QString tagName = fields[0];
        QString tagColor = fields[1];
        QString tagParent = fields[2];

        QColor color(tagColor);
        std::cout<<"color = "<<color.name().toStdString()<<std::endl;
        TagGroup* tagGroup = tagGroupHash[tagParent];
        Tag tag(tagGroup,tagName,&color);
        std::cout<<"color tag = "<<tag.getColor()->name().toStdString()<<std::endl;
        QList<QString> listFiles;
        tagHash.insert(tag,listFiles);
        if(fields.size() > 2){
            for(int i=3; i<fields.size(); i++){
                QString f = fields[i];
                tagHash[tag].push_back(f);
            }
        }
    }
    tagFile->close();
}

void TagManager::saveHashTable(){
    if(!tagGroupFile->open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)){
        std::cout<<"error: "<<tagGroupFile->errorString().toStdString()<<std::endl;
    }
    QTextStream outgf(tagGroupFile);

    if(!tagFile->open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)){
        std::cout<<"error: "<<tagFile->errorString().toStdString()<<std::endl;
    }
    QTextStream outf(tagFile);

    std::cout<<"size of taghash = "<<tagHash.size()<<std::endl;
    for(auto it = tagHash.begin();it != tagHash.end(); it++){
        QString line;
        line.append(it.key().getName());
        line.append(",");
        line.append(it.key().getColor()->name());
        std::cout<<it.key().getColor()->name().toStdString()<<std::endl;
        line.append(",");
        line.append(it.key().getParent()->getTagGroupName());
        QList<QString> files = it.value();
        for(int i = 0; i < files.size(); i++){
            line.append(",");
            std::cout<<"Writing on file: "<<files[i].toStdString()<<std::endl;
            line.append(files[i]);
        }
        std::cout<<line.toStdString()<<std::endl;
        outf<<line<<endl;
    }
    tagFile->close();
    std::cout<<"after writing the tags"<<std::endl;

    for(auto it = tagGroupHash.begin(); it != tagGroupHash.end(); it++){
        QString line;
        line.append(it.key());
        std::cout<<line.toStdString()<<std::endl;
        outgf<<line<<endl;
    }
    tagGroupFile->close();
}

QList<Tag> TagManager::getKeys()
{
    return this->tagHash.keys();
}

QList<QString> TagManager::getTagGroupKeys(){
    return this->tagGroupHash.keys();
}

QStandardItemModel* TagManager::createModel()
{
    QStandardItemModel* model = new QStandardItemModel();
    QStandardItem* parentItem = model->invisibleRootItem();
    QList<QString> keys = getTagGroupKeys();
    //construct the first nodes corresponding to groups
    for(int i = 0; i< keys.size(); i++){
        QStandardItem* item = new QStandardItem(keys[i]);
        parentItem->appendRow(item);
    }
    //go through each tag and insert it in the correct taggroup
    QList<Tag> tkeys = getKeys();
    int children = parentItem->rowCount();
    for(int i = 0; i<tkeys.size(); i++){
        QStandardItem* actualParent = NULL;
        for(int j = 0; j< children; j++){
            if(parentItem->child(j)->text() == tkeys[i].getParent()->getTagGroupName()){
                actualParent = parentItem->child(j);
                break;
            }
        }
        QStandardItem* item = new QStandardItem(tkeys[i].getName());
        actualParent->appendRow(item);
    }
    return model;
}

QStandardItemModel* TagManager::createOnlyListModel()
{
    QStandardItemModel* model = new QStandardItemModel();
    QStandardItem* parentItem = model->invisibleRootItem();
    QList<Tag> keys = getKeys();
    //construct the first nodes corresponding to groups
    for(int i = 0; i< keys.size(); i++){
        QStandardItem* item = new QStandardItem(keys[i].getName());
        parentItem->appendRow(item);
    }

    return model;
}

QStandardItemModel* TagManager::createFilteredModel(QString string){
    std::cout<<string.toStdString()<<std::endl;
    QList<Tag> final;
    std::cout<<final.size()<<std::endl;
    QList<Tag> keys = this->getKeys();
    for(int i=0; i<keys.size(); i++){
        if(tagHash[keys[i]].contains(string)){
            final.append(keys[i]);
        }
    }
    std::cout<<final.size()<<std::endl;
    QStandardItemModel* model = new QStandardItemModel();
    QStandardItem* parentItem = model->invisibleRootItem();
    if(final.size() == 0){
        return model;
    }
    for(int i = 0; i<final.size(); i++){
        QStandardItem* item = new QStandardItem(final[i].getName());
        parentItem->appendRow(item);
    }

    return model;
}

