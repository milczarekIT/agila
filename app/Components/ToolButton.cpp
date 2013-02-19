#include "ToolButton.h"

ToolButton::ToolButton(ButtonStruct structure, QWidget *parent) : QToolButton(parent)
{
    this->structure = structure;
    setOptions();
    if(!structure.isNullIcon()) setIconPolicy(structure.getIcon());
}

ToolButton::ToolButton(ButtonStruct structure, QSize icon, QWidget *parent) : QToolButton(parent)
{
    this->structure = structure;
    setOptions();
    if(!structure.isNullIcon()) setIconPolicy(structure.getIcon(),icon);
}

void ToolButton::setOptions()
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

void ToolButton::setIconPolicy(QString url)
{
    this->setIcon(QIcon(":/image-theme/" + url + ".png"));
    int size = structure.getShape().height() * 0.7;
    if(!structure.getTextValue().isEmpty()) this->setIconSize(QSize(size,size));
    else this->setIconSize(QSize(22,22));
}

void ToolButton::setIconPolicy(QString url, QSize icon)
{
    this->setIcon(QIcon(":/image-theme/" + url + ".png"));
    if(!structure.getTextValue().isEmpty()) this->setIconSize(icon);
    else this->setIconSize(QSize(22,22));
}

void ToolButton::setTopBottomLayout() {
    this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}
