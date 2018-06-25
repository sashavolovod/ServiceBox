#include "servicetablemodel.h"

ServiceTableModel::ServiceTableModel(QObject *parent /*= 0 */) : QAbstractTableModel(parent)
{
    header_data << "№" << "Дата" << "Оборудование" <<  "Состояние";
}

ServiceTableModel::~ServiceTableModel() {}

QVariant ServiceTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= serviceList->size())
        return QVariant();

    // для каждого столбца возвращаем нужные данные
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if (index.column() == 0 )
            return serviceList->at(index.row()).id;
        if (index.column() == 1 )
            return serviceList->at(index.row()).date;
        if (index.column() == 2 )
            return serviceList->at(index.row()).name;
        if (index.column() == 3 )
            return serviceList->at(index.row()).status;
    }
    return QVariant();
}

bool ServiceTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
}
int ServiceTableModel::rowCount(const QModelIndex &parent) const
{
    return serviceList->size(); // размер списка - это количество строк
}

int ServiceTableModel::columnCount(const QModelIndex &parent)    const
{
    return header_data.count();
}

QVariant ServiceTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

Qt::ItemFlags ServiceTableModel::flags(const QModelIndex &index) const
{
   if (!index.isValid())
        return Qt::ItemIsSelectable;

   return QAbstractItemModel::flags(index);
}

void ServiceTableModel::setList(QList<Service> *list)
{
    this->serviceList = list;
}

int ServiceTableModel::getId(int i)
{

}
