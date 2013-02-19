#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include <QString>
#include <QVariant>
#include <QMap>
#include <QDebug>
#include <QStringList>

/**
  * Wersja C++ dla JSONObject
  * @author Bartosz Milczarek
  */
class JsonObject
{
private:
    QString removeFirstChar(QString str);
    QString removeLastChar(QString str);

    /**
      * usuwa cudzysłowy z początku i końca łańcucha
      */
    QString removeQuotas(QString str);

    QMap<QString, QVariant> hashMap;

public:
    JsonObject(QString strObject);

    int getInt(QString key);
    QString getString(QString key);
};

#endif // JSONOBJECT_H
