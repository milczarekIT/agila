#ifndef CONTRACTORTVMODEL_H
#define CONTRACTORTVMODEL_H

#include "Database/TVModel.h"
#include "Database/Database.h"
#include "Contractor/Contractor.h"
#include "Contractor/ContractorTVDisplayer.h"

/**
  * TableViewModel dla contractora
  * @author Bartosz Milczarek, Krzysztof Marjański
  */
class ContractorTVModel : public TVModel
{
    QString symbolFilter;
    QString nameFilter;
    QString nipFilter;
    QString conGroupFilter;
    QString conTypeFilter;

    /**
      * inicjuje nazwy nagłówków dla modelu
      */
    void initHeaders();

protected:
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
public:
    ContractorTVModel();
    ~ContractorTVModel();

    /**
      * Przekazuje do modelu najważniejsze dane o wszystkich kontrahentach
      * Dane w modelu: id, symbol, name, contractorGroup, city, adress, nip
      */
    void getContractors();

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

    void setSymbolFilter (QString value);
    void setNameFilter (QString value);
    void setNipFilter (QString value);
    void setConGroupFilter(int idGroup);
    void setConTypeFilter(int type);
};

#endif // CONTRACTORTVMODEL_H
