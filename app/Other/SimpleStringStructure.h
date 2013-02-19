#ifndef SIMPLESTRINGSTRUCTURE_H
#define SIMPLESTRINGSTRUCTURE_H

#include <QString>

class SimpleStringStructure
{
    QString id;
    QString name;
public:
    SimpleStringStructure();

    void setId(QString id);
    void setName(QString name);

    QString getId();
    QString getName();
};

#endif // SIMPLESTRINGSTRUCTURE_H
