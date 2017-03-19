#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QStandardItemModel>
#include "pathhistory.h"
#include "tagmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_dirView_clicked(const QModelIndex &index);

    void on_filesView_doubleClicked(const QModelIndex &index);

    void on_searchBar_textChanged(const QString &arg1);

    void on_backButton_clicked();

    void on_forwardButton_clicked();

    void on_tagView_clicked(const QModelIndex &index);

    void handleClick();

private:
    Ui::MainWindow *ui;
    QFileSystemModel* dirModel;
    QFileSystemModel* fileModel;
    PathHistory* history;
    TagManager* tagManager;
    QStandardItemModel* model;
};

#endif // MAINWINDOW_H
