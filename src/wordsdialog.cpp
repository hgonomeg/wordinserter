#include "wordsdialog.hpp"
#include "ui_wordsdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QAction>

WordsDialog::WordsDialog(QWidget *parent,std::shared_ptr<Db_wrapper> wrapper) :
    QDialog(parent),
    ui(new Ui::WordsDialog),
    m_wrapper(wrapper)
{
    ui->setupUi(this);
    if(m_wrapper) 
        ui->tableView->setModel(m_wrapper->getModel());

    QAction* action_add = new QAction(tr("Add"),this);
    QAction* action_delete = new QAction(tr("Delete"),this);
    action_delete->setShortcut(QKeySequence("Del"));
    action_add->setShortcut(QKeySequence("Ins"));
    ui->tableView->addAction(action_add);
    ui->tableView->addAction(action_delete);
    ui->tableView->setContextMenuPolicy(Qt::ContextMenuPolicy::ActionsContextMenu);

    connect(action_add,SIGNAL(triggered()),m_wrapper.get(),SLOT(add_row()));
    connect(action_delete,SIGNAL(triggered()),this,SLOT(deleteCurrentRow()));

    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(ok()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(cancel()));
    connect(ui->applyButton,SIGNAL(clicked()),this,SLOT(apply()));
    connect(ui->openDatabaseButton,SIGNAL(clicked()),this,SLOT(openDatabase()));
}

WordsDialog::~WordsDialog()
{
    delete ui;
}

void WordsDialog::ok() {
    if(m_wrapper)
        m_wrapper->getModel()->submitAll();
    this->close();
}

void WordsDialog::cancel() {
    if(m_wrapper)
        m_wrapper->getModel()->revertAll();
    this->close();
}

void WordsDialog::apply() {
    if(m_wrapper)
        m_wrapper->getModel()->submitAll();
}

void WordsDialog::openDatabase() {

    try {
        m_wrapper.reset(new Db_wrapper(QFileDialog::getOpenFileName()));
    }catch(std::exception& e){
        QMessageBox::critical(nullptr,tr("Error loading database"),QString::fromStdString(e.what()));
        m_wrapper = nullptr;
    }

    if(m_wrapper)
        ui->tableView->setModel(m_wrapper->getModel());
}

bool WordsDialog::deleteCurrentRow() {
    int row_idx = ui->tableView->currentIndex().row();
    if(m_wrapper)
        return m_wrapper->getModel()->removeRow(row_idx);
    else
        return false;
}
