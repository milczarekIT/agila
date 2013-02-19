#include "Contractor.h"

Contractor::Contractor()
{
    id = 0;
    discount=0.0;
    type = BUYER;
}

void Contractor::setSymbol(QString symbol)
{
    this->symbol = symbol;
}
void Contractor::setType(int type) {
    this->type = type;
}

void Contractor::setPostcode (QString postcode)
{
    this->postcode=postcode;
}

void Contractor::setCity (QString city)
{
    this->city=city;
}

void Contractor::setAddress (QString address)
{
    this->address=address;
}

void Contractor::setNip (QString nip)
{
    this->nip=nip;
}

void Contractor::setAdditionalId(SimpleStructure type, QString value) {
    additionalId.setType(type);
    additionalId.setValue(value);
}

void Contractor::setDiscount(float discount)
{
    this->discount = discount;
}

void Contractor::setAccountNumber (QString accountNumber)
{
    this->accountNumber=accountNumber;
}

void Contractor::setWebsite (QString website)
{
    this->website=website;
}

void Contractor::setEmail (QString email)
{
    this->email=email;
}

void Contractor::setComments (QString comments)
{
    this->comments=comments;
}

void Contractor::setAdditional (QString additional)
{
    this->additional=additional;
}

void Contractor::setRepresetative(QString representative)
{
    this->representative = representative;
}

void Contractor::setContractorGroup (ContractorGroup contractorGroup)
{
    this->contractorGroup=contractorGroup;
}

void Contractor::setSourceOfMember (SourceOfMember sourceOfMember)
{
    this->sourceOfMember=sourceOfMember;
}

void Contractor::setPhone (QString name, QString number,bool defaultPhone)
{
    Phone a(name,number,defaultPhone);
    phones.push_back(a);
}


void Contractor::setPhones(QVector<Phone> phones)
{
    this->phones = phones;
}

void Contractor::setCompany(bool company)
{
    this->company = company;
}


QString Contractor::getSymbol()
{
    return symbol;
}
int Contractor::getType() {
    return type;
}

QString Contractor::getPostcode ()
{
    return postcode;
}
QString Contractor::getCity ()
{
    return city;
}
QString Contractor::getAddress ()
{
    return address;
}
QString Contractor::getNip ()
{
    return nip;
}

ContractorAdditionalId Contractor::getAdditionalId() {
    return additionalId;
}

float Contractor::getDiscount()
{
    return discount;
}
QString Contractor::getAccountNumber ()
{
    return accountNumber;
}
QString Contractor::getWebsite ()
{
    return website;
}
QString Contractor::getEmail ()
{
    return email;
}
QString Contractor::getComments ()
{
    return comments;
}
QString Contractor::getAdditional ()
{
    return additional;
}

QString Contractor::getRepresentative()
{
    return representative;
}

ContractorGroup Contractor::getContractorGroup ()
{
    return contractorGroup;
}
SourceOfMember Contractor::getSourceOfMember ()
{
    return sourceOfMember;
}
Phone Contractor::getPhone (int index)
{
    return phones.at(index);
}
QVector<Phone> Contractor::getPhones ()
{
    return phones;
}

QString Contractor::getDefultPhone()
{
    if(phones.size() == 0)
        return "";

    for(int i = 0; i < phones.size(); i++)
    {
        if(phones[i].isDefault())
            return phones[i].getNumber();
    }

    // w przypadku gdy nie ma deafultowego
    return phones[0].getNumber();
}

bool Contractor::isCompany()
{
    return this->company;
}



QString Contractor::toString()
{
    QString companyStr;
    if(this->company)
        companyStr = ", 3) Firma: ";
    else
        companyStr = ", 3) Osoba fizyczna: ";

   return QString("1) Id: ").append(QVariant(this->getId()).toString()) + QString(", 2) Symbol: ").append(this->getSymbol())
           + companyStr
           + QString("Nazwa: ").append(this->getName()) + QString(", 4) Kod pocztowy: ").append(this->getPostcode())
           + QString(", 5) Miejscowość: ").append(this->getCity()) + QString(", 6) Adres: ").append(this->getAddress())
           + QString(", 7) NIP: ").append(this->getNip())
           + QString(", 8) Dodatkowy ID: ").append(this->getAdditionalId().getType().getName() + " " + this->getAdditionalId().getValue())
           + QString(", 9) Rabat: ").append(QVariant(this->getDiscount()).toString())
           + QString(", 10) Numer konta: ").append(this->getAccountNumber()) + QString(", 11) Strona www: ").append(this->getWebsite())
           + QString(", 12) Email: ").append(this->getEmail()) + QString(", 13) Uwagi: ").append(this->getComments())
           + QString(", 14) Dodatkowe: ").append(this->getAdditional()) + QString(", 15) Grupa kontrahentów: " + QString::number(this->getContractorGroup().getId()))
           + QString(", 16) Źródło pozyskania klienta: ") + QString::number(this->getSourceOfMember().getId()) + phonesToString();

}

QString Contractor::phonesToString()
{
    QVector<Phone> cPhones;
    cPhones = getPhones();
    QString phonesString = ", 17) TELEFONY \t";

    for(int i = 0; i < cPhones.size(); i++)
    {
        phonesString += QString::number(i+1) + "] " + QString::number(cPhones[i].getId()) + " | " + cPhones[i].getName() + " | " + cPhones[i].getNumber() + "\t\t";
    }

    return phonesString;
}

QString Contractor::getContractorData()
{
    QString contractorData;

    contractorData = this->getName() + " \n";
    if(this->company)
        contractorData.append(this->getRepresentative() + "\n");

    contractorData.append(this->getAddress() + "\n");
    contractorData.append(this->getPostcode() + " " + this->getCity() + " \n");
    if(!this->getDefultPhone().isEmpty())
        contractorData.append("tel. " + this->getDefultPhone() + "\n");
    if(!this->getNip().isEmpty())
        contractorData.append("NIP: " + this->getNip());

    return contractorData;
}

int Contractor::operator ==(Contractor c)
{
    if(this->id != c.getId())
        return 0;
    else if(this->name != c.getName())
        return 0;
    else if(this->symbol != c.getSymbol())
        return 0;
    else if(this->postcode != c.getPostcode())
        return 0;
    else if(this->city != c.getCity())
        return 0;
    else if(this->address != c.getAddress())
        return 0;
    else if(this->nip != c.getNip())
        return 0;
    else if(this->additionalId.getType().getId() != c.additionalId.getType().getId())
        return 0;
    else if(!(this->additionalId.getValue() == c.additionalId.getValue()))
        return 0;
    else if(this->discount != c.getDiscount())
        return 0;
    else if(this->accountNumber != c.getAccountNumber())
        return 0;
    else if(this->website != c.getWebsite())
        return 0;
    else if(this->email != c.getEmail())
        return 0;
    else if(this->comments != c.getComments())
        return 0;
    else if(this->additional != c.getAdditional())
        return 0;
    else if(this->representative != c.getRepresentative())
        return 0;
    else if(!(this->contractorGroup == c.getContractorGroup()))
        return 0;
    else if(!(this->sourceOfMember == c.getSourceOfMember()))
        return 0;
    else if(this->phones != c.getPhones())
        return 0;
    else if(this->company != c.isCompany())
        return 0;
    else if(this->type !=c.getType())
        return 0;
    else
        return 1;
}
