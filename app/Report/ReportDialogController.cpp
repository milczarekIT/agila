#include "ReportDialogController.h"

ReportDialogController::ReportDialogController()
{
    this->ownerService = new OwnerService();
    this->dnc = new DocumentNumeratorController("REP");
}

ReportDialogController::~ReportDialogController()
{
    delete ownerService;
    delete dnc;
}

void ReportDialogController::doSaveReport(ReportDataReader *reportDataReader, QString reportTitle, Report::ReportType reportType) {
    QList< QList<QString> > positions = reportDataReader->readPositions();
    QList<Qt::AlignmentFlag> alignments = reportDataReader->readAligmnents();
    QList<QString> headers = reportDataReader->readHeaders();

    Report *report = new Report();
    report->setReportType(reportType);
    report->setAlignments(alignments);
    report->setHeaders(headers);
    report->setPositions(positions);
    report->setReportSymbol(dnc->getNextSymbol());
    report->setReportName(reportTitle + " " + report->getReportSymbol());
    report->setReportDateTime(QDateTime::currentDateTime());
    User *currentUser = ApplicationManager::getInstance()->getLoggedUser();
    if(currentUser != NULL && currentUser->getId() > 0)
        report->setReportCreator(currentUser);
    report->setOwner(ownerService->getActualOwner());


   ReportPdfGenerator *pdfGenerator = new ReportPdfGenerator();
   QPrinter* pdfPrinter = pdfGenerator->generate(report);

   QString outputFilePath = pdfGenerator->outputFileName(report);
   if(QFile(outputFilePath).exists()) {
       ReportInfo *reportInfo = new ReportInfo(report, outputFilePath);

       ReportInfoService *reportInfoService = new ReportInfoService();
       reportInfoService->addReportInfo(reportInfo);
       delete reportInfoService;

       PrintPreviewDialog *preview = new PrintPreviewDialog(pdfPrinter, report->getReportName());
       connect(preview->getPreview(),SIGNAL(paintRequested(QPrinter*)),pdfGenerator,SLOT(generatePreview()));
       preview->show();
       delete preview;

   }

   delete report;
}
