#include "GoodsDialogController.h"

GoodsDialogController::GoodsDialogController(QWidget *parent)
{
    this->view = new GoodsDialogView(parent,this);
    model=new QStandardItemModel();
    service = new GoodsService();
    featureModel = new FeatureModel();
    unitModel = new UnitModel();
    settingsPreferences = new SettingsPreferencesService();
    taxModel = new TaxModel();
    goodsGroupModel = new GoodsGroupModel();
    tableStateManager = new TableStateManager();
    validator = new GoodsValidator(view);
    autoSymbol = true;
    priceCalculatingEnabled = false;

    fillBox(view->getBoxTax(),taxModel->getTaxes(true));
    view->getBoxGoodGroup()->addItem("BRAK", 0);
    fillBox(view->getBoxGoodGroup(),goodsGroupModel->getGoodsGroups());
    QVector<Unit> units = unitModel->getUnits();
        for(int i = 0; i < units.size(); i++)
            view->getBoxUnit()->addItem(units[i].getName(), QVariant::fromValue(units[i].getId()));
    calculatePricesForTax(0);
    initOldGood();
    restoreTableState();
}   
GoodsDialogController::~GoodsDialogController()
{
    saveTableState();
    delete model;
    delete service;
    delete featureModel;
    delete unitModel;
    delete taxModel;
    delete goodsGroupModel;
    delete validator;
    delete settingsPreferences;
    delete tableStateManager;
}

void GoodsDialogController::initOldGood() {
    int currentIndex;
    int defaultId;

    // tax
    currentIndex = view->getBoxTax()->currentIndex();
    defaultId = view->getBoxTax()->itemData(currentIndex).toInt();
    oldGood.setTax(taxModel->getTax(defaultId));

    // unit
    currentIndex = view->getBoxUnit()->currentIndex();
    defaultId = view->getBoxUnit()->itemData(currentIndex).toInt();
    oldGood.setUnit(unitModel->getUnit(defaultId));

    // goodGroup
    currentIndex = view->getBoxGoodGroup()->currentIndex();
    defaultId = view->getBoxGoodGroup()->itemData(currentIndex).toInt();
    oldGood.setGoodsGroup(goodsGroupModel->getGoodsGroup(defaultId));
}

bool GoodsDialogController::exec()
{
    goodGroupVal = 0;

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        view->addWarehouseSelection();

    view->getRadioGood()->setChecked(true);
    view->getPicture()->setText(" Brak zdjęcia\n Kliknij PPM aby dodać");
    setDefaultMargins();

    if (view->exec())
    {
        getGoodData();
        if(isAddingOnlyToActualWarehouse())
            service->addGood(good);
        else
            service->addGoodForAllWarehouses(good);

        return true;
    }
    return false;

}

bool GoodsDialogController::isAddingOnlyToActualWarehouse() {
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        int currentIndex = view->getAddToWarehouseComboBox()->currentIndex();
        int itemData = view->getAddToWarehouseComboBox()->itemData(currentIndex).toInt();

        return (itemData != 0);
    }
    else
        return true;
}

bool GoodsDialogController::exec(int id)
{
    good = service->getGood(id);
    oldGood = service->getGood(id);
    initPricesInEdit();
    goodGroupVal=good.getGoodsGroup().getId();
    view->getLineSymbol()->setText (good.getSymbol());
    view->getLineName()->setText (good.getName());
    view->getLinePkwiu()->setText (good.getPkwiu());
    view->getLineWeight()->setText(QString::number(good.getWeight(),',', 2));
    view->getTextDescription()->setText(good.getDescription());
    view->getBoxGoodGroup()->setCurrentIndex(view->getBoxGoodGroup()->findData(QVariant::fromValue(good.getGoodsGroup().getId())));
    view->getBoxTax()->setCurrentIndex(view->getBoxTax()->findData(QVariant::fromValue(good.getTax().getId())));
    view->getBoxUnit()->setCurrentIndex(view->getBoxUnit()->findData(QVariant::fromValue(good.getUnit().getId())));
    if(good.getType() == Goods::GOOD)
        view->getRadioGood()->setChecked(true);
    else
        view->getRadioService()->setChecked(true);

    QImage image(good.getFoto());
    if (image.isNull())
        view->getPicture()->setText("Brak zdjęcia\nKliknij PPM aby dodać");
    else
        view->getPicture()->setPixmap(QPixmap::fromImage(image).scaled(QSize(170,200),Qt::KeepAspectRatio));
    updateFeatureModel(view->getBoxGoodGroup()->currentIndex());

    if (view->exec()){
        good = getGoodData();
        good.setId(id);
        if(isChangesOccured())
        {
            service->editGood(good);
        }

        return true;
    }
    return false;

}

