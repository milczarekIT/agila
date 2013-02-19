#ifndef SOMMODEL_H
#define SOMMODEL_H

#include "Database/Model.h"
#include "Contractor/SourceOfMember.h"

class SOMModel : public Model
{
public:
    SOMModel();
    ~SOMModel();

    QVector<SourceOfMember> getSourcesOfMember();
    SourceOfMember getSourceOfMember(int id);
    void addSourceOfMember(SourceOfMember som);
    void editSourceOfMember(SourceOfMember som);
    void removeSourceOfMember(int som);
};

#endif // SOMMODEL_H
