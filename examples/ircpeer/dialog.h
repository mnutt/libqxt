#ifndef DIALOG_H_INCLUDED
#define DIALOG_H_INCLUDED

#include <QDialog>
#include "ui_dialog.h"

class ConnectDialog : public QDialog
{
Q_OBJECT
public:
    ConnectDialog();
    QByteArray hostname();
    int port();
    QString nickname();

private slots:
    void save();

private:
    Ui::Dialog ui;
};

#endif // DIALOG_H_INCLUDED
