#include "Button.h"

Button::Button(ButtonStruct structure, QWidget *parent) : QPushButton(parent)
{
    this->structure = structure;
    setOptions();
    if(!structure.isNullIcon()) setIconPolicy(structure.getIcon());
}

Button::Button(ButtonStruct structure, QSize icon, QWidget *parent) : QPushButton(parent)
{
    this->structure = structure;
    setOptions();
    if(!structure.isNullIcon()) setIconPolicy(structure.getIcon(),icon);
}

void Button::setOptions()
{
    this->setText(this->structure.getTextValue());
    this->setStatusTip(this->structure.getStatus());
    this->setCursor(QCursor(Qt::PointingHandCursor));
    this->setMinimumSize(this->structure.getShape().width(),
                         this->structure.getShape().height());
    this->setMaximumSize(this->structure.getShape().width(),
                         this->structure.getShape().height());
    //this->setFocusPolicy(Qt::NoFocus);
}

void Button::setIconPolicy(QString url)
{
    this->setIcon(QIcon(":/image-theme/" + url + ".png"));
    int size = structure.getShape().height() * 0.7;
    if(!structure.getTextValue().isEmpty()) this->setIconSize(QSize(size,size));
    else this->setIconSize(QSize(22,22));
}

void Button::setIconPolicy(QString url, QSize icon)
{
    this->setIcon(QIcon(":/image-theme/" + url + ".png"));
    if(!structure.getTextValue().isEmpty()) this->setIconSize(icon);
    else this->setIconSize(QSize(22,22));
}