void GoodsDialogController::initPricesInEdit()
{
    double magNet = good.getPriceNet(Price::MAG).toString().toDouble();
    double magGross = good.getPriceGross(Price::MAG).toString().toDouble();
    double priceAGross = good.getPriceGross(Price::A).toString().toDouble();
    double priceNet, priceGross;
    for(int row = 0; row < 3; row++)
    {
        if(row == 0)
        {
            priceNet = good.getPriceNet(Price::A).toString().toDouble();
            priceGross = good.getPriceGross(Price::A).toString().toDouble();
        }
        else if(row == 1)
        {
            priceNet = good.getPriceNet(Price::B).toString().toDouble();
            priceGross = good.getPriceGross(Price::B).toString().toDouble();
        }
        else if(row == 2)
        {
            priceNet = good.getPriceNet(Price::C).toString().toDouble();
            priceGross = good.getPriceGross(Price::C).toString().toDouble();
        }

        view->getTablePrices()->setItem(row,0,new QTableWidgetItem(QString::number(priceNet, ',', 2).replace(".", ",")));
        view->getTablePrices()->setItem(row,1,new QTableWidgetItem(QString::number(priceGross, ',', 2).replace(".", ",")));
        if(magGross != 0.00)
            view->getTablePrices()->setItem(row,2,new QTableWidgetItem(QString::number((((priceGross-magGross)/magGross)*100.00),'.',2).replace(".",",")));
        else
            view->getTablePrices()->setItem(row,2,new QTableWidgetItem(QString::number((0.00),'.',2).replace(".",",")));
        if(row != 0)
        {
            double discount = (1 - (priceGross/priceAGross))*100.00;
            view->getTablePrices()->setItem(row,3,new QTableWidgetItem(QString::number(discount,'.',2).replace(".",",")));
        }

    }
    view->getTablePrices()->setItem(0,3, new QTableWidgetItem()); // upust A - nie istnieje
    view->getTablePrices()->item(0,3)->setFlags(Qt::ItemIsUserCheckable);

    // ceny zakupu
    view->getLinePriceMagNet()->setText(QString::number(magNet, ',', 2).replace(".", ","));
    view->getLinePriceMagGross()->setText(QString::number(magGross, ',', 2).replace(".", ","));

    this->priceCalculatingEnabled = true;
}

Goods GoodsDialogController::getGoodData()
{
    if(view->getRadioGood()->isChecked())
        good.setType(Goods::GOOD);
    else if(view->getRadioService()->isChecked())
        good.setType(Goods::SERVICE);
    good.setSymbol(view->getLineSymbol()->text());
    good.setName (view->getLineName()->text());
    good.setPkwiu (view->getLinePkwiu()->text());
    if(!view->getLinePriceMagNet()->text().isEmpty())
    {
    good.setPriceNet(Price::A, view->getTablePrices()->item(0,0)->text().toDouble());
    good.setPriceGross(Price::A, view->getTablePrices()->item(0,1)->text().toDouble());
    good.setPriceNet(Price::B, view->getTablePrices()->item(1,0)->text().toDouble());
    good.setPriceGross(Price::B, view->getTablePrices()->item(1,1)->text().toDouble());
    good.setPriceNet(Price::C, view->getTablePrices()->item(2,0)->text().toDouble());
    good.setPriceGross(Price::C, view->getTablePrices()->item(2,1)->text().toDouble());
    }
    good.setPriceNet (Price::MAG, view->getLinePriceMagNet()->text().toDouble());
    good.setPriceGross (Price::MAG, view->getLinePriceMagGross()->text().toDouble());
    good.setDescription(view->getTextDescription()->toPlainText());
    good.setWeight(view->getLineWeight()->text().toFloat());

    int taxId = view->getBoxTax()->itemData(view->getBoxTax()->currentIndex()).toInt();
    Tax t = taxModel->getTax(taxId);
    good.setTax(t);

    int unitId = view->getBoxUnit()->itemData(view->getBoxUnit()->currentIndex()).toInt();
    Unit u = unitModel->getUnit(unitId);
    good.setUnit(u);


    int groupId = view->getBoxGoodGroup()->itemData(view->getBoxGoodGroup()->currentIndex()).toInt();
    GoodsGroup gg = this->goodsGroupModel->getGoodsGroup(groupId);
    good.setGoodsGroup(gg);

    good.setFeatures(getGoodFeatures());

    if(good.getFoto().isNull()) good.setFoto("");
    else copyPhotoToProgramDir();

    return good;
}

