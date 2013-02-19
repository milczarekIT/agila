#ifndef FEATURE_H
#define FEATURE_H

#include <QString>

class Feature
{
    int id;
    QString name;
    QString value; // for Good
public:
    Feature();
    Feature (int id, QString value);

    void setId(int id);
    void setName(QString name);
    void setValue(QString value);

    int getId();
    QString getName();
    QString getValue();

    int operator==(Feature f);
};

#endif // FEATURE_H
