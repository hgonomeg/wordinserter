#include "wordinserter.hpp"

#include <QDebug>
#include <QMessageBox>
#include <QFile>

WordInserter::WordInserter(QWidget* parent) 
:QMainWindow(parent) {
    ui = new Ui::WordInserter;
    ui->setupUi(this);
    connect(ui->settingsButton,SIGNAL(clicked()),this,SLOT(openDialog()));
    connect(ui->actionButton,SIGNAL(clicked()),this,SLOT(transform()));

    
    m_wrapper = std::make_shared<Db_wrapper>(QString::fromLatin1("./default.db"));
    m_dialog = nullptr;

}

WordInserter::~WordInserter() {
    delete ui;
}

void WordInserter::openDialog() {
    if(m_dialog)
        delete m_dialog;
    m_dialog = new WordsDialog(this,m_wrapper);
    m_dialog->show();
}

void WordInserter::transform() {
    auto input_data = ui->inputPlainTextEdit->toPlainText().split(' ');
    auto output_data = m_wrapper->transform(std::move(input_data)).join(' ');
    ui->outputTextBrowser->setPlainText(output_data);
    
}

