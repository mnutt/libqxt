#include "xml2bdb.h"


Xml2Bdb::Xml2Bdb() : QXmlStreamReader()
{
}

void Xml2Bdb::read(QxtBdbTreeIterator<XmlNode> root)
{
    while (!atEnd())
    {
        readNext();
        if (isStartElement())
        {
            readElement(root);
        }
    }
}

void Xml2Bdb::readElement(QxtBdbTreeIterator<XmlNode> i)
{
//     Q_ASSERT(isStartElement());

    XmlNode x;
    x.name=name().toString();
    x.value=text().toString();
    x.type=tokenType();
    i=i.append(x);

    while (!atEnd()) 
    {
        readNext();
        if (isEndElement())
            break;
        else if (isStartElement())
        {
            readElement(i);
        }
        else
        {
            if(text().toString().replace("\n","").replace("\r","").replace(" ","").isEmpty())
                continue;
            XmlNode x;
            x.name=name().toString();
            x.value=text().toString();
            x.type=tokenType();
            i.append(x);
        }
    }
}

