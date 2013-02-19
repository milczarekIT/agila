#ifndef BUTTONSTRUCT_H
#define BUTTONSTRUCT_H

#include <QSize>
#include <QString>

class ButtonStruct
{
private:
    QString status;
    QString textValue;
    QString icon;
    QSize shape;

public:
    ButtonStruct(QString textValue, QString status, QString icon, QSize shape);
    ButtonStruct(QString textValue, QString icon);

    ButtonStruct(QString textValue, QString status, QSize shape);
    ButtonStruct(QString textValue, QSize shape);
    ButtonStruct(QString textValue);
    ButtonStruct();
    QString getStatus();
    QString getIcon();
    QString getTextValue();
    QSize getShape();
    void setStatus(QString status);
    void setTextValue(QString textValue);
    void setShape(QSize shape);
    void setIcon(QString icon);
    bool isNullIcon();
};

#endif // BUTTONSTRUCT_H
