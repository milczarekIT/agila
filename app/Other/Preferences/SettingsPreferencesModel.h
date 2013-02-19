#ifndef SETTINGSPREFERENCESMODEL_H
#define SETTINGSPREFERENCESMODEL_H

#include <QString>
#include "Database/Model.h"


class SettingsPreferencesModel : public Model
{
    void insertValue(QString name, QString value);
    void updateValue(QString name, QString value);

    QVariant getValue(QString name);
    void setValue(QString name, QString value);
public:
    SettingsPreferencesModel();

    int getDefaultPrintAction();
    void setDefaultPrintAction(int action);

    int getDefaultPrintNumberOfCopies();
    void setDefaultPrintNumberOfCopies(int number);

    double getDefaultGoodsMargin();
    void setDefaultGoodsMargin(double margin);

    double getDefaultGoodsDiscountB();
    void setDefaultGoodsDiscountB(double discount);


    double getDefaultGoodsDiscountC();
    void setDefaultGoodsDiscountC(double discount);


    int getPriceConversion();
    void setPriceConversion(int action);


    int getTaxIdForRR();
    void setTaxIdForRR(int idTax);

};

#endif // SETTINGSPREFERENCESMODEL_H
