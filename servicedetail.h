#ifndef SERVICEDETAIL_H
#define SERVICEDETAIL_H

#include <QDateTime>
#include <QObject>

class ServiceDetail
{
public:
    ServiceDetail();

    int serviceId;
    QDateTime startDate;
    QDateTime endDate;
    int status;
};

#endif // SERVICEDETAIL_H
