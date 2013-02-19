#ifndef SIMPLESTRUCTURE_H
#define SIMPLESTRUCTURE_H

#include <QString>

/**
  * Prosta struktura posiadająca id oraz name
  * @author Bartosz Milczarek
  */
class SimpleStructure
{
protected:
    int id;
    QString name;
public:
    SimpleStructure();
    SimpleStructure(int id, QString name);

    void setId(int id);
    void setName(QString name);

    int getId();
    QString getName();

    int operator ==(SimpleStructure ss);
};

#endif // SIMPLESTRUCTURE_H
