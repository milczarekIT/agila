#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QWidget>

/**
  * Abstrakcyjna klasa walidująca okna (dialogi)
  * @author Bartosz Milczarek
  */
class Validator
{
   QWidget *parent;
public:
    Validator(QWidget *parent = 0);

    virtual void validateForm() = 0;
    virtual bool isEmptyForm() = 0;
};

#endif // VALIDATOR_H
