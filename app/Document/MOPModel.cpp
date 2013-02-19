#include "MOPModel.h"

MOPModel::MOPModel()
{
}

MOPModel::~MOPModel()
{
}

QVector<MethodOfPayment> MOPModel::getMethodsOfPayment()
{
    QVector<MethodOfPayment> methods;

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT id_method, name, maturity FROM methods_of_payment WHERE is_active = true ORDER BY name ASC");
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("MOPModel::getMethodsOfPayment", query);

    MethodOfPayment mop;
    while(query->next())
    {
        mop.setId(query->value(0).toInt());
        mop.setName(query->value(1).toString());
        mop.setMaturity(query->value(2).toInt());
        methods.push_back(mop);
    }
    delete query;

    return methods;
}


void MOPModel::getMethodsOfPaymentModel()
{
    //model->setQuery("SELECT id_method,name,maturity "
     //               "FROM methods_of_payment WHERE is_active = true "
     //               "ORDER BY name ASC", database->db);
}

MethodOfPayment MOPModel::getMethodOfPayment(int id)
{
    MethodOfPayment mop;

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT name, maturity FROM methods_of_payment WHERE id_method = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("MOPModel::getMethodOfPayment", query);
    query->first();

    mop.setId(id);
    mop.setName(query->value(0).toString());
    mop.setMaturity(query->value(1).toInt());

    delete query;

    return mop;
}

void MOPModel::addMethodOfPayment(MethodOfPayment mop)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO methods_of_payment (name, maturity) VALUES (?, ?)");
    query->addBindValue(mop.getName());
    query->addBindValue(mop.getMaturity());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("MOPModel::addMethodOfPayment", query);

    delete query;
}

void MOPModel::editMethodOfPayment(MethodOfPayment mop)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE methods_of_payment SET name = ?, maturity = ? WHERE id_method = ?");
    query->addBindValue(mop.getName());
    query->addBindValue(mop.getMaturity());
    query->addBindValue(mop.getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("MOPModel::editMethodOfPayment", query);

    delete query;
}

void MOPModel::removeMethodOfPayment(int id)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE methods_of_payment SET is_active = false WHERE id_method = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("MOPModel::removeMethodOfPayment", query);

    delete query;
}
