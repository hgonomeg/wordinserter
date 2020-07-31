#include "db_wrapper.hpp"
#include <stdexcept>
#include <QStringList>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <random>
#include <chrono>
#include <vector>

Db_wrapper::Db_wrapper(const QString& filename) 
{
    m_model = nullptr;
    loadFromFilename(filename);
}

Db_wrapper::~Db_wrapper() {
    db.close();
}

QSqlTableModel* Db_wrapper::getModel() {
    return m_model;
}

QStringList Db_wrapper::transform(QStringList&& input_data) const {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rand_eng(seed);
    std::uniform_real_distribution<float> distribution(0.f,1.f);

    std::vector<std::pair<QString,float>> phrases;
    QSqlQuery query("SELECT * FROM phrases",this->db);
    while(query.next()) {
        QString phrase = query.value(0).toString();
        float frequency = query.value(1).toFloat();
        phrases.push_back({phrase,frequency});
    }

    QStringList ret;
    for(auto& x: input_data) {
        for(auto& y: phrases) {
            float random_value = distribution(rand_eng);
            if(y.second>=random_value)
                ret.append(y.first);
        }
        ret.append(x);
    }
    return ret;
}

bool Db_wrapper::loadFromFilename(const QString& filename) {
    if(db.isOpen())
        db.close();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    try{
    if(!db.open()) {
        throw std::runtime_error(tr("Failed to open SQLITE database: ").toStdString()+filename.toStdString());
    }
    if(!db.tables().contains("phrases"))
        throw std::runtime_error(tr("Incompatible database!").toStdString());

    if(m_model)
        delete m_model;
    m_model = new QSqlTableModel(this,db);
    m_model->setTable("phrases");
    m_model->setEditStrategy(QSqlTableModel::EditStrategy::OnManualSubmit);
    m_model->select();
    return true;
    }catch(std::exception& e)
    {
        QMessageBox::critical(nullptr,tr("Error loading databse"),QString::fromLocal8Bit(e.what()));
        return false;
    }
}

bool Db_wrapper::add_row() {
    return m_model->insertRow(0);
}
bool Db_wrapper::delete_row(int row) {
    return m_model->removeRow(row);
}
