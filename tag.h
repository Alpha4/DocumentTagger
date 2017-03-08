#ifndef TAG_H
#define TAG_H

#include <QString>
#include <QColor>
#include "taggroup.h"

class Tag
{
public:
    Tag(TagGroup& parent);
    Tag(TagGroup& parent, QString name);
    Tag(TagGroup &parent, QString name, QColor& color);
    void setColor(QColor& color);
    QColor& getColor();
    void setName(QString name);
    QString getName();
    void setParent(TagGroup& parent);
    TagGroup& getParent();

private:
    QString name;
    TagGroup& parent;
    QColor& color;
};

#endif // TAG_H
