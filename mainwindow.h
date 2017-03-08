#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>

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

private:
    Ui::MainWindow *ui;
    QFileSystemModel* dirModel;
    QFileSystemModel* fileModel;
};

#endif // MAINWINDOW_H
