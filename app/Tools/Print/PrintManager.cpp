#include "PrintManager.h"
#include <QDebug>

PrintManager::PrintManager()
{
    setEngine(new PrintEngine());
    setOwnerService(new OwnerService());
    setNumberToWords(new NumberToWords());
    setPreferences(new SettingsPreferencesService());
}

void PrintManager::priceType()
{
    if(!getPreferences()->getPriceConversion())
        getEngine()->setPriceOption("netto",true);
    else
        getEngine()->setPriceOption("brutto",false);
}

PrintEngine* PrintManager::getEngine(){return engine;}
void PrintManager::setEngine(PrintEngine* engine){this->engine=engine;}
SettingsPreferencesService* PrintManager::getPreferences(){return preferences;}
void PrintManager::setPreferences(SettingsPreferencesService* preferences){this->preferences=preferences;}
NumberToWords* PrintManager::getNumberToWords(){return ntw;}
void PrintManager::setNumberToWords(NumberToWords* ntw){this->ntw=ntw;}
OwnerService* PrintManager::getOwnerService(){return ownerService;}
void PrintManager::setOwnerService(OwnerService *ownerService){this->ownerService=ownerService;}
