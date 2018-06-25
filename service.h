#ifndef SERVICE_H
#define SERVICE_H

#include "common.h"

class Service
{
public:
    Service();
    int id;
    QDateTime date;
    QString name;
    int status;
};

#endif // SERVICE_H
