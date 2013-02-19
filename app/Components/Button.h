#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include "Components/ButtonStruct.h"
#include "Other/Application/ApplicationManager.h"

class Button : public QPushButton
{
    Q_OBJECT

private:
    ButtonStruct structure;
    void setOptions();
    void setOptions(QSize size);

public:
    Button(ButtonStruct structure, QWidget *parent = 0);
    Button(ButtonStruct structure, QSize icon, QWidget *parent = 0);
    void setIconPolicy(QString url);
    void setIconPolicy(QString url, QSize icon);
};

#endif // BUTTON_H
