#ifndef SERVICEDETAILTABLEMODEL_H
#define SERVICEDETAILTABLEMODEL_H

#include "servicedetail.h"
#include <QAbstractTableModel>
#include <QDebug>

class ServiceDetailTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    explicit ServiceDetailTableModel(QList<ServiceDetail> *list, QObject *parent = 0);
    ~ServiceDetailTableModel();

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant headerData(int section,Qt::Orientation orientation, int role=Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    int getId(int i);
    void updateData();
    QList<ServiceDetail> *serviceDetailList;

protected:

    QStringList header_data; // список заголовков столбцов
};

#endif // SERVICEDETAILTABLEMODEL_H
