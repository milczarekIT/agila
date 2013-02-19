#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

#include "Database/Model.h"
#include "Document/DocumentModel.h"
#include "Document/MethodOfPayment.h"
#include "Goods/Unit.h"
#include "Contractor/SourceOfMember.h"
#include "Goods/Tax.h"
#include "Contractor/ContractorGroup.h"
#include "Goods/GoodsGroup.h"
#include "Goods/Feature.h"

class SettingsModel : public Model
{
public:
    SettingsModel();
    ~SettingsModel();

    // default document place
    void setDefaultDocumentPlace(QString name);
    SimpleStructure getDefualtDocumentPlace();

};

#endif // SETTINGSMODEL_H



