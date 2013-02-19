#include "JsonObject.h"

JsonObject::JsonObject(QString strObject)
{
    strObject = strObject.remove(0,1);
    strObject = strObject.remove(strObject.length()-1, 1);

    QStringList nameValues = strObject.split(",");
    for(int i = 0; i < nameValues.size(); i++)
    {
        QString nameValuePair = nameValues.at(i);
        int indexOfColon = nameValues.at(i).indexOf(":");

        // before colon
        QString key = nameValuePair.mid(0, indexOfColon-1);
        key = this->removeQuotas(key);

        // after colon
        QString val = nameValuePair.mid(indexOfColon+1);
        val = val.replace("\\/", "/");
        val = this->removeQuotas(val);


        hashMap.insert(key, val);
    }
}

QString JsonObject::removeQuotas(QString str) {
    if(QString(str.at(0)) == QString("\""))
        str = str.mid(1);
    if(QString(str[str.length()-1]) == QString("\""))
        str = str.mid(0, str.length()-1);

    return str;
}

int JsonObject::getInt(QString key) {
    return hashMap.value(key).toInt();
}

QString JsonObject::getString(QString key) {
    return hashMap.value(key).toString();
}
