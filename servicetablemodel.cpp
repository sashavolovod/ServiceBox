#include "servicetablemodel.h"

ServiceTableModel::ServiceTableModel(QObject *parent /*= 0 */) : QAbstractTableModel(parent)
{
    header_data << "Дата" << "Оборудование" << "Неисправность" << "Состояние";
    list << "one";

}

ServiceTableModel::~ServiceTableModel() {}

QVariant ServiceTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= list.size())
        return QVariant();

    // для каждого столбца возвращаем нужные данные
    if (role == Qt::DisplayRole || role == Qt::EditRole){
        if (index.column() == 0 )
            return "one"; /* list.at(index.row()).fileName; */
        if (index.column() == 1 )
            return "two"; // QString ("%1 KB").arg(list.at(index.row()).pmc.WorkingSetSize /1024);
        if (index.column() == 2 )
            return "three"; // list.at(index.row()).md5sum;
        if (index.column() == 3 )
            return "не исправ"; // list.at(index.row()).md5sum;
    }

    return QVariant();
}

bool ServiceTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
}
int ServiceTableModel::rowCount(const QModelIndex &parent) const
{
    return list.size(); // размер списка - это количество строк
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
