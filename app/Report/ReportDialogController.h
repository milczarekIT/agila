#ifndef REPORTDIALOGCONTROLLER_H
#define REPORTDIALOGCONTROLLER_H

#include <QWidget>
#include <QHeaderView>
#include "Other/ITableStateManager.h"
#include "Other/Owner/OwnerService.h"
#include "Document/DocumentNumeratorController.h"
#include "Report/Report.h"
#include "Report/ReportInfo.h"
#include "ReportInfoService.h"
#include "Tools/ReportGenerator/ReportDataReader.h"
#include "Tools/ReportGenerator/ReportPdfGenerator.h"
#include "Tools/Print/PrintPreviewDialog.h"

class ReportDialogController : public QObject, public ITableStateManager
{
    Q_OBJECT
protected:
    OwnerService *ownerService;
    DocumentNumeratorController *dnc;

    void doSaveReport(ReportDataReader *reportDataReader, QString reportTitle, Report::ReportType reportType);
public:
    ReportDialogController();
    ~ReportDialogController();

    virtual void exec() = 0;

public slots:
    virtual void saveReport() = 0;
};

#endif // REPORTDIALOGCONTROLLER_H
