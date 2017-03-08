#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QUrl>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dirModel = new QFileSystemModel(this);
    fileModel = new QFileSystemModel(this);
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

    QSize grid_size(100,100);
    QSize icon_size(64,64);
    QModelIndex findex = fileModel->index(rootPath);
    ui->filesView->setModel(fileModel);

    ui->filesView->setViewMode(QListView::IconMode);
    ui->filesView->setGridSize(grid_size);
    ui->filesView->setResizeMode(QListView::Adjust);
    ui->filesView->setIconSize(icon_size);
    ui->filesView->setRootIndex(findex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dirView_clicked(const QModelIndex &index)
{
    QString path = dirModel->fileInfo(index).absoluteFilePath();
    ui->filesView->setRootIndex(fileModel->setRootPath(path));
}

void MainWindow::on_filesView_doubleClicked(const QModelIndex &index)
{
    QFileInfo file = fileModel->fileInfo(index);

    if (file.isDir() && !file.absoluteFilePath().contains(".app",Qt::CaseInsensitive)) {
        ui->filesView->setRootIndex(fileModel->setRootPath(file.absoluteFilePath()));
    } else if (file.isSymLink()) {
      std::cout << file.symLinkTarget().toStdString() << std::endl;
      ui->filesView->setRootIndex(fileModel->setRootPath(file.symLinkTarget()));
    } else {
        QString fileUrl = "file://"+file.absoluteFilePath();
        std::cout << QDesktopServices::openUrl(QUrl(fileUrl)) << std::endl;
    }
}

