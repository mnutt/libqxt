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

