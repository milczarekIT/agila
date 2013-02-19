#include "ContractorTVModel.h"

ContractorTVModel::ContractorTVModel() : TVModel()
{
    symbolFilter="";
    nameFilter="";
    nipFilter="";
    conGroupFilter = "";
    conTypeFilter = "";
    sortColumn=3;
    sortOrder=Qt::AscendingOrder;
}

ContractorTVModel::~ContractorTVModel()
{
}

void ContractorTVModel::getContractors()
{
    setQuery("SELECT id_contractor, symbol, name, contractor_group, city, adress, nip "
                "FROM contractors "
                "WHERE is_active = true "
                + conGroupFilter + conTypeFilter
                + symbolFilter + nipFilter + nameFilter +
               "ORDER BY "+QString::number(sortColumn)+" "+((sortOrder==Qt::AscendingOrder) ? "DESC" : "ASC"), Database::getInstance().db);

   initHeaders();
}


void ContractorTVModel::initHeaders()
{
    this->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    this->setHeaderData(1, Qt::Horizontal, QObject::tr("Symbol"));
    this->setHeaderData(2, Qt::Horizontal, QObject::tr("Nazwa"));
    this->setHeaderData(3, Qt::Horizontal, QObject::tr("Grupa kontrachencka"));
    this->setHeaderData(4, Qt::Horizontal, QObject::tr("Miasto"));
    this->setHeaderData(5, Qt::Horizontal, QObject::tr("Adres"));
    this->setHeaderData(6, Qt::Horizontal, QObject::tr("NIP"));
}

 void ContractorTVModel::sort ( int column, Qt::SortOrder order)
 {
     this->sortColumn=column+1;
     this->sortOrder=order;
     getContractors();
 }

 QVariant ContractorTVModel::data(const QModelIndex & index, int role) const
 {
     ContractorTVDisplayer displayer(index, role, this);
     return displayer.display();
 }

 void ContractorTVModel::setNameFilter(QString value){
     if(value.isEmpty())
         nameFilter=value;
     else
         nameFilter="AND LOWER(contractors.name) LIKE LOWER('" + value + "%') ";
 }
 void ContractorTVModel::setSymbolFilter(QString value){
     if(value.isEmpty())
         symbolFilter=value;
     else
         symbolFilter="AND LOWER(contractors.symbol) LIKE LOWER('" + value + "%') ";
 }
 void ContractorTVModel::setNipFilter(QString value){
     if(value.isEmpty())
         nipFilter=value;
     else
         nipFilter="AND contractors.nip LIKE '" + value + "%' ";
 }
 void ContractorTVModel::setConGroupFilter(int idGroup){
     if(idGroup == -1)
         conGroupFilter = "";
     else
         conGroupFilter = "AND contractor_group =  " + QString::number(idGroup) + " ";
 }

 void ContractorTVModel::setConTypeFilter(int type) {
     if(type == (Contractor::BUYER | Contractor::SUPPLIER))
         this->conTypeFilter = "";
     else if(type == Contractor::BUYER)
         this->conTypeFilter = "AND (type = 1 OR type = 3) ";
     else if(type == Contractor::SUPPLIER)
         this->conTypeFilter = "AND (type = 2 OR type = 3) ";
 }
