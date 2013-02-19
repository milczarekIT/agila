#ifndef DOCUMENTINFOMODEL_H
#define DOCUMENTINFOMODEL_H

#include "Database/Model.h"
#include "Document/DocumentInfo.h"
#include "Other/SimpleStringStructure.h"
#include "Other/Application/ApplicationManager.h"

class DocumentInfoModel : public Model
{
public:
    DocumentInfoModel();

    /** Zwraca wektor obiektów DocumentInfo wszystkich dokumentów dostępnych w aplikacji */
    QVector<DocumentInfo> getDocumentsInfo();

    /** Zwraca wektor obiektów DocumentInfo wszystkich dokumentów dostępnych w aplikacji */
    QVector<DocumentInfo> getDocumentsInfo(QString familyId);

    /** DocumentInfo dla wybranego typu np. FV */
    DocumentInfo getDocumentInfo(QString type);

    /** Zwraca typ documentu na podstawie symbolu dokumentu w parametrze */
    QString getDocumentTypeBySymbol(QString symbol);

    /** Zwraca documentFamily na podstawie symbolu dokumentu */
    SimpleStringStructure getDocumentFamilyBySymbol(QString symbol);

    /** Zwraca documentFamily na podstawie id np. SALE */
    SimpleStringStructure getFamily(QString id);

    /** zwraca wektor typów np: FV, FK na podstawie family np. SALE */
    QVector<QString> getTypesByFamily(QString family);

    /** zwraca nazwe tabeli, w której przechowywany jest dany typ documenów np. dla FV returns sale_documents, dla NK documents_nk */
    QString getTableNameByDocumentType(QString documentType);

    void editAfterText(QString documentType, QString afterText);
    void editDocumentNumbering(QString documentType, QString numbering);
};

#endif // DOCUMENTINFOMODEL_H
