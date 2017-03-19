#ifndef NEWTAGFRAME_H
#define NEWTAGFRAME_H

#include <QFrame>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QRect>
#include <QListView>

class NewTagFrame : public QFrame
{
    Q_OBJECT

public:
    NewTagFrame(QStandardItemModel* model, QRect* window, QWidget* parent = 0);

public slots:
    void buildTag();

    void disableNewGroup(QModelIndex i);
    void enableNewGroup();
private:
    QStandardItemModel* model;
    QRect* window;
    QLineEdit* tmpE;
    QLineEdit* grName;
    QListView* groups;
};

#endif // NEWTAGFRAME_H
