#ifndef DOCUMENTINFO_H
#define DOCUMENTINFO_H

#include <QString>
#include "Other/SimpleStringStructure.h"

class DocumentInfo
{
private:
    QString type;
    QString name;
    QString numbering;
    QString afterText;
    SimpleStringStructure family;
public:
    DocumentInfo();

    void setType(QString type);
    void setName(QString name);
    void setNumbering(QString numbering);
    void setAfterText(QString afterText);
    void setFamily(SimpleStringStructure family);

    QString getType();
    QString getName();
    QString getNumbering();
    QString getAfterText();
    SimpleStringStructure getFamily();
};

#endif // DOCUMENTINFO_H
