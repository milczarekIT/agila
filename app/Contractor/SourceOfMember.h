#ifndef SOURCEOFMEMBER_H
#define SOURCEOFMEMBER_H

#include <QString>
#include <QVariant>
#include "Other/SimpleStructure.h"

class SourceOfMember : public SimpleStructure
{
public:
    QString toString();

    int operator ==(SourceOfMember som);
};

#endif // SOURCEOFMEMBER_H
