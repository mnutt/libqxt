#include "qxtpointerlist.h"

void QxtPointerListDeleter::removeSender()
{
    removeThisObject(QObject::sender());
}

