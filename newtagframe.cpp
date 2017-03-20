#include "newtagframe.h"
#include <QListView>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStandardItemModel>
#include <QToolButton>
#include <QColor>
#include <QColorDialog>
#include <QButtonGroup>
#include <iostream>

NewTagFrame::NewTagFrame(QStandardItemModel* model,
                         QRect* window,
                         TagManager* tagManager,
                         QWidget *parent):
    QFrame(parent, Qt::Popup | Qt::Window),
    model(model),
    window(window),
    tagManager(tagManager)
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
    QHBoxLayout* colorLayout = new QHBoxLayout(this);

    grName = new QLineEdit(this);
    QPushButton* pbutton = new QPushButton(this);
    pbutton->setText("Clear Selection");

    /*
    QPushButton* colorButton = new QPushButton("Color",this);
    colorLabel = new QLabel(this);
    QColor defaultColor(Qt::darkRed);
    colorLabel->setText(defaultColor.name());
    colorLabel->setPalette(QPalette(defaultColor));
    colorLabel->setAutoFillBackground(true);
*/
    color = new QColor(Qt::red);//default color
    red = new QPushButton(this);
    red->setPalette(QPalette(Qt::red));
    red->autoFillBackground();
    blue = new QPushButton(this);
    blue->setPalette(QPalette(Qt::blue));
    blue->autoFillBackground();
    green = new QPushButton(this);
    green->setPalette(QPalette(Qt::green));
    green->autoFillBackground();
    yellow = new QPushButton(this);
    yellow->setPalette(QPalette(Qt::yellow));
    yellow->autoFillBackground();
    gray = new QPushButton(this);
    gray->setPalette(QPalette(Qt::gray));
    gray->autoFillBackground();
    cyan = new QPushButton(this);
    cyan->setPalette(QPalette(Qt::cyan));
    cyan->autoFillBackground();

    colorLayout->insertWidget(0,red);
    colorLayout->insertWidget(1,blue);
    colorLayout->insertWidget(2,cyan);
    colorLayout->insertWidget(3,yellow);
    colorLayout->insertWidget(4,green);
    colorLayout->insertWidget(5,gray);


    tmpE = new QLineEdit( this );
    QLabel* textLabel = new QLabel("Enter Tag Name: ");
    QLabel* grNameLabel = new QLabel("Enter Tag Group Name: ");
    textLayout->insertWidget(0,textLabel);
    textLayout->insertWidget(1,tmpE);
    grNameLayout->insertWidget(0,grNameLabel);
    grNameLayout->insertWidget(1,grName);
    //colorLayout->insertWidget(1,colorButton);
    //colorLayout->insertWidget(0,bg);

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
    dialogLayout->insertLayout(2,colorLayout);
    dialogLayout->insertLayout(3,groupLayout);
    dialogLayout->insertLayout(4,grNameLayout);
    dialogLayout->insertWidget(5,confirm);

    tmpE->setGeometry(10,10, 130, 30);
    tmpE->setFocus();

    connect(confirm,SIGNAL(clicked(bool)),this,SLOT(buildTag()));
    connect(groups,SIGNAL(clicked(QModelIndex)),this,SLOT(disableNewGroup(QModelIndex)));
    connect(pbutton,SIGNAL(clicked(bool)),this,SLOT(enableNewGroup()));
    connect(red,SIGNAL(clicked(bool)),this,SLOT(setRed()));
    connect(blue,SIGNAL(clicked(bool)),this,SLOT(setBlue()));
    connect(green,SIGNAL(clicked(bool)),this,SLOT(setGreen()));
    connect(yellow,SIGNAL(clicked(bool)),this,SLOT(setYellow()));
    connect(gray,SIGNAL(clicked(bool)),this,SLOT(setGray()));
    connect(cyan,SIGNAL(clicked(bool)),this,SLOT(setCyan()));
}

void NewTagFrame::setRed(){
    color = new QColor(Qt::red);
    red->setText("X");
    blue->setText("");
    green->setText("");
    yellow->setText("");
    cyan->setText("");
    gray->setText("");
}
void NewTagFrame::setBlue(){
    color = new QColor(Qt::blue);
    red->setText("");
    blue->setText("X");
    green->setText("");
    yellow->setText("");
    cyan->setText("");
    gray->setText("");
}

void NewTagFrame::setGreen(){
    color = new QColor(Qt::green);
    red->setText("");
    blue->setText("");
    green->setText("X");
    yellow->setText("");
    cyan->setText("");
    gray->setText("");
}

void NewTagFrame::setCyan(){
    color = new QColor(Qt::cyan);
    red->setText("");
    blue->setText("");
    green->setText("");
    yellow->setText("");
    cyan->setText("X");
    gray->setText("");
}

void NewTagFrame::setYellow(){
    color = new QColor(Qt::yellow);
    red->setText("");
    blue->setText("");
    green->setText("");
    yellow->setText("X");
    cyan->setText("");
    gray->setText("");
}

void NewTagFrame::setGray(){
    color = new QColor(Qt::gray);
    red->setText("");
    blue->setText("");
    green->setText("");
    yellow->setText("");
    cyan->setText("");
    gray->setText("X");
}


/*
void NewTagFrame::setColor()
{
    QColor color;
    color = QColorDialog::getColor(Qt::green, this);
    //color = QColorDialog::getColor(Qt::green, this, "Select Color", QColorDialog::DontUseNativeDialog);

    if (color.isValid()) {
        colorLabel->setText(color.name());
        colorLabel->setPalette(QPalette(color));
        colorLabel->setAutoFillBackground(true);
    }
}
*/

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
    QString tagGroupName;
    QModelIndexList selected = groups->selectionModel()->selectedIndexes();
    if(selected.isEmpty()){
        //std::cout<<"No group selected"<<std::endl;
        tagGroupName = grName->text();
    }else{
        tagGroupName = selected[0].data().toString();
        //std::cout<<"selected: "<<gr.toStdString()<<std::endl;
    }
    std::cout<<"hello"<<std::endl;
    std::cout<<color->name().toStdString()<<std::endl;


}
