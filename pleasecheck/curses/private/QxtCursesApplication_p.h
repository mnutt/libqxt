#ifndef QXTCURSESAPPLICATION_P_H
#define QXTCURSESAPPLICATION_P_H

#include <QObject>
#include <QxtPimpl.h>
#include "QxtCursesApplication.h"

class QxtCursesApplicationPrivate : public QObject, public QxtPrivate<QxtCursesApplication> {
Q_OBJECT
public:
    QXT_DECLARE_PUBLIC(QxtCursesApplication);

    QObject* currentFocus;

public slots:
    void handleInput();
};

#endif
