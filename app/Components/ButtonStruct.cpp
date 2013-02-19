#include "ButtonStruct.h"
ButtonStruct::ButtonStruct(QString textValue, QString status, QString icon, QSize shape)
{
    this->textValue = textValue;
    this->status = status;
    this->shape = shape;
    this->icon = icon;
}

ButtonStruct::ButtonStruct(QString textValue, QString icon)
{
    this->textValue = textValue;
    this->status = textValue;
    this->icon = icon;
    shape.setWidth(0);
    shape.setHeight(0);
}

ButtonStruct::ButtonStruct(QString textValue, QString status, QSize shape)
{
    this->textValue = textValue;
    this->status = status;
    this->shape = shape;
}

ButtonStruct::ButtonStruct(QString textValue, QSize shape)
{
    this->textValue = textValue;
    this->status = textValue;
    this->shape = shape;
}

ButtonStruct::ButtonStruct(QString textValue)
{
    this->textValue = textValue;
    this->status = textValue;
    shape.setWidth(0);
    shape.setHeight(0);
}

ButtonStruct::ButtonStruct()
{
}

QString ButtonStruct::getStatus()
{
    return status;
}

QString ButtonStruct::getTextValue()
{
    return textValue;
}

QSize ButtonStruct::getShape()
{
    return shape;
}

QString ButtonStruct::getIcon()
{
    return icon;
}

void ButtonStruct::setStatus(QString status)
{
    this->status = status;
}

void ButtonStruct::setTextValue(QString textValue)
{
    this->textValue = textValue;
}

void ButtonStruct::setShape(QSize shape)
{
    this->shape = shape;
}

void ButtonStruct::setIcon(QString icon)
{
    this->icon = icon;
}

bool ButtonStruct::isNullIcon()
{
    return icon.isNull() || icon.isEmpty();
}
