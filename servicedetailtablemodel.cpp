#include "servicedetailtablemodel.h"


ServiceDetailTableModel::ServiceDetailTableModel(QList<ServiceDetail> *list, QObject *parent /*= 0 */) : QAbstractTableModel(parent)
{
    serviceDetailList = list;
    header_data << "Дата начала ремонта" << "Дата окончания ремонта" << "Дней простоя";
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
        if (index.column() == 1 && serviceDetailList->at(index.row()).status==0)
            return serviceDetailList->at(index.row()).endDate.toString("dd.MM.yyyy");
        if (index.column() == 2 )
            return serviceDetailList->at(index.row()).startDate.daysTo(serviceDetailList->at(index.row()).endDate);
    }
    return QVariant();
}

bool ServiceDetailTableModel::setData(const QModelIndex &, const QVariant &, int)
{
    return false;
}
int ServiceDetailTableModel::rowCount(const QModelIndex &) const
{
    return serviceDetailList->size(); // размер списка - это количество строк
}

int ServiceDetailTableModel::columnCount(const QModelIndex &)    const
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

int ServiceDetailTableModel::getServiceId(int i)
{
    return serviceDetailList->at(i).serviceId;
}

ServiceDetail ServiceDetailTableModel::getServiceDetail(int i)
{
    return serviceDetailList->at(i);
}
