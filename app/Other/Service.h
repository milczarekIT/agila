#ifndef SERVICE_H
#define SERVICE_H

#include <QDebug>
#include "Other/Exceptions/Exception.h"
#include "Components/MessageBox.h"

class Service
{
protected:
    void showErrorInfo(Exception *e);
public:
    Service();


};

#endif // SERVICE_H
