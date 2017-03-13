#ifndef PATHHISTORY_H
#define PATHHISTORY_H

#include <QVector>
#include <QString>

class PathHistory
{
public:
    PathHistory();

    void add(QString path);
    QString back();
    QString next();

private:
    QVector<QString>* history;
    int index;
};

#endif // PATHHISTORY_H
