#ifndef SERVICETABLEMODEL_H
#define SERVICETABLEMODEL_H

#include <QAbstractTableModel>
#include <QColor>
#include <QFont>

#include "service.h"


class Service;

class ServiceTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ServiceTableModel(QList<Service> *list, QObject *parent = 0);
    ~ServiceTableModel();



    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant headerData(int section,Qt::Orientation orientation, int role=Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void updateData();

    int getId(int i);

protected:
    QStringList header_data; // список заголовков столбцов
    QList<Service> *serviceList;    // список, в котором хранятся все данные

};

#endif // SERVICETABLEMODEL_H