void GoodsDialogController::checkChanges()
{
    good = getGoodData();
    good.setId(oldGood.getId());
    if(validator->isEmptyForm()) {
        view->reject(); }
    else if(isChangesOccured())
    {
        MessageBox *messageBox = new MessageBox();
        if (messageBox->createQuestionBox("Dokonano zmian") == MessageBox::YES)
            validator->validateForm();
        else
            view->reject(); // zmiany dokonane, ale użytkowik chce anulować
    }
    else {
         view->reject(); // nie dokonano zmian, anuluj
     }
}

void GoodsDialogController::addTax()
{
    Tax tax;
    AddGroup *dialog = new AddGroup(this);
    dialog->setWindowTitle("Dodaj grupę");

    if(dialog->exec())
    {
        tax.setActiveInApp(true);
        tax.setName(dialog->getBoxName()->currentText()+" "+dialog->getLineValue()->text()+"");
        tax.setValue(dialog->getLineValue()->text().toFloat());
        tax.setShortName(dialog->getLineEdit()->text());
        taxModel->addTax(tax);

        view->getBoxTax()->clear();
        fillBox(view->getBoxTax(),taxModel->getTaxes(true));

        // ustawienie nowododanej grupy
        int currentIndex = view->getBoxTax()->findText(tax.getName());
        view->getBoxTax()->setCurrentIndex(currentIndex);

        view->settingsChanged("GoodsGroup");
    }

    delete dialog;
}

void GoodsDialogController::removeTax ()
{
    int currentIndex = view->getBoxTax()->currentIndex();
    int taxId = view->getBoxTax()->itemData(currentIndex).toInt();
    MessageBox messageBox;
    if(taxModel->getTax(taxId).getName().contains("Stawka zw."))
    {
        messageBox.createInfoBox("Nie można usunąć stawki zw. !");
    }
    else
    {
    if(taxId != 0)
    {

        int ret = messageBox.createQuestionBox("Usuwanie stawki VAT: " + view->getBoxTax()->currentText());

        if(ret == MessageBox::YES)
        {
            taxModel->removeTax(taxId);

            // refresh
            view->getBoxTax()->clear();
            fillBox(view->getBoxTax(),taxModel->getTaxes(false));

        }
    }
    }


}


void GoodsDialogController::updateFeatureModel (int index)
{
    QStringList headers;
    QVector<Feature> fv;
    int curIndex = view->getBoxGoodGroup()->itemData(index).toInt();
    if (curIndex == good.getGoodsGroup().getId())
        fv = good.getFeatures();
    else
        fv = featureModel->getFeaturesForGroup(curIndex);
    model->clear();
    for (int i=0; i < fv.size(); i++)
    {
    Feature f = fv.at(i);
    headers<<f.getName();
    model->setItem(i,0,new QStandardItem(f.getValue()));
    model->setItem(i,1,new QStandardItem(QString::number(f.getId())));
    }
    model->setVerticalHeaderLabels(headers);
    view->getTableFeatures()->setModel(model);
    view->getTableFeatures()->setColumnWidth(0,500);
    view->getTableFeatures()->setColumnHidden(1,true);
    view->getTableFeatures()->horizontalHeader()->hide();
}

QVector<Feature> GoodsDialogController::getGoodFeatures ()
{
    QVector<Feature> fv;
    Feature f;
    for (int i=0 ; i<model->rowCount() ;i++)
    {
        f.setId(model->item(i,1)->text().toInt());
        f.setValue(model->item(i,0)->text().left(70));
        fv.push_back(f);
    }
    return fv;
}

