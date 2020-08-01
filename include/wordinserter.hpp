#ifndef WORDINSERTER_HPP
#define WORDINSERTER_HPP

#include <QMainWindow>
#include "ui_wordinserter.h"
#include <memory>
#include "db_wrapper.hpp"
#include "wordsdialog.hpp"

class Ui_WordInserter;

namespace Ui {
class WordInserter;
} // namespace Ui

class WordInserter :public QMainWindow {
    Q_OBJECT

    private:
    Ui::WordInserter* ui;
    std::shared_ptr<Db_wrapper> m_wrapper;
    WordsDialog* m_dialog;

    public:
    explicit WordInserter(QWidget* = nullptr);
    virtual ~WordInserter();

    signals:

    public slots:

    void openDialog();
    void transform();
};


#endif // WORDINSERTER_HPP