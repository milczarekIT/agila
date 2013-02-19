#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QDebug>

class ModuleManager : public QObject
{
    Q_OBJECT

public:
    explicit ModuleManager(QObject *parent = 0);
    enum Module {Goods,Contractors,Sale,Purchase,Cash,Order,Warehouses,Reports,Settings,Price};

    void addModule(Module module);
    bool contains(Module module);

private:
    QVector<Module> modules;
};

#endif // MODULEMANAGER_H
