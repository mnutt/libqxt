/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** There is aditional information in the LICENSE file of libqxt.
** If you did not receive a copy of the file try to download it or
** contact the libqxt Management
** 
** <http://libqxt.sourceforge.net>  <aep@exys.org> <coda@bobandgeorge.com>
**
****************************************************************************/
/**
\class QxtSingleInstance QxtSingleInstance
\ingroup core
\brief make sure something is run only once on a system


\warning not maintained
\code
int main()
{
QxtSingleInstance tst("AnRealyLongUniqueString_MYAPPLICATIOn83247");


  if(tst.isAlreadyStarted()) {

    return 0;
  }

  std::string st;
  std::cin >> st;
  return 0;
}
\endcode

*/



#ifdef Q_WS_WIN

#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>

#endif

// should be global or static
class QxtSingleInstance
{
public:
  QxtSingleInstance(const char* uniqueID);
  ~QxtSingleInstance();
  bool isAlreadyStarted() const;
  
private:
  sem_t* m_sem;
  bool m_isAlreadyStarted;
};

bool QxtSingleInstance::isAlreadyStarted() const
{
  return m_isAlreadyStarted;
}

QxtSingleInstance::QxtSingleInstance(const char* uniqueID)
{
  m_sem=sem_open(uniqueID, O_CREAT, S_IRUSR | S_IWUSR, 1);
  if(m_sem==SEM_FAILED || sem_trywait(m_sem)) {
    m_isAlreadyStarted=true;
    return;
  }
  m_isAlreadyStarted=false;
}

QxtSingleInstance::~QxtSingleInstance()
{
  if(!m_isAlreadyStarted) {
    sem_post(m_sem);
  }
  sem_close(m_sem);
}

/* Code by pwuertz for Unix systems
#include <unistd.h>
QSettings settings(QSettings::IniFormat, QSettings::UserScope,"quantum","qcamera");
int pid = settings.value("lock_pid",-1).toInt();
if (getpgid(pid) != -1) {
    printf("qcamera is still runnung (pid %d)\n",pid);
    return 0;
} else {
    settings.setValue("lock_pid",getpid());
}
*/
