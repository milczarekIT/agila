#ifndef SETTINGSMASSTAXESCHANGECONTROLLER_H
#define SETTINGSMASSTAXESCHANGECONTROLLER_H

#include <QObject>
#include "Goods/TaxModel.h"
#include "Goods/GoodsGroupModel.h"
#include "SettingsMassTaxesChangeView.h"
#include "Tools/TaxChanger/TaxChangerModel.h"
#include "Settings/SettingsAbstractItemController.h"
class SettingsMassTaxesChangeView;

class SettingsMassTaxesChangeController : public SettingsAbstractItemController
{
    Q_OBJECT
private:
    SettingsMassTaxesChangeView *view;
    GoodsGroupModel *goodsGroupModel;
    TaxModel *taxModel;
    TaxChangerModel *taxChangerModel;
    int basePrice;
    void fillBox(QComboBox *box,QVector<Tax> values);
    void fillBox(QComboBox *box,QVector<GoodsGroup> values);

public:
    explicit SettingsMassTaxesChangeController(QObject *parent = 0);
    SettingsMassTaxesChangeView *getView();

public slots:
    void setModel();
    void chooseKindOfCount();
    void saveChanges();
};

#endif // SETTINGSMASSTAXESCHANGECONTROLLER_H
