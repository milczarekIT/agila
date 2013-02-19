#include "GoodsGroupModel.h"

GoodsGroupModel::GoodsGroupModel()
{
}

GoodsGroupModel::~GoodsGroupModel()
{
}

QVector<GoodsGroup> GoodsGroupModel::getGoodsGroups()
{
    QVector<GoodsGroup> groups;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT id_group, name FROM goods_groups WHERE is_active = true");
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsGroupModel::getGoodsGroups", query);
    else
    {
        GoodsGroup gg;
        while(query->next())
        {
            gg.setId(query->value(0).toInt());
            gg.setName(query->value(1).toString());
            groups.push_back(gg);
        }
    }
    delete query;

    return groups;
}


GoodsGroup GoodsGroupModel::getGoodsGroup(int id)
{
    GoodsGroup gg;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT name FROM goods_groups WHERE id_group = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsGroupModel::getGoodsGroup", query);
    else if(query->size() > 0)
    {
        query->first();
        gg.setId(id);
        gg.setName(query->value(0).toString());
    }
    delete query;

    return gg;
}

void GoodsGroupModel::addGoodsGroup(GoodsGroup gg)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO goods_groups (name) VALUES (?)");
    query->addBindValue(gg.getName());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsGroupModel::addGoodsGroup", query);

    delete query;
}

void GoodsGroupModel::editGoodsGroup(GoodsGroup gg)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE goods_groups SET name = ? WHERE id_group = ?");
    query->addBindValue(gg.getName());
    query->addBindValue(gg.getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsGroupModel::editGoodsGroup", query);

    delete query;
}

void GoodsGroupModel::removeGoodsGroup(int id)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE goods_groups SET is_active = false WHERE id_group = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsGroupModel::removeGoodsGroup", query);

    delete query;
}
