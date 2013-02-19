#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QToolButton>
#include "Components/ButtonStruct.h"
#include "Other/Application/ApplicationManager.h"

class ToolButton : public QToolButton
{
    Q_OBJECT

private:
    ButtonStruct structure;
    void setOptions();
    void setOptions(QSize size);

public:
    ToolButton(ButtonStruct structure, QWidget *parent = 0);
    ToolButton(ButtonStruct structure, QSize icon, QWidget *parent = 0);
    void setIconPolicy(QString url);
    void setIconPolicy(QString url, QSize icon);
    void setTopBottomLayout();
    
};

#endif // TOOLBUTTON_H
