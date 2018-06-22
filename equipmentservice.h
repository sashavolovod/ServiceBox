#ifndef EQUIPMENTSERVICE_H
#define EQUIPMENTSERVICE_H
#include <QtCore>

class EquipmentService
{
public:
    EquipmentService();
    int id;
    QDateTime date;
    int status;
    QString equipment_name;
};

#endif // EQUIPMENTSERVICE_H