GoodsDialogView* GoodsDialogController::getView()
{
    return view;
}


void GoodsDialogController::dialogGoodsGroup()
{
    GoodsGroup gg;
    InsertTextDialog dialog(this);
    if(dialog.exec())
    gg.setName(dialog.getLineEdit()->text().left(60));
    goodsGroupModel->addGoodsGroup(gg);
}

void GoodsDialogController::deleteGoodsGroup ()
{
    goodsGroupModel->removeGoodsGroup(view->getBoxGoodGroup()->currentIndex()+1);
}


void GoodsDialogController::fotoMenuAcces(QAction *action)
{
    if (action->text()=="Ustaw zdjęcie")
    {
        QString path = (QFileDialog::getOpenFileName(this,
                     tr("Otwórz Zdjęcie"), QDir::homePath()));
        QImage img (path);
        if(!img.isNull()){
        view->getPicture()->setPixmap(QPixmap::fromImage(img).scaled(QSize(170,200),Qt::KeepAspectRatio));
        good.setFoto(path);}
    }
    if (action->text()=="Usuń zdjęcie")
    {
        view->getPicture()->setText("Brak zdjęcia\nKliknij PPM aby dodać");
        QFile::remove(good.getFoto());
        good.setFoto("");
    }
}

void GoodsDialogController::nameTyping (const QString & text )
{
    if (!autoSymbol) return;
    QString symbol = text;
    symbol.remove(QRegExp("[%$*+?.()[{}\\]\\/\\^\"]"));
    symbol.remove("\\");
    view->getLineSymbol()->setText(symbol.toUpper());
}

void GoodsDialogController::checkAutoSymbol (const QString & text )
{
    if(text.isEmpty()) {autoSymbol=true;
                nameTyping(view->getLineName()->text());}
    else autoSymbol=false;
}

void GoodsDialogController::checkRequredFields()
{
    if(validator->isEmptyForm())
    {
        MessageBox *messageBox = new MessageBox();
        messageBox->createInfoBox("Uzupełnij formularz!");
    }
    else
    validator->validateForm();
}

void  GoodsDialogController:: fillBox(QComboBox *box,QVector<Tax> values)
{
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}

bool GoodsDialogController::isChangesOccured() {
    return !(good == oldGood);
}

void  GoodsDialogController:: fillBox(QComboBox *box,QVector<GoodsGroup> values)
{
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}

void GoodsDialogController::copyPhotoToProgramDir()
{
    QDir dir(".");
    QFileInfo pathInfo( good.getFoto() );
    if (!dir.exists("img"))dir.mkdir("img");
    dir.cd("img");
    if (!dir.exists("photos"))dir.mkdir("photos");
    dir.cd("photos");
    if(QFile::exists(dir.absolutePath()+"/" + pathInfo.fileName()))
        QFile::remove(dir.absolutePath()+"/" + pathInfo.fileName());
    QFile::copy(good.getFoto(),dir.absolutePath()+"/" + pathInfo.fileName());
    good.setFoto(dir.absolutePath()+"/" + pathInfo.fileName());
}

void GoodsDialogController::calculatePricesForTax(int index)
{
    tax = taxModel->getTax(view->getBoxTax()->itemData(index).toInt()).getValue()/100.0;

    if(priceCalculatingEnabled)
        calculateAllPricesGross();
}

void GoodsDialogController::calculateAllPricesGross()
{
    for(int row = 0; row < 3; row++)
        calculatePriceGrossFromNetForLevel(row);

    // przliczenie i zapisanie ceny mag brutto w celu poprawnego zapisu do bazy
    double priceNetMag = view->getLinePriceMagNet()->text().toDouble();
    double priceGrossMag = (1+tax)*priceNetMag;
    view->getLinePriceMagGross()->setText(QString::number(priceGrossMag, ',',2).replace(".", ",")); // zapisanie ceny mag brutto, w celu poprawnego zapisu do bazy
}


