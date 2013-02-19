#include "SettingsOwnerController.h"

SettingsOwnerController::SettingsOwnerController(QWidget *parent) :
        SettingsAbstractItemController(parent)
{
    this->view = new SettingsOwnerView(this,parent);
    ownerService = new OwnerService();
    insertOwnerData1();
}

SettingsOwnerController::SettingsOwnerController()
{
    delete ownerService;
}

void SettingsOwnerController::setModel()
{
}

void SettingsOwnerController::getOwnerData()
{
    o = ownerService->getActualOwner();
}

void SettingsOwnerController::insertOwnerData1()
{
    getOwnerData();
    view->getLineName()->setText(o.getName());
    view->getLineAdress()->setText(o.getAdress());
    view->getLinePostCode()->setText(o.getPostCode());
    view->getLineCity()->setText(o.getCity());
    view->getLineNIP()->setText(o.getNIP());
    view->getLineBankName()->setText(o.getBankName());
    view->getLineBankAccount()->setText(o.getBankAccount());
    view->getLineEMail()->setText(o.getEMail());
    view->getLineWebsite()->setText(o.getWebsite());
    view->getLinePhone1()->setText(o.getPhone(0));
    view->getLinePhone2()->setText(o.getPhone(1));
    view->getLinePhone3()->setText(o.getPhone(2));
    view->getTextAdditional()->setText(o.getAdditional());

    if(!o.getLogoPath().isEmpty())
    {
        QImage img (o.getLogoPath());
        if( !img.isNull() )
            view->getLogo()->setPixmap(QPixmap::fromImage(img).scaled(QSize(170,200),Qt::KeepAspectRatio));
    }
}

void SettingsOwnerController::setOwnerData()
{
    o.setName(view->getLineName()->text());
    o.setAdress(view->getLineAdress()->text());
    o.setPostCode(view->getLinePostCode()->text());
    o.setCity(view->getLineCity()->text());
    o.setNIP(view->getLineNIP()->text());
    o.setBankName(view->getLineBankName()->text());
    o.setBankAccount(view->getLineBankAccount()->text());
    o.setEMail(view->getLineEMail()->text());
    o.setWebsite(view->getLineWebsite()->text());
    o.setAdditional(view->getTextAdditional()->toPlainText());
    o.setPhone(0,view->getLinePhone1()->text());
    o.setPhone(1,view->getLinePhone2()->text());
    o.setPhone(2,view->getLinePhone3()->text());
}

int SettingsOwnerController::saveData()
{
    int ret  = view->getMessageBox()->createQuestionBox("Edycja danych dotyczących podmiotu !");
    if (ret == MessageBox::YES)
    {
        setOwnerData();

        Owner actualOwner = ownerService->getActualOwner();
        if(actualOwner.getId() == 0)
            ownerService->addOwner(o);
        else
            ownerService->editOwner(o);

        delete ownerService;
        view->emitChangesWereMade();
    }
    else if (ret == MessageBox::Cancel)
    {
        getOwnerData();
    }

    return 1;
}

void SettingsOwnerController::setLogo()
{
    QString path = (QFileDialog::getOpenFileName(view, "Otwórz Zdjęcie", QDir::homePath()));
    QImage img (path);

    if(!img.isNull())
    {
        o.setLogoPath(path);
        /*QDir dir(".");
        if ( !dir.exists("img") )
             dir.mkdir("img");
        dir.cd("img");

        if ( !dir.exists("logo") )
             dir.mkdir("logo");
        dir.cd("logo");

        if( QFile::exists(dir.absolutePath() + "/logo.img") )
            QFile::remove(dir.absolutePath() + "/logo.img");

        QFile::copy(path,dir.absolutePath() + "/logo.img");*/
        //img.load(dir.absolutePath() + "/logo.img");
        img.load(path);
        view->getLogo()->setPixmap(QPixmap::fromImage(img).scaled(QSize(170,200),Qt::KeepAspectRatio));
    }
}

void SettingsOwnerController::removeLogo()
{
    //QFile::remove("./img/logo/logo.img");
    o.setLogoPath("");
    view->getLogo()->setText("Brak zdefiniowanego\n\tlogo");
}

void SettingsOwnerController::autoPostalCode()
{
    QString postalCode = view->getLinePostCode()->text().trimmed();
    OtherService *otherService = new OtherService();
    QString city = otherService->getCityByPostalCode(postalCode);
    view->getLineCity()->setText(city);
    view->getLineCity()->setCursorPosition(city.length());
}

SettingsOwnerView *SettingsOwnerController::getView() {return view;}

