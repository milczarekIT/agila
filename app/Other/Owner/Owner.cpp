#include "Owner.h"

Owner::Owner()
{
    phones.push_back("");
    phones.push_back("");
    phones.push_back("");
    this->logoPath = "";
    id = 0;
}

int Owner::getId() { return id; }
QString Owner::getName() {return name;}
QString Owner::getAdress() {return adress;}
QString Owner::getPostCode() {return postCode;}
QString Owner::getCity() {return City;}
QString Owner::getNIP() {return NIP;}
QString Owner::getBankName() {return bankName;}
QString Owner::getBankAccount() {return bankAccount;}
QString Owner::getAdditional() {return additional;}
QString Owner::getEMail() {return eMail;}
QString Owner::getWebsite() {return website;}
QVector<QString> Owner::getPhones() { return this->phones; }
QString Owner::getPhone(int index) { return this->phones[index]; }
QString Owner::getLogoPath() { return this->logoPath; }

void Owner::setId(int id) { this->id = id; }
void Owner::setName(QString name) {this->name = name;}
void Owner::setAdress(QString adress) {this->adress = adress;}
void Owner::setPostCode(QString postCode) {this->postCode = postCode;}
void Owner::setCity(QString City) {this->City = City;}
void Owner::setNIP(QString NIP) {this->NIP = NIP;}
void Owner::setBankName(QString bankName) {this->bankName = bankName;}
void Owner::setBankAccount(QString bankAccount) {this->bankAccount = bankAccount;}
void Owner::setAdditional(QString additional) {this->additional = additional;}
void Owner::setEMail(QString eMail) {this->eMail = eMail;}
void Owner::setWebsite(QString website) {this->website = website;}
void Owner::setPhones(QVector<QString> phones) { this->phones = phones; }
void Owner::setPhone(int index, QString phone) { this->phones[index] = phone; }
void Owner::setLogoPath(QString logoPath) { this->logoPath = logoPath; }

QString Owner::toString()
{
    return QString("1) Nazwa: ") +  name + QString(", 2) Adress: ") + adress + QString(", 3) Kod pocztowy: ") + postCode
            + QString(", 4) Miasto: ") +  City + QString(", 5) Nip: ") + NIP + QString(", 6) Nazwa banku: ") + bankName
            + QString(", 5) Nazwa: ") + bankAccount + QString(", 6) Nazwa: ") + additional + QString(", 7) mail: ") + eMail
            + QString(", 8) www: ") + website;
}
