#include "servicetablemodel.h"

ServiceTableModel::ServiceTableModel(QList<Service> *list, QObject *parent /*= 0 */) : QAbstractTableModel(parent)
{
    serviceList = list;
    header_data << "№" << "Инв. №" << "Оборудование" <<  "Состояние";
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
            return serviceList->at(index.row()).code;
            //return serviceList->at(index.row()).date.toString("dd.MM.yyyy");
        if (index.column() == 2 )
            return serviceList->at(index.row()).name;
        if (index.column() == 3 )
        {
            switch (serviceList->at(index.row()).status)
            {
                case 0:
                    return "исправно";
                case 1:
                    return "неисправно";
                case 2:
                    return "проверяется";
            }
        }
    }
    if(role==Qt::TextColorRole)
    {
        if(index.row() >= 0)
        {
            if(serviceList->at(index.row()).status !=0 )
                return QVariant(QColor(Qt::darkRed));
        }
    }

    if(role==Qt::FontRole)
    {
        if(index.row() >= 0 && serviceList->at(index.row()).status !=0)
        {
            QFont font;
            font.setBold(true);
            return font;
        }
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

void ServiceTableModel::updateData()
{
    beginResetModel();
    endResetModel();
}

int ServiceTableModel::getId(int i)
{
    return serviceList->at(i).id;
}

bool ServiceTableModel::compareNameAsc(const Service &s1, const Service &s2)
{
    return (s1.name<s2.name);
}

bool ServiceTableModel::compareNameDesc(const Service &s1, const Service &s2)
{
    return (s1.name>s2.name);
}

bool ServiceTableModel::compareStateAsc(const Service &s1, const Service &s2)
{
    return (s1.status<s2.status);
}

bool ServiceTableModel::compareStateDesc(const Service &s1, const Service &s2)
{
    return (s1.status>s2.status);
}

bool ServiceTableModel::compareNumAsc(const Service &s1, const Service &s2)
{
    return (s1.code<s2.code);
}

bool ServiceTableModel::compareNumDesc(const Service &s1, const Service &s2)
{
    return (s1.code>s2.code);
}

void ServiceTableModel::sort(int column, Qt::SortOrder order)
{
    qDebug() << "column" << column << " order " << order;

    switch(column)
    {
    case 1:
        if(order==Qt::AscendingOrder)
            qSort(serviceList->begin(), serviceList->end(), compareNumAsc);
        else
            qSort(serviceList->begin(), serviceList->end(), compareNumDesc);
        break;
    case 2:
        if(order==Qt::AscendingOrder)
            qSort(serviceList->begin(), serviceList->end(), compareNameAsc);
        else
            qSort(serviceList->begin(), serviceList->end(), compareNameDesc);
        break;
    case 3:
        if(order==Qt::AscendingOrder)
            qSort(serviceList->begin(), serviceList->end(), compareStateAsc);
        else
            qSort(serviceList->begin(), serviceList->end(), compareStateDesc);
        break;

    };
    updateData();
}
