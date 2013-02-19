#include "DocumentNKModel.h"

DocumentNKModel::DocumentNKModel() : DocumentModel()
{
}

DocumentNK DocumentNKModel::getDocumentNK(QString symbol)
{
    DocumentNK document;
    document.setSymbol(symbol);
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT document_date, contractor, invoice_symbol, invoice_date, "
                    "corrected_content, correct_content, receive_person, issue_person, document_place, owner "
                    "FROM documents_nk "
                    "WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentNKModel::getDocumentNK", query);
    else if(query->size() > 0)
    {
        query->first();

        ContractorService *conService = new ContractorService();

        document.setDocumentDate(query->value(0).toDate());
        document.setContractor(conService->getContractor(query->value(1).toInt()));
        document.setInvoiceSymbol(query->value(2).toString());
        document.setInvoiceDate(query->value(3).toDate());
        document.setCorrectedContent(query->value(4).toString());
        document.setCorrectContent(query->value(5).toString());
        document.setReceiveName(peopleModel->getName(query->value(6).toInt()));
        document.setIssueName(peopleModel->getName(query->value(7).toInt()));
        document.setDocumentPlace(documentPlaceModel->getDocumentPlace(query->value(8).toInt()).getName());
        document.setOwnerId(query->value(9).toInt());

        delete conService;
    }
    delete query;

    return document;
}

void DocumentNKModel::addDocumentNK(DocumentNK document)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO documents_nk (symbol, document_date, contractor, "
                    "invoice_symbol, invoice_date, corrected_content, correct_content, document_place, "
                    "receive_person, issue_person, owner, warehouse) "
                    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query->addBindValue(document.getSymbol());
    query->addBindValue(document.getDocumentDate().toString("yyyy-MM-dd"));
    query->addBindValue(document.getContractor().getId());
    query->addBindValue(document.getInvoiceSymbol());
    query->addBindValue(document.getInvoiceDate().toString("yyyy-MM-dd"));
    query->addBindValue(document.getCorrectedContent());
    query->addBindValue(document.getCorrectContent());
    query->addBindValue(documentPlaceModel->getDocumentPlaceId(document.getDocumentPlace()));
    query->addBindValue(peopleModel->getPersonId(document.getReceiveName()));
    query->addBindValue(peopleModel->getPersonId(document.getIssueName()));
    query->addBindValue(document.getOwnerId());
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentNKModel::addDocumentNK", query);

    delete query;
}

void DocumentNKModel::editDocumentNK(DocumentNK newDocument)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE documents_nk SET document_date = ?, contractor = ?, "
                        "invoice_symbol = ?, invoice_date = ?, corrected_content = ?, correct_content = ?, "
                        "document_place = ?, receive_person = ?, issue_person = ? "
                    "WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(newDocument.getDocumentDate().toString("yyyy-MM-dd"));
    query->addBindValue(newDocument.getContractor().getId());
    query->addBindValue(newDocument.getInvoiceSymbol());
    query->addBindValue(newDocument.getInvoiceDate().toString("yyyy-MM-dd"));
    query->addBindValue(newDocument.getCorrectedContent());
    query->addBindValue(newDocument.getCorrectContent());
    query->addBindValue(documentPlaceModel->getDocumentPlaceId(newDocument.getDocumentPlace()));
    query->addBindValue(peopleModel->getPersonId(newDocument.getReceiveName()));
    query->addBindValue(peopleModel->getPersonId(newDocument.getIssueName()));
    query->addBindValue(newDocument.getSymbol());
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentNKModel::editDocumentNK", query);

    delete query;
}

void DocumentNKModel::removeDocumentNK(QString symbol)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("DELETE FROM documents_nk WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentNKModel::removeDocumentNK", query);

    delete query;
}


