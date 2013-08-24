#include "SettingsUserController.h"

SettingsUserController::SettingsUserController(QObject *parent) :
    SettingsAbstractItemController(parent)
{
    view = new SettingsUserView(this);
    showSignsInPasswordFields(false);
    model = new UserModel();
    setModel();
}

SettingsUserController::~SettingsUserController()
{
    delete model;
}

void SettingsUserController::setModel(QString login)
{
    fillBox(view->getBoxUsers(),model->getUsers());
    if (login == "") {
        if(ApplicationManager::getInstance()->getLoggedUser() != NULL) {
            login = ApplicationManager::getInstance()->getLoggedUser()->getLogin();
        }
    }

    if (login != "") {
        user = model->getUser(login);
        int currentIndex = view->getBoxUsers()->findData(QVariant(login));
        view->getBoxUsers()->setCurrentIndex(currentIndex);

        setData(user);
    }

}

void SettingsUserController::showUserData(int index)
{
    user = model->getUser(view->getBoxUsers()->itemData(index).toString());
    setData(user);

    view->getLineActualPassword()->setDisabled(false);
    view->getPushDelete()->setDisabled(false);
    buttonStatus = SettingsAbstractItemController::EDIT;
}

void SettingsUserController::setData(User *u)
{
    view->getLineLogin()->setText(u->getLogin());
    view->getLineName()->setText(u->getName());
    view->getLineActualPassword()->clear();
    view->getLineNewPassword()->clear();
    view->getLineReplyNewPassword()->clear();
}

void SettingsUserController::fillBox(QComboBox *box,QVector<User> values)
{
    box->clear();
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getLogin()));
}

void SettingsUserController::showSignsInPasswordFields(bool state)
{
    QLineEdit::EchoMode echoMode;
    if (state) echoMode = QLineEdit::Normal;
    else echoMode = QLineEdit::Password;

    view->getLineActualPassword()->setEchoMode(echoMode);
    view->getLineNewPassword()->setEchoMode(echoMode);
    view->getLineReplyNewPassword()->setEchoMode(echoMode);
}

void SettingsUserController::saveChanges(User *u)
{
    if (checkFillForEdit()) return;

    u->setType(user->getType());
    bool passwordEdited = checkDesireToEditPassword();

    if (!(u == user) || passwordEdited)
    {
        if (view->getMessageBox()->createQuestionBox("Edycja użytkownika. ") == MessageBox::YES)
        {
            if (passwordEdited)
            {
                if (passwordsAreCorrect())
                {
                    model->editPassword(user,createHashCode(view->getLineNewPassword()->text()));
                    view->emitChangesWereMade();
                }
            }
            if (!(u == user))
            {
                model->editUser(u,user->getLogin());
                setModel(u->getLogin());
                view->emitChangesWereMade();
            }
            return;
        }
    }
    view->getMessageBox()->createInfoBox("Nie dokonano żadnych zmian. ");
    setData(user);
}

void SettingsUserController::save()
{
    int USER_TYPE = User::TYPE_USER;

    User *u;
    u->setLogin(view->getLineLogin()->text());
    u->setName(view->getLineName()->text());
    u->setType(USER_TYPE);


    if (buttonStatus == SettingsAbstractItemController::EDIT)
            saveChanges(u);

    else if (!model->isLoginInDatabase(u->getLogin()))
    {
        if (buttonStatus == SettingsAbstractItemController::ADD)
             saveAddition(u);
    }
    else
    {
        view->getMessageBox()->createInfoBox(" Już istnieje użytkownik \n z takim loginem w systemie. ");
    }
}

void SettingsUserController::saveAddition(User *u)
{
    if (checkFillForAdd()) return;

    if (checkCorrectnessOfNewPassword())
    {
        if (view->getMessageBox()->createQuestionBox("Definiowanie użytkownika. ") == MessageBox::YES)
        {
            model->addUser(*u,createHashCode(view->getLineNewPassword()->text()));
            setModel(u->getLogin());
            view->emitChangesWereMade();
        }
    }
    else
    {
        view->getMessageBox()->createInfoBox(" Nowe hasło i jego potwierdzenie różnią się. ");
    }
}

