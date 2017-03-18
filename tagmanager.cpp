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

void TagManager::addFile(Tag tag,QFile* f){
    tagHash[tag].push_back(f);
}

void TagManager::removeFile(Tag tag, QFile *f){
    tagHash[tag].removeOne(f);
}

void TagManager::addTag(Tag tag){
    QList<QFile*> list;
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
        TagGroup tagGroup(tagGroupName);
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
        TagGroup tagGroup = tagGroupHash[tagParent];
        Tag tag(&tagGroup,tagName,&color);
        QList<QFile*> listFiles;
        tagHash.insert(tag,listFiles);
        if(fields.size() > 2){
            for(int i=3; i<fields.size(); i++){
                QFile* f = new QFile(fields[i]);
                tagHash[tag].push_back(f);
            }
        }
    }
    tagFile->close();
}

void TagManager::saveHashTable(){
    if(!tagGroupFile->open(QIODevice::Append)){
        std::cout<<"error: "<<tagGroupFile->errorString().toStdString()<<std::endl;
    }
    QTextStream outgf(tagGroupFile);

    if(!tagFile->open(QIODevice::Append)){
        std::cout<<"error: "<<tagFile->errorString().toStdString()<<std::endl;
    }
    QTextStream outf(tagFile);

    for(auto it = tagHash.begin();it != tagHash.end(); it++){
        QString line;
        line.append(it.key().getName());
        line.append(it.key().getColor()->name());
        line.append(it.key().getParent()->getTagGroupName());
        for(int i = 0; i < it->size(); i++){
            line.append(it->at(i)->fileName());
        }
        std::cout<<line.toStdString()<<std::endl;
        outf<<line<<endl;
    }
    tagFile->close();

    for(auto it = tagGroupHash.begin(); it != tagGroupHash.end(); it++){
        QString line;
        line.append(it.key());
        std::cout<<line.toStdString()<<std::endl;
        outgf<<line<<endl;
    }
    tagGroupFile->close();
}
