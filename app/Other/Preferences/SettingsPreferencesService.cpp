#include "SettingsPreferencesService.h"

SettingsPreferencesService::SettingsPreferencesService()
{
    model = new SettingsPreferencesModel();
}

SettingsPreferencesService::~SettingsPreferencesService()
{
    delete model;
}

int SettingsPreferencesService::getPriceConversion()
{
    int action = 0;
    try {
        action = model->getPriceConversion();

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return action;
}

void SettingsPreferencesService::setPriceConversion(int type)
{
    try {
        model->setPriceConversion(type);

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
}

int SettingsPreferencesService::getTaxIdForRR()
{
    int idTax = -1;
    try {
        idTax = model->getTaxIdForRR();

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return idTax;
}

void SettingsPreferencesService::setTaxIdForRR(int idTax)
{
    try {
        model->setTaxIdForRR(idTax);

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
}

int SettingsPreferencesService::getDefaultPrintAction()
{
    int action = 0;
    try {
        action = model->getDefaultPrintAction();

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return action;
}

void SettingsPreferencesService::setDefaultPrintAction(int action)
{
    try {
        model->setDefaultPrintAction(action);

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
}

int SettingsPreferencesService::getDefaultPrintNumberOfCopies()
{
    int number = 1;
    try {
        number = model->getDefaultPrintNumberOfCopies();

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return number;
}

void SettingsPreferencesService::setDefaultPrintNumberOfCopies(int number)
{
    try {
        model->setDefaultPrintNumberOfCopies(number);

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
}

double SettingsPreferencesService::getDefaultGoodsMargin()
{
    double margin = 0.0;
    try {
        margin = model->getDefaultGoodsMargin();

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return margin;
}

void SettingsPreferencesService::setDefaultGoodsMargin(double margin)
{
    try {
        model->setDefaultGoodsMargin(margin);

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
}

double SettingsPreferencesService::getDefaultGoodsDiscountB()
{
    double discount = 0.0;
    try {
        discount = model->getDefaultGoodsDiscountB();

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return discount;
}

void SettingsPreferencesService::setDefaultGoodsDiscountB(double discount)
{
    try {
        model->setDefaultGoodsDiscountB(discount);

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
}

double SettingsPreferencesService::getDefaultGoodsDiscountC()
{
    double discount = 0.0;
    try {
        discount = model->getDefaultGoodsDiscountC();

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return discount;
}

void SettingsPreferencesService::setDefaultGoodsDiscountC(double discount)
{
    try {
        model->setDefaultGoodsDiscountC(discount);

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
}
