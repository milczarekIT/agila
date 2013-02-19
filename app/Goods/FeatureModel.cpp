#include "FeatureModel.h"

FeatureModel::FeatureModel()
{
}

FeatureModel::~FeatureModel()
{
}

QVector<Feature> FeatureModel::getFeatures()
{
    QVector<Feature> features;

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT id_feature, name FROM features WHERE is_active = true");
    query->exec();

    if(this->isQueryError(query))
            throw new SQLException("FeatureModel::getFeatures", query);

    Feature *f = new Feature();
    while(query->next())
    {
        f->setId(query->value(0).toInt());
        f->setName(query->value(1).toString());
        features.push_back(*f);
    }
    delete f;
    delete query;

    return features;
}

Feature FeatureModel::getFeature(int id)
{
    Feature f;

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT name FROM features WHERE id_feature = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
            throw new SQLException("FeatureModel::getFeature", query);
    else if(query->size() > 0)
    {
        query->first();

        f.setId(id);
        f.setName(query->value(0).toString());
    }
    delete query;

    return f;
}

void FeatureModel::addFeature(Feature f)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO features (name) VALUES (?)");
    query->addBindValue(f.getName());
    query->exec();

    if(this->isQueryError(query))
            throw new SQLException("FeatureModel::addFeature", query);

    delete query;
}

void FeatureModel::editFeature(Feature f)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE features SET name = ? WHERE id_feature = ?");
    query->addBindValue(f.getName());
    query->addBindValue(f.getId());
    query->exec();

    if(this->isQueryError(query))
            throw new SQLException("FeatureModel::editFeature", query);

    delete query;
}

void FeatureModel::removeFeature(int id)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE features SET is_active = false WHERE id_feature = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
            throw new SQLException("FeatureModel::removeFeature", query);

    delete query;
}

QVector<Feature> FeatureModel::getFeaturesForGroup(int goodGroup)
{
    QVector<Feature> features;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT feature, name FROM goods_groups_features, features "
                    "WHERE goods_groups_features.feature = features.id_feature "
                    "AND goods_group = ? ");
    query->addBindValue(goodGroup);
    query->exec();

    if(this->isQueryError(query))
            throw new SQLException("FeatureModel::getFeaturesForGroup", query);

    Feature *f = new Feature();
    while(query->next())
    {
        f->setId(query->value(0).toInt());
        f->setName(query->value(1).toString());
        features.push_back(*f);
    }
    delete f;
    delete query;

    return features;
}

QVector<GoodsGroup> FeatureModel::getGroupsForFeature(int feature)
{
    QVector<GoodsGroup> groups;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT goods_group, name FROM goods_groups_features, goods_groups "
                    "WHERE goods_groups_features.goods_group = goods_groups.id_group "
                    "AND feature = ? ");
    query->addBindValue(feature);
    query->exec();

    if(this->isQueryError(query))
            throw new SQLException("FeatureModel::getGroupsForFeature", query);

    GoodsGroup *gg = new GoodsGroup();
    while(query->next())
    {
        gg->setId(query->value(0).toInt());
        gg->setName(query->value(1).toString());
        groups.push_back(*gg);
    }
    delete gg;
    delete query;

    return groups;
}

void FeatureModel::addFeatureToGroup(int feature, int goodGroup)
{
    try {
        query = new QSqlQuery(Database::getInstance().db);
        query->prepare("INSERT INTO goods_groups_features (goods_group, feature) VALUES (?, ?)");
        query->addBindValue(goodGroup);
        query->addBindValue(feature);
        query->exec();

        if(this->isQueryError(query))
                throw new SQLException("FeatureModel::addFeatureToGroup", query);

    } catch(SQLException *e) {
        qDebug() << e->getMessage();
    }

    delete query;
}

void FeatureModel::removeFeatureFromGroup(int feature, int goodGroup)
{
    try {
        query = new QSqlQuery(Database::getInstance().db);
        query->prepare("DELETE FROM goods_groups_features WHERE goods_group = ? AND feature = ?");
        query->addBindValue(goodGroup);
        query->addBindValue(feature);
        query->exec();

        if(this->isQueryError(query))
                throw new SQLException("FeatureModel::removeFeatureFromGroup", query);

    } catch(SQLException *e) {
        qDebug() << e->getMessage();
    }

    delete query;
}
