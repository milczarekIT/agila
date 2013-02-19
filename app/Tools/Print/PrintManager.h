#ifndef PRINTMANAGER_H
#define PRINTMANAGER_H

#include <QFile>
#include <QDomDocument>
#include "PrintEngine.h"
#include "Document/SaleDocument/Invoice.h"
#include "Document/StoreDocument/StoreDocument.h"
#include "Document/StoreDocument/DocumentWZ.h"
#include "Document/StoreDocument/DocumentPZ.h"
#include "Document/SaleDocument/DocumentFK.h"
#include "Document/SaleDocument/DocumentZAL.h"
#include "Document/PurchaseDocument/DocumentNK.h"
#include "Tools/Print/NumberToWords.h"
#include "Other/Owner/Owner.h"
#include "Other/Preferences/SettingsPreferencesService.h"

class PrintEngine;

class PrintManager
{

private:
    PrintEngine *engine;
    SettingsPreferencesService* preferences;
    OwnerService *ownerService;
    NumberToWords *ntw;

public:
   PrintManager();
   void priceType();

   /**
     *Gettery i settery
     *
     **/

   PrintEngine*getEngine();
   void setEngine(PrintEngine* engine);
   SettingsPreferencesService* getPreferences();
   void setPreferences(SettingsPreferencesService *preferences);
   NumberToWords* getNumberToWords();
   void setNumberToWords(NumberToWords* ntw);
   OwnerService* getOwnerService();
   void setOwnerService(OwnerService* ownerService);
};

#endif // PRINTMANAGER_H
