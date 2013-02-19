#ifndef OWNER_H
#define OWNER_H
#include <QString>
#include <QVector>

class Owner
{
private:
    int id;
    QString name;
    QString adress;
    QString postCode;
    QString City;
    QString NIP;
    QString bankName;
    QString bankAccount;
    QString additional;
    QString eMail;
    QString website;
    QVector<QString> phones;
    QString logoPath;
    bool logoDefinied;

public:
    Owner();
    int getId();
    QString getName();
    QString getAdress();
    QString getPostCode();
    QString getCity();
    QString getNIP();
    QString getBankName();
    QString getBankAccount();
    QString getAdditional();
    QString getEMail();
    QString getWebsite();
    QVector<QString> getPhones();
    QString getPhone(int index);
    QString getLogoPath();


    void setId(int id);
    void setName(QString name);
    void setAdress(QString adress);
    void setPostCode(QString postCode);
    void setCity(QString City);
    void setNIP(QString NIP);
    void setBankName(QString bankName);
    void setBankAccount(QString bankAccount);
    void setAdditional(QString additional);
    void setEMail(QString eMail);
    void setWebsite(QString website);
    void setPhones(QVector<QString> phones);
    void setPhone(int index, QString phone);
    void setLogoPath(QString logoPath);

    QString toString();
};

#endif // OWNER_H