void GoodsDialogController::calculatePrices(QTableWidgetItem* item)
{
    if(priceCalculatingEnabled)
    {
        priceCalculatingEnabled = false;

        double insertedValue = QVariant(item->text()).toDouble();
        this->setPriceTableItem(item->row(), item->column(), insertedValue); // wstawienie wpisanej wartości, użytkownik mógł wpisać bez miejsc po przecinku, wiec zamiana

        if(item->column() == 0) // kolumna cena netto
        {
            this->calculatePriceGrossFromNetForLevel(item->row());
            if(view->getLinePriceMagGross()->text().isEmpty()) // jesli cena zakupu pusta
            {
                calculatePriceMagByMarginA();
            }
            else
            {
                calculateMarginFromPrice(item->row());
            }

            if(item->row() != 0) // jeśli level cen inny niż A, policz upust dla swojego wiersza (B,C)
            {
                calculateDiscountFromPrice(item->row());
            }
            else
            {
                updateDiscontOrPriceForLevelBC(); // wylicza cene B,C jeśli jest 0,00, lub aktualizuje rabat jeśli cena jest już wpisnana (inna niż 0,00)
            }
        }
        else if(item->column() == 1) // kolumna cena brutto
        {
            this->calculatePriceNetFromGrossForLevel(item->row());
            if(view->getLinePriceMagGross()->text().isEmpty()) // jesli cena zakupu pusta
            {
                calculatePriceMagByMarginA();
            }
            else
            {
                calculateMarginFromPrice(item->row());
            }
            if(item->row() != 0) // jeśli level cen inny niż A, policz upust dla swojego wiersza (B,C)
            {
                calculateDiscountFromPrice(item->row());
            }
            else
            {
                updateDiscontOrPriceForLevelBC(); // wylicza cene B,C jeśli jest 0,00, lub aktualizuje rabat jeśli cena jest już wpisnana (inna niż 0,00)
            }
        }
        else if(item->column() == 2) // kolumna narzut
        {
            if(!view->getLinePriceMagNet()->text().isEmpty()) // cena zakupu netto nie może być pusta, do przeliczeń narzutu
            {
                this->calculatePriceNetFromMarginForLevel(item->row());
                this->calculatePriceGrossFromNetForLevel(item->row());
            }

            if(item->row() != 0) // jeśli level cen inny niż A, policz upust dla swojego wiersza (B,C)
            {
                calculateDiscountFromPrice(item->row());
            }
            else
            {
                updateDiscontOrPriceForLevelBC(); // wylicza cene B,C jeśli jest 0,00, lub aktualizuje rabat jeśli cena jest już wpisnana (inna niż 0,00)
            }
        }
        else if(item->column() ==3) // kolumna upust
        {
            if(item->row() != 0) // dla ceny A nie wpisujemy upustu
            {
                this->calculatePriceGrossFromDiscountForLevel(item->row());
                this->calculatePriceNetFromGrossForLevel(item->row());
                this->calculateMarginFromPrice(item->row());
            }
        }

        priceCalculatingEnabled = true;
    }
}
void GoodsDialogController::setPriceTableItem(int row, int col, double value)
{
    view->getTablePrices()->item(row, col)->setText(QString::number(value, ',', 2).replace(".", ","));
}

void GoodsDialogController::calculatePriceGrossFromNetForLevel(int row)
{
    double priceNet = view->getTablePrices()->item(row, 0)->text().toDouble();
    double priceGross = (1+tax)*priceNet;
    this->setPriceTableItem(row, 1, priceGross);
}

void GoodsDialogController::calculatePriceNetFromGrossForLevel(int row)
{
    double priceGross = view->getTablePrices()->item(row, 1)->text().toDouble();
    double priceNet = priceGross/(1+tax);
    this->setPriceTableItem(row, 0, priceNet);
}

void GoodsDialogController::calculatePriceNetFromMarginForLevel(int row)
{
    double priceNetMag = view->getLinePriceMagNet()->text().toDouble();
    double marginInRow = view->getTablePrices()->item(row, 2)->text().toDouble();

    double priceNetInRow = priceNetMag*(1.00+(marginInRow/100.00));
    this->setPriceTableItem(row, 0, priceNetInRow);
}

