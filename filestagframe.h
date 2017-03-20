#ifndef FILESTAGFRAME_H
#define FILESTAGFRAME_H

#include <QFrame>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QStandardItemModel>
#include "tagmanager.h"

class FilesTagFrame : public QFrame
{
    Q_OBJECT

public:
    FilesTagFrame(TagManager* tagManager, QString path, QWidget* parent = 0);
public slots:
    void updateModel(QString str);
    void hideButton();
    void associateTag();

    void saveModel();
signals:
    void end();
private:
    TagManager* tagManager;
    QString path;
    QListView* tagNotAddedView;
    QLineEdit* searchTag;
    QListView* tagAddedView;
    QStandardItemModel *model,*filteredModel;
    QPushButton* associate;

};

#endif // FILESTAGFRAME_H
