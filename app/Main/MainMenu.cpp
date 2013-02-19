#include "MainMenu.h"

MainMenu::MainMenu(MainMenuController * controller)
{
    this->controller = controller;
    setInterface();
}

void MainMenu::setInterface()
{
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(logo = new QLabel(),1,1);
    layout->setColumnMinimumWidth(0,40);
    layout->setColumnMinimumWidth(2,40);
    /*QGridLayout *frameLayout = new QGridLayout();
    QFrame *frame = new QFrame();
    frame->setFrameShape(QFrame::Box);
    frame->setFrameShadow(QFrame::Raised);
    frame->setMaximumSize(150,45);
    frame->setLayout(frameLayout);

    file = new Button(ButtonStruct("logo", QSize(70,70)),QSize(65,65));
    save = new Button(ButtonStruct("S","Zapisz", QSize(22,22)));
    print = new Button(ButtonStruct("P","Drukuj", QSize(22,22)));
    back = new Button(ButtonStruct("B","Cofnij", QSize(22,22)));
    next = new Button(ButtonStruct("N","Ponów", QSize(22,22)));
    help = new Button(ButtonStruct("H","Pomoc", QSize(22,22)));

    frameLayout->addWidget(save,0,1,Qt::AlignTop);
    frameLayout->addWidget(print,0,2,Qt::AlignTop);
    frameLayout->addWidget(back,0,3,Qt::AlignTop);
    frameLayout->addWidget(next,0,4,Qt::AlignTop);
    frameLayout->addWidget(help,0,5,Qt::AlignTop);

    this->setLayout(layout);
    layout->addWidget(file,0,1);
    layout->addWidget(frame,0,2);

    connect(help,SIGNAL(clicked()),controller,SLOT(showHelp()));*/
    QImage img (":/image-theme/logo.png");
    logo->setPixmap(QPixmap::fromImage(img));
    this->setLayout(layout);
}

Button *MainMenu::getFile()
{
    return file;
}

Button *MainMenu::getSave()
{
    return save;
}

Button *MainMenu::getPrint()
{
    return print;
}

Button *MainMenu::getNext()
{
    return next;
}

Button *MainMenu::getBack()
{
    return back;
}

Button *MainMenu::getHelp()
{
    return help;
}
