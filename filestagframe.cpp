#include "filestagframe.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QListView>
#include <iostream>

FilesTagFrame::FilesTagFrame(TagManager *tagManager,
                             QString path,
                             QWidget *parent):
    QFrame(parent, Qt::Popup | Qt::Window),
    tagManager(tagManager),
    path(path)
{
    this->resize(400,300);
    QPoint encore(200,200);
    this->move(parent->window()->frameGeometry().topLeft() +
               parent->window()->rect().center() - rect().center());

    model = tagManager->createOnlyListModel();
    //std::cout<<index->data().toString().toStdString()<<std::endl;
    //file = index->data().toString();
    filteredModel = tagManager->createFilteredModel(path);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    QVBoxLayout* addTagLayout = new QVBoxLayout(this);

    searchTag = new QLineEdit(this);
    tagNotAddedView = new QListView(this);
    tagAddedView = new QListView(this);
    associate = new QPushButton();
    associate->setText("Add Tag To File");
    associate->setDisabled(1);

    QLabel* searchLabel = new QLabel("Search Tag",this);
    QHBoxLayout* searchLayout = new QHBoxLayout(this);

    QLabel* listLabel = new QLabel("Current Tags:",this);
    QVBoxLayout* tagLayout = new QVBoxLayout(this);

    searchLayout->insertWidget(0,searchLabel);
    searchLayout->insertWidget(1,searchTag);

    tagLayout->insertWidget(0,listLabel);
    tagLayout->insertWidget(1,tagAddedView);

    tagNotAddedView->setModel(model);
    tagAddedView->setModel(filteredModel);

    addTagLayout->insertLayout(0,searchLayout);
    addTagLayout->insertWidget(1,tagNotAddedView);
    addTagLayout->insertWidget(2,associate);

    mainLayout->insertLayout(0,addTagLayout);
    mainLayout->insertLayout(1,tagLayout);

    connect(searchTag,SIGNAL(textChanged(QString)),this,SLOT(updateModel(QString)));
    connect(tagNotAddedView,SIGNAL(clicked(QModelIndex)),this,SLOT(hideButton()));
    connect(associate,SIGNAL(clicked(bool)),this,SLOT(associateTag()));
    connect(this,SIGNAL(end()),this,SLOT(saveModel()));
}

void FilesTagFrame::saveModel(){
    std::cout<<"INSIDE SAVEMODEL SLOT!!!!!!"<<std::endl;
    tagManager->saveHashTable();
    //this->hide();
}

void FilesTagFrame::associateTag(){
    QModelIndexList selected = tagNotAddedView->selectionModel()->selectedIndexes();
    QString d = selected[0].data().toString();
    QList<Tag> tags = tagManager->getKeys();
    //std::cout<<"number of elem: "<<tags.size()<<std::endl;
    //tagManager->addFile(tags[0],"hello");
    //std::cout<<"index = "<<file.toStdString()<<std::endl;
    //std::cout<<"error???"<<std::endl;
    //std::cout<<"d = "<<d.toStdString()<<std::endl;
    for(int i = 0; i<tags.size(); i++){
        //std::cout<<tags[i].getName().toStdString()<<std::endl;
        if(tags[i].getName() == d){
            //std::cout<<"equalité"<<std::endl;
            tagManager->addFile(tags[i],path);
            break;
        }
    }
    //std::cout<<"before creation model"<<std::endl;
    filteredModel = tagManager->createFilteredModel(path);
    tagAddedView->setModel(filteredModel);

    emit end();

}

void FilesTagFrame::hideButton(){
    QModelIndexList selected = tagNotAddedView->selectionModel()->selectedIndexes();
    if(selected.isEmpty()){
        associate->setDisabled(1);
    }else{
        associate->setEnabled(1);
    }
}

void FilesTagFrame::updateModel(QString str){
    if(str==""){
        //associate->setDisabled(1);
        tagNotAddedView->setModel(model);
    }else{
        associate->setDisabled(1);
        QList<Tag> keys = tagManager->getKeys();
        QList<Tag> filtered;
        for(int i = 0; i<keys.size(); i++){
            if(keys[i].getName().contains(str)){
                filtered.append(keys[i]);
            }
        }
        QStandardItemModel* upModel = new QStandardItemModel();
        QStandardItem* parent = upModel->invisibleRootItem();
        for(int i = 0; i< filtered.size(); i++){
            QStandardItem* item = new QStandardItem(filtered[i].getName());
            parent->appendRow(item);
        }

        tagNotAddedView->setModel(upModel);
        //tagManager->saveHashTable();
    }
}
