#ifndef TAX_H
#define TAX_H

#include <QString>
#include "Other/SimpleStructure.h"

class Tax : public SimpleStructure
{
private:
    float value;
    QString shortName;
    bool activeInApp;
public:
    Tax();

    void setValue(float value);
    void setShortName(QString letter);
    void setActiveInApp(bool activeInApp);

    float getValue();
    QString getShortName();
    bool isActiveInApp();

    int operator ==(Tax t);

};

#endif // TAX_H

