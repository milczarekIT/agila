#include "ContractorTVDisplayer.h"

ContractorTVDisplayer::ContractorTVDisplayer(const QModelIndex & index, int role, TVModel const* model) : TVDisplayer(index, role, model)
{

}

ContractorTVDisplayer::~ContractorTVDisplayer()
{

}

QVariant ContractorTVDisplayer::display() const
{
    if (isDisplayOrEditRole())
    {
        if (isContractorGroupColumn())
            return displayContractorGroup();
        else
            return model->baseData(index, role);
    }
    return QVariant();
}

bool ContractorTVDisplayer::isContractorGroupColumn() const {
    return index.column() == 3;
}
QVariant ContractorTVDisplayer::displayContractorGroup() const {

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
