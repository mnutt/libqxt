#include "dialog.h"
#include <QSettings>

ConnectDialog::ConnectDialog()
{
    ui.setupUi(this);
    connect(this, SIGNAL(accepted()), this, SLOT(save()));
    QSettings settings("libqxt.org", "ircpeer");
    if(settings.contains("username"))
        ui.nick->setText(settings.value("username").toString());
    if(settings.contains("port"))
        ui.port->setText(settings.value("port").toString());
    if(settings.contains("server"))
        ui.server->setText(settings.value("server").toString());
}

void ConnectDialog::save()
{
    QSettings settings("libqxt.org", "ircpeer");
    settings.setValue("username", nickname());
    settings.setValue("port", QString::number(port()));
    settings.setValue("server", hostname());
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
