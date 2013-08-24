#ifndef REPORTLISTTVMODEL_H
#define REPORTLISTTVMODEL_H

#include "Database/TVModel.h"
#include "Report/Report.h"

class ReportListTVModel : public TVModel
{
    QString reportTypeFilter;

    void initHeaders();
protected:
     QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
public:
    ReportListTVModel();

    void getData();

    QVariant data(int row, int column, int role);

    void setReportTypeFilter(Report::ReportType type);

};

#endif // REPORTLISTTVMODEL_H
