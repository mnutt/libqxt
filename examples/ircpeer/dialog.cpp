#include "dialog.h"

ConnectDialog::ConnectDialog()
{
    ui.setupUi(this);
}


QByteArray ConnectDialog::hostname()
{
    return ui.server->text().toAscii();
}
int ConnectDialog::port()
{
    return ui.port->text().toInt();
}
QString ConnectDialog::nickname()
{
    return ui.nick->text();
}
