#ifndef PRICEDOCUMENTCONTROLLER_H
#define PRICEDOCUMENTCONTROLLER_H

#include <QObject>
#include "Goods/GoodsModel.h"
#include "PriceGoodSelectorController.h"
#include "Document/PriceDocument/PriceList.h"
#include "Document/DocumentNumeratorController.h"
#include "Document/PriceDocument/PriceDocumentView.h"
#include "Document/PriceDocument/PriceDocumentsValidator.h"
class PriceDocumentView;
class PriceDocumentsValidator;

class PriceDocumentController : public QObject
{
    Q_OBJECT
protected:
    PriceDocumentView *view;
    DocumentNumeratorController *documentNumerator;
    PriceDocumentsValidator *validator;
    GoodsModel *goodsModel;
    QVector<Goods> *goods;
    PriceList pList;
    bool edition;

    void setCurrentPriceLevel();
    void initPriceLevel();
    void updateGoodsSet(QVector<Goods> *choosedGood);
    virtual QString getNextSymbol() = 0;

public:
    explicit PriceDocumentController(QObject *parent = 0);
    ~PriceDocumentController();
    bool isValidateDateNotConcerns();
    QVector<DocumentPosition> getDocumentPositions();
    QVector<Goods> *getGoodsFromDocumentsPositions(QVector<DocumentPosition> dp);
    PriceDocumentView *getView();
    bool isChangesOccured();
    virtual PriceList getDataFromView() = 0;
    virtual void add() = 0;
    virtual void edit(QString symbol) = 0;

public slots:
    int exec();
    void selectGoods();
    void setDateLikeNotConcerns(bool notConc);
    void removeGoodsFromPositions();
    void initTableModel();
    void checkChanges();
    void checkRequiredFields();
    virtual int exec(QString symbol) = 0;
    
};

#endif // PRICEDOCUMENTCONTROLLER_H
