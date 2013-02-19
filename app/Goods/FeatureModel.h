#ifndef FEATUREMODEL_H
#define FEATUREMODEL_H

#include "Database/Model.h"
#include "Goods/Feature.h"
#include "Goods/GoodsGroup.h"

class FeatureModel : public Model
{
public:
    FeatureModel();
    ~FeatureModel();

    QVector<Feature> getFeatures();
    Feature getFeature(int id);
    void addFeature(Feature f);
    void editFeature(Feature f);
    void removeFeature(int id);
    void getFeaturesModel();

    // features - goodsGroup
    /**
      * Zwraca wektor cech dla danej grupy towarowej
      * @param goodGroup - id grupy towarowej
      */
    QVector<Feature> getFeaturesForGroup(int goodGroup);

    /**
      * Zwraca wektor grup towarowych dla danej cechy
      * @param feature - id cechy
      */
    QVector<GoodsGroup> getGroupsForFeature(int feature);
    void addFeatureToGroup(int feature, int goodGroup);
    void removeFeatureFromGroup(int feature, int goodGroup);
};

#endif // FEATUREMODEL_H
