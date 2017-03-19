#include "newtagframe.h"
#include <QListView>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStandardItemModel>
#include <QToolButton>
#include <iostream>

NewTagFrame::NewTagFrame(QStandardItemModel* model,
                         QRect* window,
                         QWidget *parent):
    QFrame(parent, Qt::Popup | Qt::Window ),
    model(model),
    window(window)
{
    this->resize(300,400);
    QPoint middleWindow(window->x()+window->width()/2 - 150,window->y()+window->height()/2 - 200);
    this->move( mapToParent( middleWindow ) );
    QLabel* dialogLabel = new QLabel("New Tag Box");
    dialogLabel->setAlignment(Qt::AlignCenter);
    QVBoxLayout* dialogLayout = new QVBoxLayout(this);
    QHBoxLayout* textLayout = new QHBoxLayout(this);
    QHBoxLayout* grNameLayout = new QHBoxLayout(this);
    QVBoxLayout* groupLayout = new QVBoxLayout(this);
    QHBoxLayout* gtlayout = new QHBoxLayout(this);
    grName = new QLineEdit(this);
    QPushButton* pbutton = new QPushButton(this);
    pbutton->setText("Clear Selection");

    tmpE = new QLineEdit( this );
    QLabel* textLabel = new QLabel("Enter Tag Name: ");
    QLabel* grNameLabel = new QLabel("Enter Tag Group Name: ");
    textLayout->insertWidget(0,textLabel);
    textLayout->insertWidget(1,tmpE);
    grNameLayout->insertWidget(0,grNameLabel);
    grNameLayout->insertWidget(1,grName);

    QPushButton* confirm = new QPushButton("OK",this);
    groups = new QListView(this);
    groups->setModel(model);
    groups->setViewMode(QListView::IconMode);
    QLabel* groupLabel = new QLabel("Choose a group: ");
    gtlayout->insertWidget(0,groupLabel);
    gtlayout->insertWidget(1,pbutton);
    groupLayout->insertLayout(0,gtlayout);
    groupLayout->insertWidget(1,groups);


    dialogLayout->insertWidget(0,dialogLabel);
    dialogLayout->insertLayout(1,textLayout);
    dialogLayout->insertLayout(2,groupLayout);
    dialogLayout->insertLayout(3,grNameLayout);
    dialogLayout->insertWidget(4,confirm);

    tmpE->setGeometry(10,10, 130, 30);
    tmpE->setFocus();

    connect(confirm,SIGNAL(clicked(bool)),this,SLOT(buildTag()));
    connect(groups,SIGNAL(clicked(QModelIndex)),this,SLOT(disableNewGroup(QModelIndex)));
    connect(pbutton,SIGNAL(clicked(bool)),this,SLOT(enableNewGroup()));
}

void NewTagFrame::enableNewGroup(){
    groups->clearSelection();
    grName->setEnabled(1);
}

void NewTagFrame::disableNewGroup(QModelIndex i){
    if(i.data().toString() != "")
        grName->setDisabled(1);
}

void NewTagFrame::buildTag()
{
    //std::cout<<tmpE->text().toStdString()<<std::endl;
    QString name = tmpE->text();
    QModelIndexList selected = groups->selectionModel()->selectedIndexes();
    if(selected.isEmpty()){
        //std::cout<<"No group selected"<<std::endl;
    }else{
        QString gr = selected[0].data().toString();
        //std::cout<<"selected: "<<gr.toStdString()<<std::endl;
    }


}