void SettingsUserController::addUser()
{
    view->getBoxUsers()->setCurrentIndex(view->getBoxUsers()->count());
    view->getLineActualPassword()->setDisabled(true);
    view->getPushDelete()->setDisabled(true);
    buttonStatus = SettingsAbstractItemController::ADD;
}

void SettingsUserController::removeUser()
{
    if(user->getType() != User::TYPE_ADMIN)
    {
        if (view->getMessageBox()->createQuestionBox("Usuwanie wybranego użytkownika !") == MessageBox::YES)
        {
            model->removeUser(view->getBoxUsers()->itemData(view->getBoxUsers()->currentIndex()).toString());
            view->emitChangesWereMade();
        }
    }
    else
    {
        view->getMessageBox()->createInfoBox("Nie można usunąć administratora. ");
    }
    setModel();
}

QString SettingsUserController::createHashCode(QString password)
{
    QByteArray noHashedPassword = password.toUtf8();
    QByteArray hashedPassword;

    QCryptographicHash* hash = new QCryptographicHash(QCryptographicHash::Md5);
    hash->addData(noHashedPassword);
    hashedPassword = hash->result();
    hashedPassword = hashedPassword.toHex();

    delete hash;
    return hashedPassword;
}

bool SettingsUserController::checkFillForEdit()
{
    if (view->getLineLogin()->text().isEmpty() || view->getLineName()->text().isEmpty())
    {
        view->getMessageBox()->createInfoBox("Uzupełnij wymagane dane. ");
        return true;
    }
    else if (checkDesireToEditPassword())
    {
        if(view->getLineNewPassword()->text().isEmpty() ||
           view->getLineActualPassword()->text().isEmpty() ||
           view->getLineReplyNewPassword()->text().isEmpty())
        {
            view->getMessageBox()->createInfoBox("Uzupełnij wymagane dane edycji hasła.");
            return true;
        }
    }
    return false;
}

bool SettingsUserController::checkFillForAdd()
{
    if (view->getLineLogin()->text().isEmpty() || view->getLineName()->text().isEmpty()
        || view->getLineNewPassword()->text().isEmpty()
        || view->getLineReplyNewPassword()->text().isEmpty())
    {
        view->getMessageBox()->createInfoBox("Uzupełnij wymagane dane. ");
        return true;
    }
    return false;
}

bool SettingsUserController::checkDesireToEditPassword()
{
    return !view->getLineNewPassword()->text().isEmpty() ||
            !view->getLineActualPassword()->text().isEmpty() ||
            !view->getLineReplyNewPassword()->text().isEmpty();
}

bool SettingsUserController::passwordsAreCorrect()
{
    if(model->getPassword(user->getLogin()) != createHashCode(view->getLineActualPassword()->text()))
    {
        view->getMessageBox()->createInfoBox(" Wprowadzono niepoprawne hasło. ");
        return false;
    }
    if(!checkCorrectnessOfNewPassword())
    {
        view->getMessageBox()->createInfoBox(" Nowe hasło i jego potwierdzenie różnią się. ");
        return false;
    }
    return true;
}

bool SettingsUserController::checkCorrectnessOfNewPassword()
{
    return view->getLineNewPassword()->text() == view->getLineReplyNewPassword()->text();
}

void SettingsUserController::updateAfterLogging(User u)
{
    if (u.getType() == User::TYPE_ADMIN) showAdminComponents(true);
    else  showAdminComponents(false);
    setModel(u.getLogin());
}

void SettingsUserController::showAdminComponents(bool show)
{
    if(show)
    {
        view->getBoxUsers()->show();
        view->getLabel()[0]->show();
        view->getLabel()[1]->show();
        view->getPushAdd()->show();
        view->getPushDelete()->show();
    }
    else
    {
        view->getBoxUsers()->hide();
        view->getLabel()[0]->hide();
        view->getLabel()[1]->hide();
        view->getPushAdd()->hide();
        view->getPushDelete()->hide();
    }
}


SettingsUserView *SettingsUserController::getView() {return view;}
