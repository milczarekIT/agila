#include "Report.h"

Report::Report()
{
    this->documentType = "REP";
    reportCreator = NULL;
}

QList< QList<QString> > Report::getPositions() {
    return positions;
}

void Report::setPositions(QList< QList<QString> > positions) {
    this->positions = positions;
}

QList<Qt::AlignmentFlag> Report::getAlignments() {
    return alignments;
}

void Report::setAlignments(QList<Qt::AlignmentFlag> alignments) {
    this->alignments = alignments;
}

QList<QString> Report::getHeaders() {
    return headers;
}

void Report::setHeaders(QList<QString> headers) {
    this->headers = headers;
}

QString Report::getReportSymbol() {
    return reportSymbol;
}

void Report::setReportSymbol(QString reportSymbol) {
    this->reportSymbol = reportSymbol;
}

QString Report::getReportName() {
    return reportName;
}

void Report::setReportName(QString reportName) {
    this->reportName = reportName;
}

Report::ReportType Report::getReportType() {
    return reportType;
}

void Report::setReportType(ReportType reportType) {
    this->reportType = reportType;
}

User *Report::getReportCreator() {
    return reportCreator;
}

void Report::setReportCreator(User *reportCreator) {
    this->reportCreator = reportCreator;
}

QDateTime Report::getReportDateTime() {
    return this->reportDateTime;
}

void Report::setReportDateTime(QDateTime reportDateTime) {
    this->reportDateTime = reportDateTime;
}

Owner Report::getOwner() {
    return this->owner;
}

void Report::setOwner(Owner owner) {
    this->owner = owner;
}
