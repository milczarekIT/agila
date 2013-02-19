#include "DepartmentModel.h"

DepartmentModel::DepartmentModel()
{
}

DepartmentModel::~DepartmentModel()
{
}

QVector<SimpleStructure> DepartmentModel::getDepartments()
{
    QVector<SimpleStructure> departments;

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT id_department, name FROM departments WHERE is_active = true");
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DepartmentModel::getDepartments", query);
    else
    {
        SimpleStructure *ss = new SimpleStructure();
        while(query->next())
        {
            ss->setId(query->value(0).toInt());
            ss->setName(query->value(1).toString());
            departments.push_back(*ss);
        }
        delete ss;
    }
    delete query;

    return departments;
}

SimpleStructure DepartmentModel::getDepartment(int id)
{
    SimpleStructure ss;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT name FROM departments WHERE id_department = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DepartmentModel::getDepartment", query);
    else if(query->size() > 0)
    {
        query->first();

        ss.setId(id);
        ss.setName(query->value(0).toString());
    }
    delete query;

    return ss;
}

void DepartmentModel::addDepartment(SimpleStructure department) {

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO departments (name) VALUES (?)");
    query->addBindValue(department.getName());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DepartmentModel::addDepartment", query);

    delete query;
}

void DepartmentModel::editDepartment(SimpleStructure department) {

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE departments SET name = ? WHERE id_department = ?");
    query->addBindValue(department.getName());
    query->addBindValue(department.getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DepartmentModel::editDepartment", query);

    delete query;
}

void DepartmentModel::removeDepartment(int id)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE departments SET is_active = false WHERE id_department = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DepartmentModel::removeDepartment", query);

    delete query;
}
