#ifndef XML2BDB_H_INCLUDED
#define XML2BDB_H_INCLUDED

#include <QXmlStreamReader>
#include <QxtBdbTree>
#include "node.h"

class Xml2Bdb : public QXmlStreamReader
{
public:
    Xml2Bdb();
    void read(QxtBdbTreeIterator<XmlNode> root);
private:
    void readElement(QxtBdbTreeIterator<XmlNode> i);
};

#endif // XML2BDB_H_INCLUDED
