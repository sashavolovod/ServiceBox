#ifndef COMBOBOXITEM_H
#define COMBOBOXITEM_H
#include <QObject>

#include <QString>

class ComboBoxItem
{
public:
    ComboBoxItem();
    int id;
    int parentId;
    QString name;
};

#endif // COMBOBOXITEM_H
