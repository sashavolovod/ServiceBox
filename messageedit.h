#ifndef MESSAGEEDIT_H
#define MESSAGEEDIT_H


#include <QWidget>
#include <QTextEdit>
#include <QDebug>
#include <QKeyEvent>
#include "mainwindow.h"

class MainWindow;

class MessageEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit MessageEdit(QWidget *parent = 0);

signals:

public slots:

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    MainWindow *mainWindow;
};

#endif // MESSAGEEDIT_H
