#ifndef SETTINGSTVMODEL_H
#define SETTINGSTVMODEL_H

#include "Database/TVModel.h"

class SettingsTVModel : public TVModel
{
    void initHeaders();
public:
    SettingsTVModel();

    void getFeaturesForGroup(int goodGroup);
    void getRestFeaturesForGroup(int goodGroup);

};

#endif // SETTINGSTVMODEL_H
