#ifndef TRANSPORTMODEL_H
#define TRANSPORTMODEL_H

#include "Database/Model.h"
#include "Document/DocumentModel.h"

class TransportModel : public Model
{
public:
    TransportModel();

    QVector<SimpleStructure> getMeansOfTransport();
    SimpleStructure getMeanOfTransport(int id);
    void addMeanOfTransport(SimpleStructure transport);
    void editMeanOfTransport(SimpleStructure transport);
    void removeMeanOfTransport(int id);

};

#endif // TRANSPORTMODEL_H
