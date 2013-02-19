#ifndef CONTRACTOR_H
#define CONTRACTOR_H

#include <QString>
#include <QVector>
#include <QVariant>
#include <QDebug>
#include "Other/SimpleStructure.h"
#include "Contractor/Phone.h"
#include "Contractor/ContractorGroup.h"
#include "Contractor/SourceOfMember.h"
#include "Contractor/ContractorAdditionalId.h"

using namespace std;

class Contractor : public SimpleStructure
{
private:
    QString symbol;
    int type;
    QString postcode;
    QString city;
    QString address;
    QString nip;
    ContractorAdditionalId additionalId;
    float discount;
    QString accountNumber;
    QString website;
    QString email;
    QString comments;
    QString additional;
    QString representative; // przedstawiciel, osoba reprezentujaca firmę (odbierająca dokumenty)
    ContractorGroup contractorGroup;
    SourceOfMember sourceOfMember;
    QVector <Phone> phones;
    bool company;

    QString phonesToString();
public:
    Contractor();

    static const int BUYER = 1;
    static const int SUPPLIER = 2;

    void setSymbol(QString symbol);
    void setType(int type);
    void setPostcode (QString postcode);
    void setCity (QString city);
    void setAddress (QString address);
    void setNip (QString nip);
    void setAdditionalId(SimpleStructure type, QString value);
    void setDiscount(float discount);
    void setAccountNumber (QString accountNumber);
    void setWebsite (QString website);
    void setEmail (QString email);
    void setComments (QString comments);
    void setAdditional (QString additional);
    void setRepresetative(QString representative);
    void setContractorGroup (ContractorGroup contractorGroup);
    void setSourceOfMember (SourceOfMember sourceOfMember);
    void setPhone (QString name, QString number, bool defaultPhone);
    void setPhones(QVector<Phone> phones);
    void setCompany(bool company);

    QString getSymbol();
    int getType();
    QString getPostcode ();
    QString getCity ();
    QString getAddress ();
    QString getNip ();
    ContractorAdditionalId getAdditionalId();
    float getDiscount();
    QString getAccountNumber ();
    QString getWebsite ();
    QString getEmail ();
    QString getComments ();
    QString getAdditional ();
    QString getRepresentative();
    ContractorGroup getContractorGroup();
    SourceOfMember getSourceOfMember();
    Phone getPhone (int index);
    QVector<Phone> getPhones ();
    QString getDefultPhone();
    bool isCompany();

    QString toString();
    QString getContractorData();

    int operator==(Contractor c);

};

#endif // CONTRACTOR_H
