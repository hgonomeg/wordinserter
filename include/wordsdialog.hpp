#ifndef WORDSDIALOG_HPP
#define WORDSDIALOG_HPP

#include <QDialog>
#include <memory>
#include "db_wrapper.hpp"

namespace Ui {
class WordsDialog;
}

class WordsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WordsDialog(QWidget *parent = nullptr,std::shared_ptr<Db_wrapper> wrapper = nullptr);
    ~WordsDialog();

private slots:
    void ok();
    void cancel();
    void openDatabase();
    void apply();
    bool deleteCurrentRow();
private:
    Ui::WordsDialog *ui;
    std::shared_ptr<Db_wrapper> m_wrapper;
};

#endif // WORDSDIALOG_HPP
