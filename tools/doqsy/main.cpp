#include <QFile>
#include <QDebug>
#include <QtXml>
#include <QxtHtmlTemplate>
#include <QStringList>
#include <QPair>
#include <QHash>
#include <QSettings>
#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>
#include <QProcess>

struct Class;
struct Member
{
    QString name;
    QString ref;
    QString type;
    QString signature;
    QString desc;
    QString brief;
    QString kind;
    QDomElement dom;
    Class * classs;
};

struct Module;
struct Class
{
    QString name;
    QString ref;

    QString desc;
    QString brief;

    Module * module;
    QList<Member *> members;

};
struct Module
{
    QString name;
    QString ref;

    QString desc;
    QString brief;

    QList<Class *> classes;
};


bool sortClassBynameLessThen(const Class *s1, const Class *s2)
{
    return s1->name < s2->name;
}
bool sortModuleBynameLessThen(const Module *s1, const Module *s2)
{
    return s1->name < s2->name;
}




///information collected from the xml files
QList<Class *>  classes;
QList<Class *>  publiclasses;
QList<Module *> modules;
QList<Member *> members;

QList<QString>  filesIShouldCopy;

///settings
QString outputDir;
QString templateDir;
QString xmlDir;
QString versionNr;
QString projectName;


Class * findClassByRef(QString ref)
{
    foreach(Class * c,classes)
    {
        if (c->ref==ref)
            return c;
    }
    qFatal("ref %s invalid",qPrintable(ref));
    return 0;
}







QString refToLink( QString ref)
{
    QStringList e=ref.split("_");

    QString object=e.at(0);
    QString sub;
    if(e.count()>1)
        sub=e.at(1);



    ///FIXME that's a dirty hack. Might not actualy be sane
    ///TODO external reference resolving
    if (!object.contains("Qxt"))
    {
        object="http://doc.trolltech.com/latest/"+object;

        if (sub.startsWith("1"))
            sub=sub.mid(1);
    }


    if(sub.size())
        return object+".html#"+sub;
    else
        return object+".html";
}






QString descRTF(QDomElement element,bool noOuterParagraph=false)
{
    ///TODO parse the rest




    QString text;

    int codeindent=0;

    for(QDomNode n = element.firstChild(); !n.isNull(); n = n.nextSibling())
    {
        if (n.isElement ())
        {
            QDomElement e= n.toElement();
            if(e.tagName ()=="sp")
            {
                text += " ";
            }
            else if(e.tagName ()=="para")
            {
                if(noOuterParagraph)
                {
                    text += descRTF(e);
                }
                else
                {
                    text += "<p>"+descRTF(e)+"</p>";
                }
            }
            else if(e.tagName ()=="simplesect")
            {
                QString d="";
                if(e.attribute("kind")=="see")
                    d="See also:";
                else if(e.attribute("kind")=="warning")
                    d="Warning:";
                else if(e.attribute("kind")=="note")
                    d="Note:";

                text += "<div class=\"simplesect\" >"
                        "<img src=\""+e.attribute("kind")+".png\" alt=\""+e.attribute("kind")+"\" />"
                        " <strong>"+d+"</strong> "   +descRTF(e,true)+"</div>";
            }
            else if(e.tagName ()=="bold")
            {
                text += "<strong>"+descRTF(e)+"</strong>";
            }
            else if(e.tagName ()=="emphasis")
            {
                text += "<em>"+descRTF(e)+"</em>";
            }
            else if(e.tagName ()=="programlisting")
            {
                text += "<div class=\"code\">"+descRTF(e)+"</div>";
            }
            else if(e.tagName ()=="codeline")
            {

                QString c= descRTF(e);

                bool close =c.contains("}");
                bool open  =c.contains("{");

                if(close && !open)
                {
                    codeindent--;
                }

                for(int x=0;x<codeindent;x++)
                {
                    text +="&nbsp;&nbsp;&nbsp;&nbsp;";
                }

                if(open && !close)
                    codeindent++;



                text +=c+"<br/>\r\n";
            }
            else if(e.tagName ()=="highlight")
            {
                text += "<span class=\"highlight_"+e.attribute("class")+"\"  >";
                text +=descRTF(e)+"</span>";
            }
            else if(e.tagName ()=="ref")
            {
                ///ignore namespaces, we don't have them
                if(e.attribute("refid").startsWith("namespace"))
                    text +=descRTF(e);
                else
                    text += "<a class=\"reflink\" href=\""+refToLink(e.attribute("refid"))+"\">"+descRTF(e)+"</a>";
            }
            else if(e.tagName ()=="image")
            {
                QString s=descRTF(e);
                text += "<table class=\"descimg\" ><tr><td><img alt=\""+s+"\" src=\""+e.attribute("name")+"\"></td></tr>";
                text += "<tr><td><sup>"+s+"</sup></td></tr></table>";
                filesIShouldCopy.append(e.attribute("name"));
            }
            else if(e.tagName ()=="linebreak")
            {
                text += "<br/>\r\n";
            }
            else if(e.tagName ()=="itemizedlist")
            {
                text += "<ul>\r\n"+descRTF(e)+"\r\n</ul>\r\n";
            }
            else if(e.tagName ()=="listitem")
            {
                text += "<li>"+descRTF(e)+"</li>\r\n";
            }
            else if(e.tagName ()=="heading")
            {
                text += "<h"+e.attribute("level")+">"+descRTF(e)+"</h"+e.attribute("level")+">";
            }

            ///tables
            else if(e.tagName ()=="table")
            {
                text += "<table  border=\"1px\" class=\"desctable\">\r\n"+descRTF(e)+"\r\n</table>\r\n";
            }
            else if(e.tagName ()=="row")
            {
                text += "<tr>\r\n"+descRTF(e)+"\r\n</tr>\r\n";
            }
            else if(e.tagName ()=="entry")
            {
                text += "<td>"+descRTF(e)+"</td>";
            }

            ///memberdef->param
            else if(e.tagName ()=="type")
            {
                text += "  <span class=\"memberdef_type\">"+descRTF(e)+"</span>  ";
            }
            else if(e.tagName ()=="declname")
            {
                text += "  <span class=\"memberdef_declname\">"+descRTF(e)+"</span>  ";
            }
            else if(e.tagName ()=="defval")
            {
                text += "<span class=\"memberdef_defval\">= "+descRTF(e)+"</span>";
            }


            else 
            {
                    
                 text += descRTF(e);
            }
        }
        else if (n.isText ()) 
        {
            text += n.toText().data().replace("<","&lt;").replace(">","&gt;");
        }
    }
    return text;
}






