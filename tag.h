#ifndef TAG_H
#define TAG_H

#include <QString>
#include <QColor>
#include "taggroup.h"

class TagGroup;
class Tag
{
public:
    Tag(TagGroup* parent, QString name, QColor* color);

    void setColor(QColor* color);
    QColor* getColor() const;
    void setName(QString name);
    QString getName() const;
    void setParent(TagGroup* parent);
    TagGroup* getParent() const;
    bool operator==(const Tag& other) const;

private:
    TagGroup* parent;
    QString name;
    QColor* color;
};

inline uint qHash(const Tag &tag, uint seed) {
    return qHash(tag.getName(), seed);
}

#endif // TAG_H
