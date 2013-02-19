#ifndef SETTINGSPREFERENCESSERVICE_H
#define SETTINGSPREFERENCESSERVICE_H

#include "Other/Service.h"
#include "SettingsPreferencesModel.h"

class SettingsPreferencesService : public Service
{
    SettingsPreferencesModel *model;
public:
    SettingsPreferencesService();
    ~SettingsPreferencesService();

    /**
      * Zwraca jedną z wartości: SettingsPreference::PRINT_ACTION_PRINT_AND_PDF, SettingsPreference::PRINT_ACTION_PRINT_ONLY, SettingsPreference::PRINT_ACTION_PDF_ONLY;
      */
    int getDefaultPrintAction();
    void setDefaultPrintAction(int action);

    /**
      * Zwraca domyślną liczbę kopii jaka ma być drukowana (dot. wszystkich dokumentów)
      */
    int getDefaultPrintNumberOfCopies();
    void setDefaultPrintNumberOfCopies(int number);

    /**
      * Zwraca domyślny narzut dla towarów (tzn. w procentach narzut dla ceny A od ceny zakupu
      */
    double getDefaultGoodsMargin();
    void setDefaultGoodsMargin(double margin);

    /**
      * Zwraca domyślny upust dla towarów dla ceny B (upust liczony od ceny A)
      */
    double getDefaultGoodsDiscountB();
    void setDefaultGoodsDiscountB(double discount);

    /**
      * Zwraca domyślny upust dla towarów dla ceny C (upust liczony od ceny A)
      */
    double getDefaultGoodsDiscountC();
    void setDefaultGoodsDiscountC(double discount);
    /**
      * Zwraca rodzaj ceny w jakiej wystawiane sa faktury
      */
    int getPriceConversion();
    void setPriceConversion(int type);
    /**
      *Id tax wybrany przez użytkownika dla Faktury Rolnik Ryczałtowy
      */
    int getTaxIdForRR();
    void setTaxIdForRR(int idTax);
};

#endif // SETTINGSPREFERENCESSERVICE_H
