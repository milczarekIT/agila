#ifndef DEPARTMENTMODEL_H
#define DEPARTMENTMODEL_H

#include "Other/SimpleStructure.h"
#include "Database/Model.h"

class DepartmentModel : public Model
{
public:
    DepartmentModel();
    ~DepartmentModel();

    QVector<SimpleStructure> getDepartments();
    SimpleStructure getDepartment(int id);
    void addDepartment(SimpleStructure department);
    void editDepartment(SimpleStructure department);
    void removeDepartment(int id);
};

#endif // DEPARTMENTMODEL_H
