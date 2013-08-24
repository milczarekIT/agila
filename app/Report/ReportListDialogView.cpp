#include "ReportListDialogView.h"

ReportListDialogView::ReportListDialogView(QWidget *parent, ReportListDialogController *controller) : QDialog(parent)
{
    this->controller = controller;

    this->setLayout(layout = new QGridLayout());
    this->setMinimumSize(900,600);

    addComponents();
    addContextMenu();
}

ReportListDialogView::~ReportListDialogView() {
    delete menu;
    delete tableView;
}

void ReportListDialogView::addComponents() {
    tableView = new QTableView;
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setFocusPolicy(Qt::NoFocus);
    tableView->verticalHeader()->setDefaultSectionSize(20);

    layout->setRowMinimumHeight(0, 20);

    layout->addWidget(tableView, 0, 1, 1, 6);
}

void ReportListDialogView::addContextMenu() {
    menu = new QMenu();
    QAction *action = new QAction("Pokaż raport",this);
    action->setShortcut(Qt::CTRL+Qt::Key_O);
    action->setStatusTip("Pokaż raport");
    action->setProperty("actionName", "show_report");
    menu->addAction(action);

    action = new QAction("Drukuj raport",this);
    action->setShortcut(Qt::CTRL+Qt::Key_P);
    action->setStatusTip("Drukuj raport");
    action->setProperty("actionName", "print_report");
    menu->addAction(action);

    connect(menu, SIGNAL(triggered(QAction*)), controller, SLOT(handleMenuAction(QAction*)));
}

void ReportListDialogView::setTVModel(TVModel *model)
{
    tableView->setModel(model);
    tableView->setColumnHidden(0, true);
    tableView->setColumnWidth(1, 120);
    tableView->setColumnWidth(2, 350);
    tableView->setColumnWidth(3, 140);
    tableView->setColumnWidth(4, 200);
    tableView->setColumnHidden(5, true);
}


void ReportListDialogView::contextMenuEvent( QContextMenuEvent * event )
{
    menu->exec(event->globalPos());
}
