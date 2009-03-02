#ifndef FSIMAGEMODEL_H_INCLUDED
#define FSIMAGEMODEL_H_INCLUDED
/**

    warning: this model is a quick and dirty hack. 
    it has major flaws and should not be used for anything but testing

*/

#include <QAbstractItemModel>
#include <QDir>
#include <QFileSystemWatcher>

struct FsImageModelImage;
class FsImageModel : public QAbstractItemModel
{
Q_OBJECT
public:
    explicit FsImageModel(QString path,QObject * parent = 0);
    virtual ~FsImageModel();
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &index) const;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
private:
    QList<FsImageModelImage*> files;
    QDir dir;
    QFileSystemWatcher watcher;
private slots:
    void directoryChanged ( const QString & path );
    void fileChanged ( const QString & path );
};

#endif // FSIMAGEMODEL_H_INCLUDED
