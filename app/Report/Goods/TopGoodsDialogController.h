#ifndef TOPGOODSDIALOGCONTROLLER_H
#define TOPGOODSDIALOGCONTROLLER_H

#include "Report/ReportDialogController.h"
#include "Report/Goods/TopGoodsTVModel.h"
#include "Report/Goods/TopGoodsDialogView.h"
#include "Report/ReportDialogController.h"
class TopGoodsDialogView;

class TopGoodsDialogController : public ReportDialogController
{
    Q_OBJECT
private:
    TopGoodsDialogView *view;
    TopGoodsTVModel *tvModel;

    void initModelFromInterfaceData();
    void restoreTableState();
    void saveTableState();
public:
    TopGoodsDialogController(QWidget *parent);
    ~TopGoodsDialogController();

    void exec();

public slots:
    void printReport();
    void setListLimitFilter(int limit);
    void setDateFromFilter(QDate fromDate);
    void setDateToFilter(QDate toDate);

};

#endif // TOPGOODSDIALOGCONTROLLER_H
