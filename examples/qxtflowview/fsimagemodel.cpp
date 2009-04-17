#include "fsimagemodel.h"

#include <QFileInfo>
#include <QImage>
#include <QDebug>
#include <QThread>

struct FsImageModelImage
{
    QFileInfo info;
    QImage image;
};

FsImageModel::FsImageModel(QString path,QObject * parent ):QAbstractItemModel(parent)
{
    dir = QDir::current();
    if(!path.isEmpty())
        dir = QDir(path);

    connect(&watcher,SIGNAL(directoryChanged ( const QString &  )),this,SLOT(directoryChanged ( const QString &  )));
    connect(&watcher,SIGNAL(fileChanged ( const QString & )),this,SLOT(fileChanged ( const QString & )));
    watcher.addPath(dir.absolutePath());



    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i)
    {
        FsImageModelImage * img= new FsImageModelImage;
        img->info=list.at(i);
        img->image.load(dir.absoluteFilePath(img->info.fileName()));
        files.append(img);
        watcher.addPath(dir.absoluteFilePath(img->info.fileName()));
    }



}

FsImageModel::~FsImageModel()
{
    qDeleteAll(files);
}

QModelIndex FsImageModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex (  row,  column, files.at(row) );
}


QModelIndex FsImageModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int FsImageModel::rowCount(const QModelIndex & parent ) const
{
    if(parent.isValid())
        return 0;
    return files.count();
}


int FsImageModel::columnCount(const QModelIndex & parent ) const
{
    return 1;
}


QVariant FsImageModel::data(const QModelIndex & index, int role ) const
{
    FsImageModelImage* img=static_cast<FsImageModelImage*>(index.internalPointer());
    if(role==Qt::DisplayRole)
        return img->info.fileName();

    if(role==Qt::DecorationRole)
        return img->image;

    return QVariant();
}

class Thread : public QThread
{
    friend class FsImageModel;
};

void FsImageModel::directoryChanged ( const QString & path )
{

    Q_ASSERT(path==dir.absolutePath());

    QStringList org=watcher.files ();

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i)
    {
        QString path= dir.absoluteFilePath(list.at(i).fileName());

        if(org.contains(path))
        {
            org.removeAll(path);
        }
        else
        {
            beginInsertRows (QModelIndex(),files.count(),files.count());
            FsImageModelImage * img= new FsImageModelImage;
            img->info=list.at(i);


            int retry=100;
            while(!img->image.load(path))
            {
                Thread::usleep(1000);
                if(--retry<0)
                {
                    break;
                }
            }; ///hax
            files.append(img);
            watcher.addPath(path);
            endInsertRows ();
        }
    }


    foreach(const QString &a, org)
        fileChanged(a);


}

void FsImageModel::fileChanged ( const QString & path )
{
    int i=0;
    foreach(FsImageModelImage* img,files)
    {
        if(dir.absoluteFilePath(img->info.fileName())==path)
        {
            if(img->info.exists())
            {
                emit dataChanged ( index(i,0), index(i,0));
            }
            else
            {
                beginRemoveRows (QModelIndex(),i,i);
                watcher.removePath(path);
                delete files.at(i);
                files.removeAt(i);
                endRemoveRows ();
                break;
            }
            break;
        }
        ++i;
    }
}
