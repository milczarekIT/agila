    #ifndef GOODSGROUPMODEL_H
#define GOODSGROUPMODEL_H

#include "Database/Model.h"
#include "Goods/GoodsGroup.h"

class GoodsGroupModel : public Model
{
public:
    GoodsGroupModel();
    ~GoodsGroupModel();

    QVector<GoodsGroup> getGoodsGroups();
    GoodsGroup getGoodsGroup(int id);
    void addGoodsGroup(GoodsGroup gg);
    void editGoodsGroup(GoodsGroup gg);
    void removeGoodsGroup(int id);
    void getGoodsGroupsModel();
};

#endif // GOODSGROUPMODEL_H
