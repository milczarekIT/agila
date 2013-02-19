#ifndef TOPCONTRACTORSDIALOGCONTROLLER_H
#define TOPCONTRACTORSDIALOGCONTROLLER_H

#include <QWidget>
#include "Report/Contractor/TopContractorsTVModel.h"
#include "Report/Contractor/TopContractorsDialogView.h"
#include "Report/ReportDialogController.h"
class TopContractorsDialogView;

class TopContractorsDialogController : public ReportDialogController
{
    Q_OBJECT
private:
    void initModelFromInterfaceData();

    void restoreTableState();
    void saveTableState();

    TopContractorsDialogView *view;
    TopContractorsTVModel *tvModel;
public:
    TopContractorsDialogController(QWidget *parent);
    ~TopContractorsDialogController();

    void exec();

public slots:
    void printReport();
    void setListLimitFilter(int limit);
    void setDateFromFilter(QDate fromDate);
    void setDateToFilter(QDate toDate);
};

#endif // TOPCONTRACTORSDIALOGCONTROLLER_H
