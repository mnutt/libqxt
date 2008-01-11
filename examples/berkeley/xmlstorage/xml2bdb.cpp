#include "xml2bdb.h"
#include <QApplication>

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

    XmlNode x;
    x.name=name().toString();
    x.value=text().toString();
    x.type=tokenType();
    i=i.append(x);

    while (!atEnd()) 
    {
        QApplication::processEvents ();
        readNext();
        if (isEndElement())
            break;
        else if (isStartElement())
        {
            readElement(i);
        }
        else
        {
            if(text().toString().simplified().isEmpty())
                continue;
            XmlNode x;
            x.name=name().toString();
            x.value=text().toString();
            x.type=tokenType();
            i.append(x);
        }
    }
}

