#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QUrl>
#include <iostream>
#include <tagitemdelegate.h>

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

}

MainWindow::~MainWindow()
{
    delete ui;
}

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