void GoodsDialogController::calculatePriceGrossFromDiscountForLevel(int row)
{
    double discountInRow = view->getTablePrices()->item(row, 3)->text().toDouble();
    double priceGrossA = view->getTablePrices()->item(0, 1)->text().toDouble();

    double priceGrossInRow = (1.00 - (discountInRow/100.00))*priceGrossA;
    this->setPriceTableItem(row, 1, priceGrossInRow);
}

void GoodsDialogController::calculatePriceMagByMarginA()
{
    double priceNetA = view->getTablePrices()->item(0, 0)->text().toDouble();
    double marginA = view->getTablePrices()->item(0, 2)->text().toDouble();

    double priceMagNet = priceNetA/((marginA/100)+1);
    double priceMagGross = priceMagNet*(1+tax);
    view->getLinePriceMagNet()->setText(QString::number(priceMagNet, ',', 2).replace(".", ","));
    view->getLinePriceMagGross()->setText(QString::number(priceMagGross, ',', 2).replace(".", ","));
}



//zwykle ustawianie cenny netto zakupu
void GoodsDialogController::setPriceMag(double value)
{
    QString str;
    view->getLinePriceMagNet()->setText(str.setNum(value, ',', 2).replace(QRegExp("[.]"),","));
}
//wyliczanie cenn netto
void GoodsDialogController::calculatePricesMagNet(int row)
{
    QString str;
    view->getTablePrices()->item(row,0)->setText(str.setNum(view->getTablePrices()->item(row,1)->text().toDouble()/(1+tax), ',', 2).replace(QRegExp("[.]"),","));
}

void GoodsDialogController::calculateMarginFromPrice(int row)
{
    double priceSaleNet = view->getTablePrices()->item(row, 0)->text().toDouble();
    double priceMagNet = view->getLinePriceMagNet()->text().toDouble();

    if(priceMagNet != 0.00)
    {
        double margin = ((priceSaleNet - priceMagNet)/priceMagNet)*100;
        this->setPriceTableItem(row, 2, margin);
    }

}
//wyliczanie upustow z cenn
void GoodsDialogController::calculateDiscountFromPrice(int row)
{
    double priceGrossA = view->getTablePrices()->item(0, 1)->text().toDouble();
    double priceGrossInRow = view->getTablePrices()->item(row, 1)->text().toDouble();

    if(priceGrossA != 0.00)
    {
        double discountInRow = (1 - (priceGrossInRow/priceGrossA))*100;
        this->setPriceTableItem(row, 3, discountInRow);
    }

}

void GoodsDialogController::updateDiscontOrPriceForLevelBC()
{
    double priceGrossA = view->getTablePrices()->item(0, 1)->text().toDouble();
    double priceGrossB = view->getTablePrices()->item(1, 1)->text().toDouble();
    double priceGrossC = view->getTablePrices()->item(2, 1)->text().toDouble();

    if(priceGrossA != 0.00 & priceGrossB != 0.00) // jesli cena B juz uzupelniona, wylicza rabat
    {
        double discountB = (1 - (priceGrossB/priceGrossA))*100;
        this->setPriceTableItem(1, 3, discountB);
    }

    if(priceGrossA != 0.00 & priceGrossC != 0.00) // jescli cena C juz uzupelniona, wylicza rabat
    {
        double discountC = (1 - (priceGrossC/priceGrossA))*100;
        this->setPriceTableItem(2, 3, discountC);
    }

    if(priceGrossA != 0.00 & priceGrossB == 0.00)
    {
        double discountB = view->getTablePrices()->item(1, 3)->text().toDouble();
        double priceAGross = view->getTablePrices()->item(0,1)->text().toDouble();

        double priceBGross = priceAGross - ((discountB/100)*priceAGross); // price gross
        this->setPriceTableItem(1,1, priceBGross);

        this->calculatePriceNetFromGrossForLevel(1); // price net
        this->calculateMarginFromPrice(1);
    }

    if(priceGrossA != 0.00 & priceGrossC == 0.00)
    {
        double discountC = view->getTablePrices()->item(2, 3)->text().toDouble();
        double priceAGross = view->getTablePrices()->item(0,1)->text().toDouble();

        double priceCGross = priceAGross - ((discountC/100)*priceAGross); // price Gross
        this->setPriceTableItem(2,1, priceCGross);

        this->calculatePriceNetFromGrossForLevel(2); // price Net
        this->calculateMarginFromPrice(2); // margin

    }
}

