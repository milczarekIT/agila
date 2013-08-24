#ifndef UNREALIZEDORDERTVMODEL_H
#define UNREALIZEDORDERTVMODEL_H

#include "Database/TVModel.h"
#include "Report/Order/UnrealizedOrderTVDisplayer.h"
#include "Other/Application/ApplicationManager.h"

class UnrealizedOrderTVModel : public TVModel
{
    QString type; // ZK or ZD
    void initHeaders();
protected:
     QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
public:
    UnrealizedOrderTVModel(QString type);
    ~UnrealizedOrderTVModel();

    QVariant data(int row, int column, int role);

    void getData();
    Price getValue();
};

#endif // UNREALIZEDORDERTVMODEL_H