///fill classes and modules globals
void parseIndex(QString location)
{


    QDomDocument doc("doc");
    QFile file(location+"/index.xml");
    if (!file.open(QIODevice::ReadOnly))
        qFatal("cannot open file");
    QString  errorMsg;
    int errorLine=0;
    int errorColumn=0;

    if (!doc.setContent(&file,&errorMsg,&errorLine,&errorColumn)) 
    {
        qCritical("%s:%i:%i %s",qPrintable(location+"/index.xml"),errorLine,errorColumn,qPrintable(errorMsg));
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    if(docElem.tagName ()!="doxygenindex")
        qFatal("unexpected top node in %s",qPrintable(location+"/index.xml"));


    QDomElement e = docElem.firstChildElement("compound");
    while(!e.isNull()) 
    {
        if (e.attribute("kind")=="class")
        {
            Class * cl=new Class;
            cl->module=0;
            cl->name=e.firstChildElement("name").text();
            cl->ref=e.attribute("refid");
            classes.append(cl);
        }
        else if (e.attribute("kind")=="group")
        {
            Module * cl=new Module;
            cl->name=e.firstChildElement("name").text();
            cl->ref=e.attribute("refid");
            modules.append(cl);
        }
        else
        {
            qWarning("no way to document %s",qPrintable(e.attribute("kind")));
        }
    e = e.nextSiblingElement("compound");
    }

}



void parseModule(QString location,Module *m)
{
    QDomDocument doc("doc");
    QString filename=location+"/"+m->ref+".xml";

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        qFatal("cannot open file %s",qPrintable(filename));
    QString  errorMsg;
    int errorLine=0;
    int errorColumn=0;

    if (!doc.setContent(&file,&errorMsg,&errorLine,&errorColumn)) 
    {
        qCritical("%s:%i:%i %s",qPrintable(filename),errorLine,errorColumn,qPrintable(errorMsg));
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    QDomElement def  = docElem.firstChildElement("compounddef");
    if(def.attribute("id")!=m->ref)
        qFatal("combound def %s not expected in %s",qPrintable(def.attribute("id")),qPrintable(filename));



    m->brief=descRTF(def.firstChildElement("briefdescription"));
    m->desc=descRTF(def.firstChildElement("detaileddescription"));



    QDomElement e = def.firstChildElement("innerclass");
    while(!e.isNull()) 
    {
        if (e.attribute("prot")=="public")
        {
            Class * cll=findClassByRef(e.attribute("refid"));
            m->classes.append(cll);
            cll->module=m;
        }
        else
        {
            qWarning("non public member in %s",qPrintable(m->ref));
        }
    e = e.nextSiblingElement("innerclass");
    }

}

QString printAssistantFile()
{
    QxtHtmlTemplate t;
    if(!t.open(templateDir+"/index.dcf"))qFatal("cannot open template");
    QxtHtmlTemplate t_i;
    if(!t_i.open(templateDir+"/index.dcf.unroll.classes"))qFatal("cannot open template");
    QxtHtmlTemplate t_i_i;
    if(!t_i_i.open(templateDir+"/index.dcf.unroll.members"))qFatal("cannot open template");


    t["unroll_classes"]="";
    foreach(Class * cl,publiclasses)
    {
        t_i.clear();
        t_i["name"]=cl->name;
        t_i["link"]=refToLink(cl->ref);
        t_i["unroll_members"]="";

        foreach(Member * m,cl->members)
        {
            t_i_i.clear();
            t_i_i["name"]=m->name;
            t_i_i["link"]=refToLink(m->ref);
            t_i["unroll_members"]+=t_i_i.render();
        }
        t["unroll_classes"]+=t_i.render();
    }

    return t.render();
}

QString printAssistantNGQHPFile()
{
    QxtHtmlTemplate t;
    if(!t.open(templateDir+"/qxt.qhp.xml"))qFatal("cannot open template");
    QxtHtmlTemplate t_i;
    if(!t_i.open(templateDir+"/qxt.qhp.xml.unroll.classes"))qFatal("cannot open template");
    QxtHtmlTemplate t_i_i;
    if(!t_i_i.open(templateDir+"/qxt.qhp.xml.unroll.keywords"))qFatal("cannot open template");
    QxtHtmlTemplate t_i_i_i;
    if(!t_i_i_i.open(templateDir+"/qxt.qhp.xml.unroll.files"))qFatal("cannot open template");


    foreach(Class * cl,publiclasses)
    {
        t_i.clear();
        t_i["name"]=cl->name;
        t_i["link"]=refToLink(cl->ref);
        t["unroll_classes"]+=t_i.render();

        t_i_i.clear();
        t_i_i["name"]=cl->name;
        t_i_i["link"]=refToLink(cl->ref);
        t_i_i["id"]="class:"+cl->name;
        t["unroll_keywords"]+=t_i_i.render();

        foreach(Member * m,cl->members)
        {
            if (cl->name==m->name) ///skip ctor
                continue;
            m->name.replace("<","&lt;").replace(">","&gt;");
            t_i_i.clear();
            t_i_i["name"]=m->name;
            t_i_i["link"]=refToLink(m->ref);
            t_i_i["id"]="class:"+cl->name+"::"+m->name;
            t["unroll_keywords"]+=t_i_i.render();
        }
    }

    foreach(QString file,QDir(outputDir).entryList ())
    {
        t_i_i_i.clear();
        t_i_i_i["name"]=file;
        t["unroll_files"]+=t_i_i_i.render();
    }



    t["projectName"]=projectName;
    t["versionNr"]=versionNr;

    return t.render();
}

QString printPublicClasses()
{

    QxtHtmlTemplate t;
    if(!t.open(templateDir+"/classes.html"))qFatal("cannot open template");
    QxtHtmlTemplate t_i;
    if(!t_i.open(templateDir+"/classes-unroll.html"))qFatal("cannot open template");


    uint trs=classes.count()/4;
    QHash<uint,QString> rowstring;
    uint cr=1;

    QString lastChar=" ";
    foreach(Class * cl,publiclasses)
    {
        if (cl->name.count()<3)qFatal("bad class name %s",qPrintable(cl->name));


        if(cl->name.at(3)!=lastChar.at(0))
        {
            lastChar=cl->name.at(3);
            rowstring[cr]+="<th>"+lastChar+"</th>";
            cr++;
            if(cr>trs)
                cr=1;
        }

        t_i.clear();
        t_i["name"]=cl->name;
        t_i["link"]=refToLink(cl->ref);

        rowstring[cr]+=t_i.render();
        cr++;
        if(cr>trs)
            cr=1;
    }

    foreach(QString rowstr, rowstring.values())
    {
        t["unroll"]+="<tr>\r\n"+rowstr+"</tr>\r\n\r\n";
    }
    return t.render();;
}






QString printModules()
{
    QxtHtmlTemplate t;
    if(!t.open(templateDir+"/modules.html"))qFatal("cannot open template");
    QxtHtmlTemplate t_i;
    if(!t_i.open(templateDir+"/modules-unroll.html"))qFatal("cannot open template");


    int i=0;


    foreach(Module * cl,modules)
    {
        i++;
        t_i.clear();
        t_i["iseven"]=QString::number(i%2);
        t_i["name"]=cl->name;
        t_i["link"]=cl->ref+".html";
        t_i["desc"]=cl->brief.replace("<p>","").replace("</p>","");
        t["unroll"]+=t_i.render();
    }
    return t.render();;
}




void preParseSection(QDomElement sectiondef,Class * cl)
{
    qDebug()<<"preparsing section "<<sectiondef.attribute("kind");

    if(sectiondef.attribute("kind").startsWith("private"))///skip private stuff
    {
        return;
    }
    if(sectiondef.attribute("kind")=="friend")///skip friend declarations
    {
        return;
    }

    QDomElement member=sectiondef.firstChildElement("memberdef");
    while(!member.isNull()) 
    {

        QString detaileddescription=descRTF(member.firstChildElement("detaileddescription"));
        QString briefdescription=descRTF(member.firstChildElement("briefdescription"));

        if(briefdescription.contains("{DOQSY:PRIV}") || detaileddescription.contains("{DOQSY:PRIV}")) ///skip reimp and priv
        {
            member=member.nextSiblingElement("memberdef");
            continue;
        }




        qDebug()<<"preparsing member "<<member.firstChildElement("name").text();

        Member * mem=new Member;
        cl->members.append(mem);
        members.append(mem);
        mem->classs=cl;
        mem->ref=member.attribute("id");
        mem->name=member.firstChildElement("name").text();
        mem->type=member.firstChildElement("type").text();
        mem->kind=sectiondef.attribute("kind");
        mem->dom=member;
        mem->desc=detaileddescription;
        mem->brief=briefdescription;



        if (member.attribute("kind")=="function" || member.attribute("kind")=="slot" || member.attribute("kind")=="signal")
        {

            mem->signature=" ( ";

            QDomElement parr =member.firstChildElement("param");
            while(!parr.isNull())
            {
                mem->signature+=descRTF(parr);
                mem->signature+="  , ";
                parr=parr.nextSiblingElement("param");
            }
            if(mem->signature.size()>3)
                mem->signature.chop(2);
            mem->signature+=" ) ";

        }
        else if (member.attribute("kind")=="enum")
        {
            mem->signature=" { ";

            QDomElement parr =member.firstChildElement("enumvalue");
            while(!parr.isNull())
            {
                mem->signature+=descRTF(parr.firstChildElement("name"));
                mem->signature+="  , ";
                parr=parr.nextSiblingElement("enumvalue");
            }
            if(mem->signature.size()>3)
                mem->signature.chop(2);
            mem->signature+=" } ";

        }



        if ( member.attribute("const")=="yes")
            mem->signature+=" const ";
        if ( member.attribute("virt")=="virtual")
            mem->type=" virtual "+mem->type;
        if ( member.attribute("virt")=="pure-virtual")
        {
            mem->type=" virtual "+mem->type;
            mem->signature+=" =0 ";
        }

        if ( member.attribute("explicit")=="yes")
            mem->type=" explicit "+mem->type;
        if ( member.attribute("static")=="yes")
            mem->signature+=" static ";
        member=member.nextSiblingElement("memberdef");
    }
}


QString printAndDeletePropertyAccessors(QDomElement parr,Class * cl)
{
    qDebug()<<"printAndDeletePropertyAccessors"<<parr.text()<<cl->name;
    QString tt;
    Member * ac=0;
    foreach(Member * acs,cl->members)
    {
        if(acs->name==parr.text() && acs->kind=="public-func")
        {
            qDebug()<<acs->name<<"matched";
            ac=acs;
            break;
        }
        else if(acs->name==parr.text() && acs->kind=="public-slot")
        {
            qDebug()<<acs->name<<"matched";
            ac=acs;
            break;
        }
    }
    if(!ac)
        qFatal("cannot find accessor '%s",qPrintable(parr.text()));


    tt+=ac->type+" "+ac->name+" "+ac->signature;


    if(ac->kind=="public-slot")
    {  
//         ac->desc+="<div class=\"simplesect_see\"> <strong>See Also:</strong> "+parr.text()+" </div>";

    }
    else
    {
        qDebug()<<"deleting "<<ac->name;

        members.removeAll(ac);
        cl->members.removeAll(ac);
//         delete ac; 
        /**
        * Whatever the fuck happened, calling delete on ac will delete a _RANDOM_ member.
        * everything else works fine thought.
        * scary
        */
    }
    return tt;
}














QString printClass(QString location,Class * cl)
{
    QDomDocument doc("doc");
    QString filename=location+"/"+cl->ref+".xml";

    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly))
        qFatal("cannot open file %s",qPrintable(filename));

    QString  errorMsg;
    int errorLine=0;
    int errorColumn=0;

    if (!doc.setContent(&file,&errorMsg,&errorLine,&errorColumn)) 
    {
        qCritical("%s:%i:%i %s",qPrintable(filename),errorLine,errorColumn,qPrintable(errorMsg));
        return QString("%1:%2:%3 %4").arg(filename).arg(errorLine)
            .arg(errorColumn).arg(errorMsg);
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    if(docElem.tagName ()!="doxygen")
        qFatal("unexpected top node in %s",qPrintable(filename));
    QDomElement def  = docElem.firstChildElement("compounddef");



    QxtHtmlTemplate t;
    if(!t.open(templateDir+"/class.html"))qFatal("cannot open template");




    ///name
    t["class_name"]=def.firstChildElement("compoundname").text();
    t["ref"]=def.attribute("id");

    if(cl->module)
    {
        t["module_name"]=cl->module->name;
        t["module_link"]=cl->module->ref+".html";
    }
    else
        qWarning("class %s has no module defined",qPrintable(cl->name));




    ///description
    cl->desc=descRTF(def.firstChildElement("detaileddescription"));
    cl->brief=def.firstChildElement("briefdescription").text().replace("<","&lt;").replace(">","&gt;");


    ///templates
    cl->desc.replace("{implicitshared}",
                    "<div class=\"simplesect\" >"
                    "<img src=\"implicitshared.png\" alt=\"implicit shared\" />"
                    " <strong>This class is implicit shared.</strong></div>"
                    );

    t["desc_short"]=cl->brief;
    t["desc_detailed"]=cl->desc;





    ///inherits
    t["inherits"]="";
    QDomElement basecompoundref =def.firstChildElement("basecompoundref");
    while(!basecompoundref.isNull())
    {
        QxtHtmlTemplate t_i;
        if(!t_i.open(templateDir+"/class-unroll-inherits.html"))qFatal("cannot open template");
        t_i["name"]=basecompoundref.text();
        t_i["link"]=refToLink(basecompoundref.attribute("refid"));
        t["inherits"]+=t_i.render();
        basecompoundref=basecompoundref.nextSiblingElement("basecompoundref");
    }



    ///sections
    t["sections"]="";
    QxtHtmlTemplate t_section,t_members_unroll,t_impl;
    if(!t_section.open(templateDir+"/class-section.html"))qFatal("cannot open template");
    if(!t_members_unroll.open(templateDir+"/class-section-unroll.html"))qFatal("cannot open template");
    if(!t_impl.open(templateDir+"/class-impl.html"))qFatal("cannot open template");


    ///preread. for getting property access functions right
    QDomElement sectiondef=def.firstChildElement("sectiondef");
    while(!sectiondef.isNull()) 
    {
        preParseSection(sectiondef,cl);
        sectiondef = sectiondef.nextSiblingElement("sectiondef");
    }


    sectiondef=def.firstChildElement("sectiondef");
    while(!sectiondef.isNull()) 
    {
        if(sectiondef.attribute("kind").startsWith("private"))///skip private stuff
        {
            sectiondef = sectiondef.nextSiblingElement("sectiondef");
            continue;
        }
        if(sectiondef.attribute("kind")=="friend")///skip friend declarations
        {
            sectiondef = sectiondef.nextSiblingElement("sectiondef");
            continue;
        }




        t_section.clear();

        t_section["kind"]=sectiondef.attribute("kind");
        if (t_section["kind"]=="public-type")
        {
             t_section["desc"]="Public Types";
        }
        else if (t_section["kind"]=="public-attrib")
        {
             t_section["desc"]="Public Attributes";
        }
        else if (t_section["kind"]=="public-func")
        {
             t_section["desc"]="Public Functions";
        }
        else if (t_section["kind"]=="public-static-func")
        {
             t_section["desc"]="Public Static Functions";
        }
        else if (t_section["kind"]=="protected-func")
        {
             t_section["desc"]="Protected Functions";
        }
        else if (t_section["kind"]=="property")
        {
             t_section["desc"]="Properties";
        }
        else if (t_section["kind"]=="public-slot")
        {
             t_section["desc"]="Public Slots";
        }
        else if (t_section["kind"]=="signal")
        {
             t_section["desc"]="Signals";
        }

        else 
        {
             t_section["desc"]=t_section["kind"];
        }



        qDebug()<<"parsing section "<<t_section["kind"];


        QString memberstring;
        foreach(Member * mem,cl->members)
        {

            if(mem->kind!=sectiondef.attribute("kind"))
                continue;
            qDebug()<<"parsing member "<<mem->name;


            QDomElement member = mem->dom;


            t_members_unroll.clear();
            t_members_unroll["name"]        =mem->name;
            t_members_unroll["signature"]   =mem->signature;
            t_members_unroll["type"]        =mem->type;
            t_members_unroll["link"]        =refToLink(mem->ref);

            t_section["list"]+=t_members_unroll.render();



            ///Member Function Documentation (impl) 
            t_impl.clear();

            QStringList lii=member.attribute("id").split("_");
            if(lii.count()>1)
                t_impl["ref"]=lii.at(1);
            else
                t_impl["ref"]=lii.at(0);

            t_impl["name"]=mem->name;
            t_impl["signature"]=mem->signature;
            t_impl["type"]=mem->type;

            
            if (member.attribute("kind")=="enum")
            {
                QString tt="<table border=\"1px\" class=\"desctable\">\r\n<tr><th>Constant</th><th>Description</th></tr>\r\n";

                QDomElement parr =member.firstChildElement("enumvalue");
                while(!parr.isNull())
                {
                    tt+="<tr><td>";
                    tt+=descRTF(parr.firstChildElement("name"));
                    tt+="</td><td>";
                    tt+=descRTF(parr.firstChildElement("detaileddescription"));
                    tt+="</td></tr>\r\n";
                    parr=parr.nextSiblingElement("enumvalue");

                }

                tt+="</table>\r\n";
                mem->desc=tt+mem->desc;
            }
            if (member.attribute("kind")=="property")
            {
                QString tt="<p>Access Functions:<ul>\r\n";

                QDomElement parr =member.firstChildElement("read");
                if(!parr.isNull())
                    tt+="<li><strong>read: </strong>"+printAndDeletePropertyAccessors(parr,cl)+"</li>";

                parr =member.firstChildElement("write");
                if(!parr.isNull())
                    tt+="<li><strong>write: </strong>"+printAndDeletePropertyAccessors(parr,cl)+"</li>";

                parr =member.firstChildElement("reset");
                if(!parr.isNull())
                    tt+="<li><strong>reset: </strong>"+printAndDeletePropertyAccessors(parr,cl)+"</li>";

                tt+="</ul></p>\r\n";
                mem->desc+=tt;
            }



            t_impl["desc"]=mem->desc;
            t_impl["brief"]=mem->brief;

            memberstring+=t_impl.render();
        }
        t["impl"]+=memberstring;


        if(!memberstring.isEmpty())///skip empty sections
        {
            t["sections"]+=t_section.render();
        }

        sectiondef = sectiondef.nextSiblingElement("sectiondef");
    }


    return t.render();
}







QString printModule(Module * m)
{
    QxtHtmlTemplate t;
    if(!t.open(templateDir+"/module.html"))qFatal("cannot open template");
    QxtHtmlTemplate t_i;
    if(!t_i.open(templateDir+"/modules-unroll.html"))qFatal("cannot open template");

    t["name"]+=m->name;
    t["brief"]+=m->brief;
    t["desc"]+=m->desc;

    int i=0;
    qSort(m->classes.begin(), m->classes.end(), sortClassBynameLessThen);
    foreach(Class * cl,m->classes)
    {
        i++;
        t_i.clear();
        t_i["iseven"]=QString::number(i%2);
        t_i["name"]=cl->name;
        t_i["link"]=cl->ref+".html";
        t_i["desc"]=cl->brief;

        t["unroll"]+=t_i.render();
    }
    return t.render();;
}





QString printListOfMembers(QString location,Class * cl)
{
    QDomDocument doc("doc");
    QFile file(location+"/"+cl->ref+".xml");
    if (!file.open(QIODevice::ReadOnly))
        qFatal("cannot open file %s",qPrintable(location+"/"+cl->ref+".xml"));
    QString  errorMsg;
    int errorLine=0;
    int errorColumn=0;

    if (!doc.setContent(&file,&errorMsg,&errorLine,&errorColumn)) 
    {
        qCritical("%s:%i:%i %s",qPrintable(location+"/"+cl->ref+".xml"),errorLine,errorColumn,qPrintable(errorMsg));
        return QString("%1:%2:%3 %4").arg(location+"/index.xml").arg(errorLine)
            .arg(errorColumn).arg(errorMsg);
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    if(docElem.tagName ()!="doxygen")
        qFatal("unexpected top node in %s",qPrintable(location+"/"+cl->ref+".xml"));
    QDomElement def  = docElem.firstChildElement("compounddef");



    QxtHtmlTemplate t;
    if(!t.open(templateDir+"/class-members.html"))qFatal("cannot open template");


    ///name
    t["class_name"]=def.firstChildElement("compoundname").text();
    t["ref"]=def.attribute("id");

    ///list
    QDomElement list =def.firstChildElement("listofallmembers");
    t["list"]="";

    QxtHtmlTemplate t_i;
    if(!t_i.open(templateDir+"/class-members-unroll.html"))
        qFatal("cannot open template");


    QDomElement member=list.firstChildElement("member");
    while(!member.isNull()) 
    {
        if(member.attribute("prot")=="private")///skip private members
        {
            member = member.nextSiblingElement("memberdef");
            continue;
        }



        t_i.clear();
        t_i["name"]=member.firstChildElement("name").text();
        t_i["link"]=refToLink(member.attribute("refid"));
        t["list"]+=t_i.render();
        member = member.nextSiblingElement("member");
    }

    return t.render();
}







void wrapToFile(QString filename,QString content,QString title)
{

    QxtHtmlTemplate site;
    if(!site.open(templateDir+"/site.html"))qFatal("cannot open template");
    site["content"]=content;
    site["versionNr"]=versionNr;
    site["projectName"]=projectName;
    site["title"]=title;



    QFile file(outputDir+"/"+filename);
    if (!file.open(QIODevice::WriteOnly))
        qFatal("cannot open output file %s",qPrintable(filename));

    file.write(site.render().toUtf8());

    file.close();
}






int main(int argc,char ** argv)
{

    QCoreApplication app(argc,argv);
    qDebug("[greetings]");


    QString settingsfile="Doqsyfile";


    if(app.arguments().count()>1)
    {
       settingsfile=app.arguments().at(1);
    }

    if(!QFileInfo(settingsfile).exists())
        qFatal("cannot open %s",qPrintable(settingsfile));

    if (!QDir::setCurrent (QFileInfo(settingsfile).absolutePath ()))
        qFatal("unable to change working directory to %s",qPrintable(QFileInfo(settingsfile).absolutePath ()));

    QSettings settings(settingsfile,QSettings::IniFormat);
    settings.beginGroup ("doqsy");
    outputDir=settings.value("output","doc").toString();
    templateDir=settings.value("templates","templates").toString();
    QString doxyexe=settings.value("doxygen","doxygen").toString();



    QDir().mkpath(outputDir);
    settings.endGroup();

    qDebug("[cleaning output dir]");
    foreach(QString asdasdasdasd,QDir(outputDir).entryList ())
    {
        QFile(outputDir+QDir::separator()+asdasdasdasd).remove();
    }


    if(!QDir::temp().mkpath("doqsytmp"))
        qFatal("cannot make  temp dir");
    xmlDir=QDir::temp().absoluteFilePath("doqsytmp");



    

    QString doxygeninput;

    settings.beginGroup ("doxygen");
    foreach(QString key,settings.allKeys())
    {
        doxygeninput+=(key+"="+settings.value(key).toString()+"\r\n");
        if(key=="PROJECT_NUMBER")
            versionNr=settings.value(key).toString();
        else if(key=="PROJECT_NAME")
            projectName=settings.value(key).toString();
    }
    settings.endGroup();

    doxygeninput+=  "XML_OUTPUT             = "+xmlDir+"\r\n"
                        "OUTPUT_DIRECTORY       = "+QDir::tempPath()+"\r\n"
                        "GENERATE_XML           = YES\r\n";



    qDebug("[running doxygen]");


    QProcess doxygenprocess;

    doxygenprocess.setProcessChannelMode(QProcess::ForwardedChannels);

    doxygenprocess.setWorkingDirectory (QDir().absolutePath ());

    doxygenprocess.start (doxyexe,QStringList()<<"-");

    if(!doxygenprocess.waitForStarted ())
        qFatal("doxygen failed to start");

    doxygenprocess.write(doxygeninput.toUtf8());

    doxygenprocess.closeWriteChannel();

    if(!doxygenprocess.waitForFinished (120000))
        qFatal("doxygen failed to finish within 2 minutes");

    if(doxygenprocess.exitCode ())
        qFatal("doxygen run unsecussfull");


    qDebug("[beginn parsing]");

    parseIndex(xmlDir);


    qSort(classes.begin(), classes.end(), sortClassBynameLessThen);
    qSort(modules.begin(), modules.end(), sortModuleBynameLessThen);

    foreach(Module *  m,modules)
    {
        qDebug()<<"parsing module"<<m->ref;
        parseModule(xmlDir,m);
        publiclasses+=m->classes;
    }

    wrapToFile("modules.html",printModules(),"Modules");

    qSort(publiclasses.begin(), publiclasses.end(), sortClassBynameLessThen);
    wrapToFile("classes.html",printPublicClasses(),"Classes");




    foreach(Class * c,classes)
    {
        qDebug()<<"parsing class "<<c->name;
        wrapToFile(c->ref+".html",printClass(xmlDir,c),c->name);
        wrapToFile(c->ref+"-members.html",printListOfMembers(xmlDir,c),c->name+" all Members");
    }

    foreach(Module *  m,modules)
    {
        wrapToFile(m->ref+".html",printModule(m),m->name);
    }

    {
    QFile file(outputDir+"/index.dcf");
    if (!file.open(QIODevice::WriteOnly))
        qFatal("cannot open output file index.dcf");
    file.write(printAssistantFile().toUtf8());
    file.close();
    }




    QxtHtmlTemplate t_i;
    if(!t_i.open(templateDir+"/index.html"))
        qFatal("cannot open template");

    wrapToFile("index.html",t_i.render(),"Qxt Reference Documentation");

    qDebug("[copying referenced files]");


    filesIShouldCopy<<"stylesheet.css"<<"logo.png"<<"qxt.qhcp"<<"see.png"<<"note.png"<<"warning.png"<<"implicitshared.png";

    foreach(QString f,filesIShouldCopy)
    {
        QFile(templateDir+QDir::separator ()+f).copy (outputDir+QDir::separator ()+f);
        qDebug()<<f;
    }

    #if QT_VERSION >= 0x040400
    qDebug("[generating qt help]");

    {
    QFile file(outputDir+QDir::separator ()+"qxt.qhp");
    if (!file.open(QIODevice::WriteOnly))
        qFatal("cannot open output file qxt.qhp");
    file.write(printAssistantNGQHPFile().toUtf8());
    file.close();
    }
 
    qDebug("[running qcollectiongenerator]");


    QProcess qcollectiongenerator;
    QDir().cd(outputDir);
    qcollectiongenerator.setWorkingDirectory (outputDir);
    qcollectiongenerator.setProcessChannelMode(QProcess::ForwardedChannels);
    qcollectiongenerator.start ("qcollectiongenerator",QStringList()<<"qxt.qhcp"<<"-o"<<"qxt.qch");
    if(!qcollectiongenerator.waitForStarted ())
        qFatal("qcollectiongenerator failed to start");
    qcollectiongenerator.closeWriteChannel();
    if(!qcollectiongenerator.waitForFinished (120000))
        qFatal("qcollectiongenerator failed to finish within 2 minutes");
    if(qcollectiongenerator.exitCode ())
    {

        qFatal("qcollectiongenerator run unsecussfull");
    }
    #endif


    qDebug("[done]");
    return 0;
}

