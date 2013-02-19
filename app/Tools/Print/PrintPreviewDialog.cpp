#include "PrintPreviewDialog.h"

PrintPreviewDialog::PrintPreviewDialog(QPrinter *drukarka)
{
    this->mainLayout= new QGridLayout();
    this->setLayout(mainLayout);
    this->print = new QPrintPreviewWidget(drukarka);
    addComponents();
}
PrintPreviewDialog::~PrintPreviewDialog()
{
    delete print;
    delete mainLayout;
}
void PrintPreviewDialog::show()
{
    this->setWindowState(Qt::WindowMaximized);
    print->setZoomFactor(1.3);

    print->show();
    this->exec();
}
QPrintPreviewWidget* PrintPreviewDialog::getPreview()
{
    return this->print;
}

void PrintPreviewDialog::addComponents()
{
    zoomPlus = new Button(ButtonStruct("Zoom +",QSize(70,28)));
    zoomMinus = new Button(ButtonStruct("Zoom -",QSize(70,28)));
    close = new Button(ButtonStruct("Zamknij",QSize(70,28)));
    zoomFactor = new QDoubleSpinBox();
    zoomFactor->setMaximumWidth(70);
    zoomFactor->setMinimum(0);
    zoomFactor->setMaximum(200);
    zoomFactor->setValue(130);
    mainLayout->setColumnMinimumWidth(1,35);
    mainLayout->addWidget(close,0,7);
    mainLayout->addWidget(zoomFactor,1,7);
    mainLayout->addWidget(zoomMinus,2,7);
    mainLayout->addWidget(zoomPlus,3,7);
    mainLayout->addWidget(print,0,0,6,1);
    connect(zoomPlus,SIGNAL(pressed()),this,SLOT(zoomPl()));
    connect(zoomMinus,SIGNAL(pressed()),this,SLOT(zoomMi()));
    connect(close,SIGNAL(clicked()),this,SLOT(close()));
    connect(zoomFactor,SIGNAL(valueChanged(double)),this,SLOT(changeZoom()));
}

void PrintPreviewDialog::zoomPl()
{
    zoomFactor->setValue((print->zoomFactor()+0.101)*100.0);
    changeZoom();
}

void PrintPreviewDialog::zoomMi()
{
    zoomFactor->setValue((print->zoomFactor()-0.101)*100.0);
    changeZoom();
}

void PrintPreviewDialog::changeZoom()
{
    print->setZoomFactor(zoomFactor->value()/100.0);
}
