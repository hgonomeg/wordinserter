#ifndef DB_WRAPPER_HPP
#define DB_WRAPPER_HPP

#include <QString>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QStringList>

class Db_wrapper :public QObject {
  Q_OBJECT

 public:
  Db_wrapper(const QString& filename);
  ~Db_wrapper();

  QSqlTableModel* getModel();
  QStringList transform(QStringList&& input_data) const;
  bool loadFromFilename(const QString& filename);
 public slots:
  bool add_row();
  bool delete_row(int row);
 private:
  QSqlTableModel* m_model;
  QSqlDatabase db;

    
};

#endif //  DB_WRAPPER_HPP