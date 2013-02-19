#ifndef MOPMODEL_H
#define MOPMODEL_H

#include "Database/Model.h"
#include "Document/MethodOfPayment.h"

class MOPModel : public Model
{
public:
    MOPModel();
    ~MOPModel();

    QVector<MethodOfPayment> getMethodsOfPayment();
    void getMethodsOfPaymentModel();
    MethodOfPayment getMethodOfPayment(int id);
    void addMethodOfPayment(MethodOfPayment mop);
    void editMethodOfPayment(MethodOfPayment mop);
    void removeMethodOfPayment(int id);
};

#endif // MOPMODEL_H
