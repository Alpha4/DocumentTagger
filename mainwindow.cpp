#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dirModel = new QFileSystemModel(this);
    fileModel = new QFileSystemModel(this);
    //std::cout<<QDir::homePath().toStdString()<<std::endl;
    QString rootPath = QDir::homePath();
    dirModel->setRootPath(rootPath);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    QModelIndex index = dirModel->index(rootPath);
    ui->dirView->setModel(dirModel);
    ui->dirView->setRootIndex(index);
    ui->dirView->hideColumn(1);
    ui->dirView->hideColumn(2);
    ui->dirView->hideColumn(3);
}

MainWindow::~MainWindow()
{
    delete ui;
}
