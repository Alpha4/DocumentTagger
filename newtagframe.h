#ifndef NEWTAGFRAME_H
#define NEWTAGFRAME_H

#include <QFrame>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QRect>
#include <QListView>
#include <QColor>
#include <QPushButton>
#include <tagmanager.h>

class NewTagFrame : public QFrame
{
    Q_OBJECT

public:
    NewTagFrame(QStandardItemModel* model, QRect* window, TagManager *tagManager, QWidget* parent = 0);

public slots:
    void buildTag();

    void disableNewGroup(QModelIndex i);
    void enableNewGroup();
    //void setColor();
    void setRed();
    void setBlue();
    void setGreen();
    void setCyan();
    void setYellow();
    void setGray();
private:
    QStandardItemModel* model;
    QRect* window;
    QLineEdit* tmpE;
    QLineEdit* grName;
    QListView* groups;
    TagManager* tagManager;
    QColor* color;
    QPushButton *red,*blue,*green,*yellow,*cyan,*gray;
};

#endif // NEWTAGFRAME_H
