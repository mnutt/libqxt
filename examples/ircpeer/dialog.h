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

