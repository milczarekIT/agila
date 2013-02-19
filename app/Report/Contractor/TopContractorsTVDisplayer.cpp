#include "TopContractorsTVDisplayer.h"

TopContractorsTVDisplayer::TopContractorsTVDisplayer(const QModelIndex &index, int role, const TVModel *model) :TVDisplayer(index, role, model)
{
}

TopContractorsTVDisplayer::~TopContractorsTVDisplayer() {}

 QVariant TopContractorsTVDisplayer::display() const
 {
     if (isDisplayOrEditRole())
     {
         if(isPriceColumn())
             return displayPrice();
         else if(isContractorGroupColumn())
             return displayContractorGroup();
         else
             return model->baseData(index, role);
     }
     if(isTextAligmentRole())
     {
         if (isPriceColumn())
                 return QVariant(Qt::AlignRight | Qt::AlignVCenter);
     }
     return QVariant();
 }

 bool TopContractorsTVDisplayer::isContractorGroupColumn() const
 {
     return index.column() == 3;
 }
 bool TopContractorsTVDisplayer::isPriceColumn() const
 {
     return index.column() == 4;
 }

 QVariant TopContractorsTVDisplayer::displayContractorGroup() const
 {
     int idGroup =  model->baseData(index, role).toInt();

     if(idGroup == 0)
         return "BRAK";
     else
     {
         ContractorGroupModel *cgmodel = new ContractorGroupModel();
         QString groupName = cgmodel->getContractorGroup(idGroup).getName();
         delete cgmodel;

         return groupName;
     }
 }
 QVariant TopContractorsTVDisplayer::displayPrice() const
 {
     double value = model->baseData(index, role).toDouble();

     if(value == 0.0)
         return "";
     else
         return QString::number(value, ',', 2).replace(QRegExp("[.]"), ",");
 }
