#ifndef STORERESULTSERVICE_H
#define STORERESULTSERVICE_H

#include "Database/Database.h"
#include "DocumentPosition.h"
#include "Goods/GoodsModel.h"

class StoreResultService
{
private:

    /**
      * Zmienna odpowiadająca za to czy jest wywoływany skutek magazynowy czy też nie
      * tzn. czy stan magazynowy (ilość towaru) ma się zmieniać czy nie
      * Domyślnie wywolywany jest skutek magazynowy
      */
    bool storeResult;

    /**
      * zmienna odpowiadająca za to czy stan na magazynie ma się zwiększać czy zmniejszać
      * false - dla zmniejszenia towaru np. faktury, paragon, wydania magazynowe
      * true - dla zwiekszenia towaru np. przyjecia magazynowe
      * Domyślnie konstruktor ustawia ta zmienną na false
      * Zmienna nie jest brana pod uwage, gdy dla dokumentu nie jest wywoływany skutek magazynowy
      */
    bool increasedQuantity;
public:
    StoreResultService();

    /**
      * Wywołuje skutek magazynowy dla dokumentu
      * @see changeStoreResult(QVector<DocumentPosition> positions, bool storeResult);
      */
    void callStoreResult(QVector<DocumentPosition> positions);
    void callStoreResult(DocumentPosition position);
    void callDiffStoreResult(DocumentPosition oldPosition, DocumentPosition newPosition);

     /**
      * Cofa skutek magazynowy
      * @see changeStoreResult(QVector<DocumentPosition> positions, bool storeResult);
      */
    void cancelStoreResult(QVector<DocumentPosition> positions);
    void cancelStoreResult(DocumentPosition position);

    /**
      * Zmiana skutku magazynowego (jeśli był, to odwolanie, jeśli nie było to wywołanie)
      * Wyołuje lub anuluje skutek magazynowy
      * @see callStoreResult(QVector<DocumentPosition> positions);
      * @see cancelStoreResult(QVector<DocumentPosition> positions);
      */
    void changeStoreResult(QVector<DocumentPosition> positions, bool storeResult);

    void setStoreResult(bool storeResult);

    /** Increased - dla dokumentów, po których ilość towaru się zwiększa w magazynie */
    void setIncreasedQuantity();

    /** Decreased - dla dokumentów, po których ilość towaru się zmniejsza w magazynie */
    void setDecreasedQuantity();

    bool isStoreResult();
    bool isIncreasedQuantity();

};

#endif // STORERESULTSERVICE_H
