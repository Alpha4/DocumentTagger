#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QLabel>
#include <iostream>
#include <tagitemdelegate.h>
#include "tagviewdelegate.h"
#include "tagmanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dirModel = new QFileSystemModel(this);
    fileModel = new QFileSystemModel(this);
    history = new PathHistory();

    //set dirModel to dirView
    QString rootPath = QDir::homePath();
    dirModel->setRootPath(rootPath);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    QModelIndex index = dirModel->index(rootPath);
    ui->dirView->setModel(dirModel);
    ui->dirView->setRootIndex(index);
    ui->dirView->hideColumn(1);//hide size
    ui->dirView->hideColumn(2);//hide type
    ui->dirView->hideColumn(3);//hide date modif

    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
    fileModel->setRootPath(rootPath);
    fileModel->setNameFilterDisables(false);
    history->add(rootPath);

    QSize grid_size(100,100);
    QSize icon_size(64,64);
    QModelIndex findex = fileModel->index(rootPath);
    ui->filesView->setModel(fileModel);
    ui->filesView->setItemDelegate(new TagItemDelegate());

    ui->filesView->setViewMode(QListView::IconMode);
    ui->filesView->setGridSize(grid_size);
    ui->filesView->setResizeMode(QListView::Adjust);
    ui->filesView->setIconSize(icon_size);
    ui->filesView->setRootIndex(findex);

    QFile* tagGroupFile = new QFile("/home/andrei/Documents/Work/qt/DocumentTagger/tagGroups.txt");
    QFile* tagFile = new QFile("/home/andrei/Documents/Work/qt/DocumentTagger/tags.txt");
    tagManager = new TagManager(tagFile,tagGroupFile);
    tagManager->fillHashTable();
    model = tagManager->createModel();

    ui->tagView->setModel(model);
    ui->tagView->setItemDelegate(new TagViewDelegate(this));

    QPushButton* createTagButton = new QPushButton("New Tag");
    ui->leftSplitter->insertWidget(0,createTagButton);
    connect(createTagButton,SIGNAL(clicked(bool)),this,SLOT(handleClick()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleClick(){
    QRect rect = this->rect();
    NewTagFrame* popup = new NewTagFrame(model,&rect,this);
    popup->show();
}

/*
void MainWindow::handleClick(){

    popup1 = new QFrame(this, Qt::Popup | Qt::Window );

    popup1->resize(300,400);
    QRect window = this->rect();
    QPoint middleWindow(window.x()+window.width()/2 - 150,window.y()+window.height()/2 - 200);
    popup1->move( mapToGlobal( middleWindow ) );
    QLabel* dialogLabel = new QLabel("New Tag Box");
    dialogLabel->setAlignment(Qt::AlignCenter);
    QVBoxLayout* dialogLayout = new QVBoxLayout(popup1);
    QHBoxLayout* textLayout = new QHBoxLayout(popup1);
    QVBoxLayout* groupLayout = new QVBoxLayout(popup1);

    tmpE = new QLineEdit( popup1 );
    QLabel* textLabel = new QLabel("Enter Tag Name: ");
    textLayout->insertWidget(0,textLabel);
    textLayout->insertWidget(1,tmpE);

    QPushButton* confirm = new QPushButton("OK",popup1);
    groups = new QListView(popup1);
    groups->setModel(model);
    groups->setViewMode(QListView::IconMode);
    QLabel* groupLabel = new QLabel("Choose a group: ");
    groupLayout->insertWidget(0,groupLabel);
    groupLayout->insertWidget(1,groups);


    dialogLayout->insertWidget(0,dialogLabel);
    dialogLayout->insertLayout(1,textLayout);
    dialogLayout->insertLayout(2,groupLayout);
    dialogLayout->insertWidget(3,confirm);
    connect(confirm,SIGNAL(clicked(bool)),popup1,SLOT(this->buildTag()));
    //connect( tmpE, SIGNAL( returnPressed() ), popup1, SLOT( hide() ) );
    tmpE->setGeometry(10,10, 130, 30);
    tmpE->setFocus();
    popup1->show();
}
*/

void MainWindow::on_dirView_clicked(const QModelIndex &index)
{
    QString path = dirModel->fileInfo(index).absoluteFilePath();
    ui->filesView->setRootIndex(fileModel->setRootPath(path));
    history->add(path);
}

void MainWindow::on_filesView_doubleClicked(const QModelIndex &index)
{
    QFileInfo file = fileModel->fileInfo(index);

    if (file.isDir() && !file.absoluteFilePath().contains(".app",Qt::CaseInsensitive)) {
        ui->filesView->setRootIndex(fileModel->setRootPath(file.absoluteFilePath()));
        history->add(file.absoluteFilePath());
    } else if (file.isSymLink()) {
        ui->filesView->setRootIndex(fileModel->setRootPath(file.symLinkTarget()));
        history->add(file.symLinkTarget());
    } else {
        QString fileUrl = "file://"+file.absoluteFilePath();
        std::cout << QDesktopServices::openUrl(QUrl(fileUrl)) << std::endl;
    }
}


void MainWindow::on_searchBar_textChanged(const QString &arg1)
{
    QStringList keywords;
    fileModel->setNameFilters(keywords);
    if (arg1!="")
        keywords << "*"+arg1+"*";
    fileModel->setNameFilters(keywords);
}

void MainWindow::on_backButton_clicked()
{
    ui->filesView->setRootIndex((fileModel->setRootPath(history->back())));
}

void MainWindow::on_forwardButton_clicked()
{
    ui->filesView->setRootIndex((fileModel->setRootPath(history->next())));
}

void MainWindow::on_tagView_clicked(const QModelIndex &index)
{
    std::cout<<index.column()<<std::endl;
    std::cout<<index.row()<<std::endl;
    if(index.parent().data().isNull()){
        std::cout<<"root"<<std::endl;
    }else{
        std::cout<<index.parent().data().toString().toStdString()<<std::endl;
    }
}
