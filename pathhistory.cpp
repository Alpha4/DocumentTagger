#include "pathhistory.h"

#include <QVector>
#include <QString>
#include <iostream>

PathHistory::PathHistory()
{
    this->history = new QVector<QString>();
    this->index = -1;
}

void PathHistory::add(QString path) {
    std::cout << "ADD " << index << " | " << history->size() << std::endl;
    if (index != history->size()-1) {
        for(int i = index; i< history->size(); i++){
            std::cout << "removed from history : "<< history->at(i).toStdString() << std::endl;
            history->removeLast();
        }
    }
    history->append(path);
    index++;
}

QString PathHistory::back() {
    std::cout<< "BACK " << index << " | " << history->size() << std::endl;
    if (index > 0)
        return history->at(--index);
    return history->at(index);
}

QString PathHistory::next() {
    std::cout <<"NEXT "<< index << " | " << history->size() << std::endl;
    if (index < history->size() - 1)
        return history->at(++index);
    return history->at(index);
}
