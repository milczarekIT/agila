#include "UnitModel.h"

UnitModel::UnitModel()
{
}

UnitModel::~UnitModel()
{
}

QVector<Unit> UnitModel::getUnits()
{
    QVector<Unit> units;

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT id_unit, name, zero_places FROM units WHERE is_active = true");
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("UnitModel::getUnits", query);

    Unit *unit = new Unit();
    while(query->next())
    {
        unit->setId(query->value(0).toInt());
        unit->setName(query->value(1).toString());
        unit->setZeroPlaces(query->value(2).toInt());
        units.push_back(*unit);
    }
    delete unit;
    delete query;

    return units;
}


Unit UnitModel::getUnit(int id)
{
    Unit u;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT name, zero_places FROM units WHERE id_unit = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("UnitModel::getUnit", query);
    else if(query->size() > 0)
    {
        query->first();

        u.setId(id);
        u.setName(query->value(0).toString());
        u.setZeroPlaces(query->value(1).toInt());
    }

    return u;
}


void UnitModel::addUnit(Unit u)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO units (name, zero_places) VALUES (?, ?)");
    query->addBindValue(u.getName());
    query->addBindValue(u.getZeroPlaces());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("UnitModel::addUnit", query);

    delete query;
}


void UnitModel::editUnit(Unit u)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE units SET name = ?, zero_places = ? WHERE id_unit = ?");
    query->addBindValue(u.getName());
    query->addBindValue(u.getZeroPlaces());
    query->addBindValue(u.getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("UnitModel::editUnit", query);

    delete query;
}

void UnitModel::removeUnit(int id)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE units SET is_active = false WHERE id_unit = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("UnitModel::removeUnit", query);

    delete query;
}
