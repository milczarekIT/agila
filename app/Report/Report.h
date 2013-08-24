#ifndef REPORT_H
#define REPORT_H

#include <QList>
#include <Qt>
#include <QString>
#include <QDateTime>
#include "Other/Owner/Owner.h"
#include "Document/Document.h"

class Report : public Document
{
public:
    enum ReportType {CURRENT_INVENTORY, CURRENT_INVENTORY_GROUP, UNPAID_SALE_DOCUMENTS, UNPAID_PURCHASE_DOCUMENTS, UNREALIZED_ZK_ORDERS, UNREALIZED_ZD_ORDERS, MISSING_GOODS, ENDING_GOODS, ORDERED_CONTRACTOR_GOODS, ORDERED_SUPPLIER_GOODS, BESTSELLER_GOODS, TOP_CONTRACTORS};

private:
    QList< QList<QString> > positions;
    QList<Qt::AlignmentFlag> alignments;
    QList<QString> headers;

    QString reportSymbol;
    QString reportName;
    User *reportCreator;
    QDateTime reportDateTime;
    Owner owner;
    Report::ReportType reportType;
public:
    Report();


    static const int UNPAID_SALE_DOCUMENT = 0x0001;
    static const int UNPAID_SALE_DOCUMENT_ON_TIME = 0x0002;

    QList< QList<QString> > getPositions();
    void setPositions(QList< QList<QString> > positions);

    QList<Qt::AlignmentFlag> getAlignments();
    void setAlignments(QList<Qt::AlignmentFlag> alignments);

    QList<QString> getHeaders();
    void setHeaders(QList<QString> headers);

    QString getReportSymbol();
    void setReportSymbol(QString reportSymbol);

    QString getReportName();
    void setReportName(QString reportName);

    Report::ReportType getReportType();
    void setReportType(Report::ReportType reportType);

    User *getReportCreator();
    void setReportCreator(User *reportCreator);

    QDateTime getReportDateTime();
    void setReportDateTime(QDateTime reportDateTime);

    Owner getOwner();
    void setOwner(Owner owner);
};

#endif // REPORT_H
