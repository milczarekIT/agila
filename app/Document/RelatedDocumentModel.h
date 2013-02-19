#ifndef RELATEDDOCUMENTMODEL_H
#define RELATEDDOCUMENTMODEL_H

#include "Database/Model.h"
#include "Document/SimpleDocumentInfo.h"
#include "Document/DocumentInfoModel.h"

class RelatedDocumentModel : public Model
{
    QStringList getRelatedDocumentsSymbols(QString symbol);
public:
    RelatedDocumentModel();

    QVector<SimpleDocumentInfo> getRelatedDocuments(QString symbol);
    QVector<SimpleDocumentInfo> getRelatedDocumentsByType(QString symbol, QString type);
    SimpleDocumentInfo getSimpleDocumentInfo(QString symbol);

    /**
      * Dodawanie, edycja dokumentów powiązanych np. WZ jest dokumentem powiązanycm z FV
      * np:
      * dokumenty bazowe: FV
      * dokumenty powiązane: KP, WZ, FK
      */
    void addLinkToDocument(QString baseDocument, QString linkedDocument);
    void editLinkToBaseDocument(QString baseDocument, QString linkedDocument);
    void editLinkToLinkedDocument(QString baseDocument, QString linkedDocument);
    void removeLinkToDocument(QString baseDocument, QString linkedDocument);
    void removeLinksToDocument(QString document);
    void deleteLinksToDocument(QString document);
    bool isDocumentSymbolInVector(QString documentSymbol, QVector<SimpleDocumentInfo> vector);
    bool isDocumentInApp(QString symbol);
};

#endif // RELATEDDOCUMENTMODEL_H