//wyliczanie brutto
void GoodsDialogController::calculatePricesMagGross(int row)
{
    QString str;
    view->getTablePrices()->item(row,1)->setText(str.setNum(view->getTablePrices()->item(row,0)->text().toDouble()*(1+tax), ',', 2).replace(QRegExp("[.]"),","));
}
//przeliczanie wszystkich cen na podstawie ceny magazynowej
void GoodsDialogController::calculateAllPricesFromMag()
{
    double priceNetMag = view->getLinePriceMagNet()->text().toDouble();
    double priceGrossMag = (1+tax)*priceNetMag;
    view->getLinePriceMagGross()->setText(QString::number(priceGrossMag, ',',2).replace(".", ",")); // zapisanie ceny mag brutto, w celu poprawnego zapisu do bazy


    if(priceNetMag != 0.00)
    {
        for(int row = 0; row < 3; row++)
        {
            if(isPriceNetGrossSet(row))
            {
                // wyliczenie nowych narzutów i upustów

                calculateMarginFromPrice(row);

                if(row != 0) // price A
                    calculateDiscountFromPrice(row);
            }
            else // wyliczenie cen na podstawie ustawionych narzutów i upustów
            {
                if(row == 0) // price A
                {
                    calculatePriceNetFromMarginForLevel(row); // net from margin
                    calculatePriceGrossFromNetForLevel(row); // gross from net
                }
                else
                {
                    calculatePriceGrossFromDiscountForLevel(row); // gross from discount
                    calculatePriceNetFromGrossForLevel(row); // net from gross
                    calculateMarginFromPrice(row); // margin from net
                }
            }
        }
    }
}

bool GoodsDialogController::isPriceNetGrossSet(int row)
{
    double priceNet = view->getTablePrices()->item(row, 0)->text().toDouble();
    double priceGross = view->getTablePrices()->item(row, 1)->text().toDouble();

    return (priceNet != 0.00 && priceGross != 0.00);
}

//pierwsze wczytanie deafultowych upustow i marz
void GoodsDialogController::setDefaultMargins()
{
    QString str;
    for(int row=0; row<3;row++)
    {
        view->getTablePrices()->setItem(row, 0, new QTableWidgetItem(str.setNum(0.00, ',', 2).replace(".", ",")));
        view->getTablePrices()->setItem(row, 1, new QTableWidgetItem(str.setNum(0.00, ',', 2).replace(".", ",")));
    }

     view->getTablePrices()->setItem(0,2,new QTableWidgetItem(str.setNum(settingsPreferences->getDefaultGoodsMargin(), ',', 2).replace(QRegExp("[.]"),",")));
     view->getTablePrices()->setItem(0,3,new QTableWidgetItem(""));
     view->getTablePrices()->item(0, 3)->setFlags(Qt::ItemIsUserCheckable);

     view->getTablePrices()->setItem(1,3,new QTableWidgetItem(str.setNum(settingsPreferences->getDefaultGoodsDiscountB(), ',', 2).replace(QRegExp("[.]"),",")));
     view->getTablePrices()->setItem(1,2,new QTableWidgetItem(str.setNum(0.0, ',', 2).replace(QRegExp("[.]"),",")));

     view->getTablePrices()->setItem(2,3,new QTableWidgetItem(str.setNum(settingsPreferences->getDefaultGoodsDiscountC(), ',', 2).replace(QRegExp("[.]"),",")));
     view->getTablePrices()->setItem(2,2,new QTableWidgetItem(str.setNum(0.0, ',', 2).replace(QRegExp("[.]"),",")));

    this->priceCalculatingEnabled = true;
}

void GoodsDialogController::restoreTableState() {
    QByteArray state = tableStateManager->getState("PRICE_TABLE_GOODS");
    view->getTablePrices()->horizontalHeader()->restoreState(state);
}

void GoodsDialogController::saveTableState() {
    QByteArray state = view->getTablePrices()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("PRICE_TABLE_GOODS");
    if(state != oldState)
        tableStateManager->saveState("PRICE_TABLE_GOODS", state);
}
