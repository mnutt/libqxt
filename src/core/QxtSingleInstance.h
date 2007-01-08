/*******************************************************************
Qt extended Library 
Copyright (c) 2006 Igor Ulyanov <iulyanov@gmail.com> 
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/
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


