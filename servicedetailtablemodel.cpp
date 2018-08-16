#include "servicedetailtablemodel.h"


ServiceDetailTableModel::ServiceDetailTableModel(QList<ServiceDetail> *list, QObject *parent /*= 0 */) : QAbstractTableModel(parent)
{
    serviceDetailList = list;
    header_data << "Дата начала ремонта" << "Дата оконсания ремонта" << "Дней простоя";
}

ServiceDetailTableModel::~ServiceDetailTableModel() {}

QVariant ServiceDetailTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= serviceDetailList->size())
        return QVariant();

    // для каждого столбца возвращаем нужные данные
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if (index.column() == 0 )
            return serviceDetailList->at(index.row()).startDate.toString("dd.MM.yyyy");
        if (index.column() == 1 )
            return serviceDetailList->at(index.row()).endDate.toString("dd.MM.yyyy");
        if (index.column() == 2 )
            return 1;
    }
    return QVariant();
}

bool ServiceDetailTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
}
int ServiceDetailTableModel::rowCount(const QModelIndex &parent) const
{
    return serviceDetailList->size(); // размер списка - это количество строк
}

int ServiceDetailTableModel::columnCount(const QModelIndex &parent)    const
{
    return header_data.count();
}

QVariant ServiceDetailTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return header_data.at(section); // заголовки столбцов
    } else
    {
       return QString("%1").arg( section + 1 ); // возвращаем номера строк
    }
}

Qt::ItemFlags ServiceDetailTableModel::flags(const QModelIndex &index) const
{
   if (!index.isValid())
        return Qt::ItemIsSelectable;

   return QAbstractItemModel::flags(index);
}

void ServiceDetailTableModel::updateData()
{
    beginResetModel();
    endResetModel();
}

int ServiceDetailTableModel::getId(int i)
{
    return serviceDetailList->at(i).serviceId;
}
