#include "GoodsGroup.h"

GoodsGroup::GoodsGroup(int id, QString name)
{
    this->setId(id);
    this->setName(name);
}

GoodsGroup::GoodsGroup()
{
    GoodsGroup::SimpleStructure(id, name);
}
