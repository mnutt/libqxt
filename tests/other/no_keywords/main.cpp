#include <QtGlobal>
#if defined(Q_WS_WIN) && defined(QXT_BERKELEY_LIB)
#include <QxtBerkeley>
#endif
#ifdef QXT_CORE_LIB
#include <QxtCore>
#endif
#ifdef QXT_CRYPTO_LIB
#include <QxtCrypto>
#endif
#ifdef QXT_GUI_LIB
#include <QxtGui>
#endif
#ifdef QXT_NETWORK_LIB
#include <QxtNetwork>
#endif
#ifdef QXT_SQL_LIB
#include <QxtSql>
#endif
#ifdef QXT_WEB_LIB
#include <QxtWeb>
#endif

int main(int argc, char* argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
}
