#include "ReportListTVModel.h"

ReportListTVModel::ReportListTVModel()
{
    reportTypeFilter = "";
}

void ReportListTVModel::getData()
{
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
    this->setQuery("SELECT r.id, r.symbol, r.name, r.creation_date, u.name, r.file_path "
                   "FROM reports r, users u "
                   "WHERE r.creator = u.id AND r.warehouse = " + warehouseId.append(" ") +
                   "AND r.is_active = true " + reportTypeFilter +
                   "ORDER BY "+QString::number(sortColumn)+" "+((sortOrder==Qt::AscendingOrder) ? "DESC" : "ASC"), Database::getInstance().db);
    this->initHeaders();

    qDebug() << "last_q: " << this->query().lastQuery();
}

void ReportListTVModel::initHeaders()
{
    this->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    this->setHeaderData(1, Qt::Horizontal, QObject::tr("Symbol"));
    this->setHeaderData(2, Qt::Horizontal, QObject::tr("Nazwa"));
    this->setHeaderData(3, Qt::Horizontal, QObject::tr("Data utworzenia"));
    this->setHeaderData(4, Qt::Horizontal, QObject::tr("Utworzony przez"));
    this->setHeaderData(5, Qt::Horizontal, QObject::tr("Path"));
}

QVariant ReportListTVModel::data(const QModelIndex & index, int role) const
{
    //OrderedGoodsTVDisplayer displayer(index, role, this);
    //return displayer.display();
    return baseData(index, role);
}

QVariant ReportListTVModel::data(int row, int column, int role) {
    QModelIndex modelIndex = this->index(row, column);
    return data(modelIndex, role);
}

void ReportListTVModel::setReportTypeFilter(Report::ReportType type)
{
    this->reportTypeFilter = "AND report_type = '" + QVariant(type).toString() + "' ";
}
