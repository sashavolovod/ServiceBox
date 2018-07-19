#include "messageedit.h"

MessageEdit::MessageEdit(QWidget *parent) : QTextEdit(parent)
{
    mainWindow = (MainWindow *)parent;
}

void MessageEdit::keyPressEvent(QKeyEvent *e)
{

    if( ((e->key()== Qt::Key_Enter) || (e->key()== Qt::Key_Return)) && this->toPlainText().length()>0 )
    {
        if(mainWindow->sendMessage(this->toPlainText())==true )
        {
            this->clear();
        }
    }
    else
    {
        QTextEdit::keyPressEvent(e);
    }
}
