#include "Document.h"

Document::Document() {
    documentDate = QDate::currentDate();
    issueName = "";
    receiveName = "";
    storeResult = false;

    OwnerService *ownerService = new OwnerService();
    this->ownerId = ownerService->getActualOwner().getId();
    delete ownerService;
}

QString Document::getSymbol(){
    return this->documentSymbol;
}


QString Document::getDocumentPlace(){
    return this->documentPlace;
}


QDate Document::getDocumentDate(){
    return this->documentDate;
}


QVector<DocumentPosition> Document::getDocumentPositions(){
    return documentPositions;
}


double Document::getTotal() {
    return total;
}

bool Document::getStoreResult() {
    return storeResult;
}


Contractor Document::getContractor(){
    return this->contractor;
}

 QVector<SimpleDocumentInfo> Document::getRelatedDocuments()
{
    return relatedDocuments;
}

QString Document::getDocumentName()
{
    return documentName;
}

QString Document::getDocumentType()
{
    return documentType;
}

QString Document::getDocumentFamily()
{
    return documentType;
}

QString Document::getIssueName()  {
    return this->issueName;
}
QString Document::getReceiveName()    {
    return this->receiveName;
}

int Document::getOwnerId() {
    return ownerId;
}


void Document::setSymbol(QString symbol){
    this->documentSymbol = symbol;
}


void Document::setDocumentPlace(QString documentPlace){
    this->documentPlace = documentPlace;
}


void Document::setDocumentDate(QDate documentDate){
    this->documentDate = documentDate;
}


void Document::setDocumentPositions(QVector<DocumentPosition> documentPositions)
{
    this->documentPositions = documentPositions;
}


void Document::setStoreResult(bool storeResult)
{
    this->storeResult = storeResult;
}


void Document::setTotal(double total)
{
    this->total = total;
}


void Document::setContractor(Contractor contractor)   {
    this->contractor = contractor;
}

void Document::setRelatedDocuments(QVector<SimpleDocumentInfo> relatedDocuments)
{
    this->relatedDocuments = relatedDocuments;
}

void Document::setIssueName(QString issueName)    {
    this->issueName = issueName;
}
void Document::setReceiveName(QString receiveName)    {
    this->receiveName = receiveName;
}

void Document::setDocumentName(QString documentName)
{
    this->documentName = documentName;
}

void Document::setDocumentType(QString documentType)
{
    this->documentType = documentType;
}

void Document::setDocumentFamily(QString documentFamily)
{
    this->documentFamily = documentFamily;
}


QString Document::positionsToString()
{

        QString positionsString = QString(", POZYCJE (") + QVariant(documentPositions.size()).toString() + QString("): \n");
        positionsString += "Lp. \t | \tGOOD \t | \tquantity \t | \tprice_net \t | \ttax_id";
        for(int i =0; i < this->documentPositions.size(); i++)
        {
            positionsString += "\n" + QString::number(i+1) + documentPositions[i].toString();
        }
        return positionsString;

}

void Document::setOwnerId(int ownerId) {
    this->ownerId = ownerId;
}

QString Document::getSignature() { return this->signature; }

QString Document::toString()
{
   return  QString("1) Symbol: ").append(this->getSymbol())
           + QString(", 3) Miejsce wystawienia dokumentu: ").append(this->getDocumentPlace())
           + QString(", 5) Kontrahent id: ").append(QVariant(this->getContractor().getId()).toString())
           + QString(", 6) Data wystawienia dokumentu: ").append(this->getDocumentDate().toString("yyyy-MM-dd"))
           + QString(", 9) Skutek magazynowy: ").append(QVariant(this->storeResult).toString())
           + QString(", 10) Wartość: ").append(QVariant(this->getTotal()).toString()) + positionsToString();

}

