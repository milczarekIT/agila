#include "SettingsTVModel.h"

SettingsTVModel::SettingsTVModel()
{
}

void SettingsTVModel::getFeaturesForGroup(int goodGroup)
{
    this->setQuery("SELECT feature, name FROM goods_groups_features, features "
                    "WHERE goods_groups_features.feature = features.id_feature "
                   "AND goods_group = " + QVariant(goodGroup).toString(), Database::getInstance().db);

    this->setHeaderData(1, Qt::Horizontal, QObject::tr("Cechy dla wybranej grupy"));
}

void SettingsTVModel::getRestFeaturesForGroup(int goodGroup)
{
    this->setQuery("SELECT id_feature, name "
                    "FROM features WHERE features.is_active = true AND features.id_feature != ALL "
                    "(SELECT feature FROM goods_groups_features, features "
                   "WHERE goods_groups_features.feature = features.id_feature AND goods_group =  "
                   + QVariant(goodGroup).toString()+ ") ", Database::getInstance().db);


    this->setHeaderData(1, Qt::Horizontal, QObject::tr("Wszystkie cechy dla dóbr"));
}

void SettingsTVModel::initHeaders() {}
