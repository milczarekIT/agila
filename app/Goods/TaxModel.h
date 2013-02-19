#ifndef TAXMODEL_H
#define TAXMODEL_H

#include "Database/Model.h"
#include "Goods/Tax.h"

class TaxModel : public Model
{
public:
    TaxModel();
    ~TaxModel();

    QVector<Tax> getTaxes(bool onlyActiveInApp);
    Tax getTax(int id);
    void addTax(Tax t);
    void editTax(Tax t);
    void removeTax(int id);
};

#endif // TAXMODEL_H
