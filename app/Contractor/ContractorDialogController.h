#ifndef ContractorDialogCONTROLLER_H
#define ContractorDialogCONTROLLER_H

#include <QWidget>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QHeaderView>
#include "Contractor/ContractorDialogView.h"
#include "Contractor/ContractorService.h"
#include "Contractor/ContractorValidator.h"
#include "Components/InsertTextDialog.h"
#include "Components/MessageBox.h"
#include "Other/ITableStateManager.h"
#include "Other/TableStateManager.h"
#include "Other/OtherService.h"
class ContractorDialogView;
class ContractorValidator;

/**
  * Kontroler okna kontrahenta
  *  @author Jan Krajewski, Krzysztof Marjański, Bartosz Milczarek
  */

class ContractorDialogController : public QWidget, public ITableStateManager
{
    Q_OBJECT

private:
    ContractorDialogView *view;
    ContractorService *service;
    ContractorValidator *validator;


    Contractor contractor, oldContractor;

    SOMModel *somModel;
    ContractorGroupModel *contractorGroupModel;
    ContractorAdditionalTypeIdModel * contractorAdditionalTypeIdModel;
    TableStateManager *tableStateManager;

    /**
      zmienna określająca czy wpisywanie symbolu następuje automatycznie (true) bądz user sam ją wprowadza (false)
      */
       bool autoSymbol;
       /**
         Model zawierający listę telefonów
         */
       QStandardItemModel *phoneModel;

    /**
      Metoda służąca do zebrania do kupy (konkretnie klasy Contractor) danych kontrahenta z formularza.
      */
    Contractor getContractorData ();

    void  fillBox(QComboBox *box,QVector<ContractorGroup> values);
    void  fillBox(QComboBox *box,QVector<SourceOfMember> values);
    void  fillBox(QComboBox *box,QVector<SimpleStructure> values);

    void initTablePhone();

    bool isChangesOccured();

    void restoreTableState();
    void saveTableState();

public:
 /**
   Konstruktor inicjujący wskaźnik do okienka dialogowego dla danej klasy - bez uzupełnienia formularza
  @param
    parent - przekazywany dalej do klasy ContractorEditDialogView, określa rodzica okna
 */
  explicit ContractorDialogController(QWidget *parent = 0);
  ~ContractorDialogController();

  ContractorDialogView *getView();
  /**
    czyta i zapisuje do bazy dane z formularza
    @returns wskaźnik do dodanego kontrahenta lub NULL jeśli nie dodano
    */
  Contractor *exec();
  /**
    edytuje kontrahenta o wskazanym id.
    @return true jeżeli nastąpiła edycja false jeżeli nie.
    */
  bool exec(int id);
  /**
    Czyści wszystkie pola
    */
void clearFields();


public slots:
  /**
    * Dodawanie/usuwanie grupy kontrahenckiej
    */
   void addContractorGroup();
   void removeContractorGroup();
 /**
   Slot publiczny wywoływany gdy jest wprowadzany test do pola nazwa
   */
   void nameTyping ();
   /**
     Slot publiczny wywoływany podczas wpisywania danych do pola symbol. Sprawdza czy jest potrzeba automatycznego
     uzupełniania pola Symbol.*/
   void checkAutoSymbol (const QString & text );
   /**
     Slot wywoływany gdy user wciśnie ok w okienku. Sprawdza czy wszystkie wymagane pola są podane.*/
   void checkRequiredFields ();

   /**
     * Po naciśnieciu 'Anuluj', sprawdza czy nie nastąpiły zmiany i czy użytkownik chce zapisać
     */
   void checkChanges();
   /**
     Slot dodający, usuwające telefon
     */
   void addPhone ();
   void removePhone ();
   /**
     * Sloty do buttonów '+', '-' - dodawanie, usuwanie źródeł pozyskania klienta
     */
   void addSourceOfMember();
   void removeSourceOfMember();

   /**
     * Slot wywoływany po wpisaniu kodu pocztowego, automatycznie uzupełnia miasto
     */
   void autoPostalCode();

   void selectedBusinessContractor(bool selectedBusiness);
   void selectedIndividualContractor(bool selectedIndividual);

   void phoneChanged(QModelIndex topLeft,QModelIndex bottomRight);

};

#endif // CONTRACTOREDITCONTROLLER_H
