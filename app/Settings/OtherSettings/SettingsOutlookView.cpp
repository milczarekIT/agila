#include "SettingsOutlookView.h"

SettingsOutlookView::SettingsOutlookView(SettingsOutlookController *controller, QWidget *parent) :
        SettingsAbstractItemView(parent)
{
    this->controller = controller;
    initGraphicElements();
    setGraphicSettings();
    setInterfaceController();
}

void SettingsOutlookView::initGraphicElements() {
    mainLayout->addWidget(new QLabel("Ustawienia wyglądu: "),1,1);
    mainLayout->addWidget(blue = new QLabel(),2,3);
    mainLayout->addWidget(grey = new QLabel(),6,3);
    mainLayout->addWidget(radioStandard = new QRadioButton("Systemowy"),4,4);
    mainLayout->addWidget(radioBlue = new QRadioButton("Niebieski"),2,4);
    mainLayout->addWidget(radioGrey = new QRadioButton("Szary"),6,4);
    mainLayout->addWidget(save = new Button(ButtonStruct("Zapisz",QSize(260,30)),this),4,3,Qt::AlignCenter);
}

void SettingsOutlookView::setGraphicSettings() {
    mainLayout->setRowMinimumHeight(3,20);
    mainLayout->setRowMinimumHeight(5,20);
    mainLayout->setRowMinimumHeight(7,10);
    setPhoto(":/image-theme/blue",blue);
    setPhoto(":/image-theme/grey",grey);
}

void SettingsOutlookView::setPhoto(QString path, QLabel *label) {
    QImage img (path + ".png");

    if(!img.isNull())
        label->setPixmap(QPixmap::fromImage(img).scaled(QSize(300,300),Qt::KeepAspectRatio));
}

void SettingsOutlookView::setInterfaceController() {
    connect(save,SIGNAL(clicked()),controller,SLOT(changeStyleSheet()));
}

QRadioButton *SettingsOutlookView::getRadioGrey() {
    return radioGrey;
}

QRadioButton *SettingsOutlookView::getRadioBlue() {
    return radioBlue;
}

QRadioButton *SettingsOutlookView::getRadioStandard() {
    return radioStandard;
}
