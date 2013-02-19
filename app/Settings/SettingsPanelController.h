#ifndef SETTINGSPANELCONTROLLER_H
#define SETTINGSPANELCONTROLLER_H

#include <QWidget>
#include "Settings/SettingsPanelView.h"
#include "Other/Application/ModuleManager.h"
class SettingsPanelView;

/**
  @author Janiu
  Klasa odpowiedzialna za nadanie kontrolek modułowi ustawień
  */
class SettingsPanelController : public QWidget
{
    Q_OBJECT
private:
  /**
    QWidget z gama elementów służącą do ustawień, wykorzystywany do nadania mu odpowiedniej funkcjonalności
  */
    SettingsPanelView *view;

public:
  /**
   Konstruktor inicjujący wskaźnik do widgeta dla danej klasy
  @param
    parent - przekazywany dalej do klasy SettingsPanelView, określa rodzica okna
   */
    explicit SettingsPanelController(QWidget *parent = 0);
  /**
   Metoda publiczna zwracająca wskaźnik do interfejsu graficznego aktualnego widgeta
  */
    SettingsPanelView *getView();
    /**
      Metoda, która aktualizuje dane we wszystkich modułach ustawień
      */
    void getSettingsModel();

public slots:
    void demo(int i);
    void initModularity();
};

#endif // SETTINGSPANELCONTROLLER_H
