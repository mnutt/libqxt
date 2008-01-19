#include <QDialog>
#include "ui_dialog.h"

class ConnectDialog : public QDialog
{
public:
    ConnectDialog();
    QByteArray hostname();
    int port();
    QString nickname();

private:
    Ui::Dialog ui;
};

