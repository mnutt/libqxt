#include <QtTest>
#include <QxtTemporaryDir>

class tst_QxtTemporaryDir : public QObject
{
    Q_OBJECT

private slots:
    void testConstructors();

    void testDirTemplate();
    void testAutoRemove();

    void testRemove();
    void testDirPath();
    void testErrorString();

    void testSpecialConditions();
};

void tst_QxtTemporaryDir::testConstructors()
{
    {
        // default values
        QxtTemporaryDir tempDir;
        QCOMPARE(tempDir.autoRemove(), true);
        QVERIFY(tempDir.dir() != QDir());
        QVERIFY(!tempDir.path().isNull());
        QVERIFY(tempDir.errorString().isNull());
    }

    {
        // default temp dir within "/tmp"
        QxtTemporaryDir tempDir;

        QFileInfo templateInfo(tempDir.dirTemplate());
        QCOMPARE(templateInfo.path(), QDir::tempPath());
        QVERIFY(templateInfo.baseName().startsWith("qxt"));

        QFileInfo dirInfo(tempDir.path());
        QCOMPARE(dirInfo.path(), QDir::tempPath());
        QVERIFY(dirInfo.baseName().startsWith("qxt"));

        QVERIFY(templateInfo.baseName() != dirInfo.baseName());
    }

    {
        // custom temp dir within "."
        QxtTemporaryDir tempDir("template");

        QFileInfo templateInfo(tempDir.dirTemplate());
        QCOMPARE(templateInfo.path(), QDir().path());
        QVERIFY(templateInfo.baseName().startsWith("tem"));

        QFileInfo dirInfo(tempDir.path());
        QCOMPARE(dirInfo.path(), QDir().path());
        QVERIFY(dirInfo.baseName().startsWith("tem"));

        QVERIFY(templateInfo.baseName() != dirInfo.baseName());
    }

    {
        // custom temp dir within "/tmp"
        QxtTemporaryDir tempDir(QDir::temp().filePath("template"));

        QFileInfo templateInfo(tempDir.dirTemplate());
        QCOMPARE(templateInfo.path(), QDir::tempPath());
        QVERIFY(templateInfo.baseName().startsWith("tem"));

        QFileInfo dirInfo(tempDir.path());
        QCOMPARE(dirInfo.path(), QDir::tempPath());
        QVERIFY(dirInfo.baseName().startsWith("tem"));

        QVERIFY(templateInfo.baseName() != dirInfo.baseName());
    }
}

void tst_QxtTemporaryDir::testDirTemplate()
{
    // default
    QxtTemporaryDir tempDir;
    QString defaultDirTemplate = tempDir.dirTemplate();
    QVERIFY(QFileInfo(defaultDirTemplate).baseName().startsWith("qxt"));

    // init
    QString tempPath = tempDir.path();
    QCOMPARE(defaultDirTemplate, tempDir.dirTemplate());
    QVERIFY(QFileInfo(tempPath).baseName().startsWith("qxt"));
    QVERIFY(QDir(tempPath).exists());

    // change on the fly
    QString dirTemplate = QDir::temp().filePath("tst");
    tempDir.setDirTemplate(dirTemplate);
    QCOMPARE(dirTemplate, tempDir.dirTemplate());

    // re-init
    QString tempPath2 = tempDir.path();
    QCOMPARE(dirTemplate, tempDir.dirTemplate());
    QVERIFY(QFileInfo(tempPath2).baseName().startsWith("tst"));
    QVERIFY(!QDir(tempPath).exists()); // auto-removed
    QVERIFY(QDir(tempPath2).exists());
}

void tst_QxtTemporaryDir::testAutoRemove()
{
    QString tempPath;
    {
        QxtTemporaryDir tempDir;
        // default value
        QCOMPARE(tempDir.autoRemove(), true);
        // create temp dir
        tempPath = tempDir.path();
        // verify success
        QVERIFY(!tempPath.isEmpty());
    }
    // must have been auto-removed
    QVERIFY(!QDir(tempPath).exists());

    {
        QxtTemporaryDir tempDir;
        // change value
        tempDir.setAutoRemove(false);
        QCOMPARE(tempDir.autoRemove(), false);
        // create temp dir
        tempPath = tempDir.path();
        // verify success
        QVERIFY(!tempPath.isEmpty());
    }
    // must not have been auto-removed
    QVERIFY(QDir(tempPath).exists());
    // cleanup
    QDir().rmdir(tempPath);
}

void tst_QxtTemporaryDir::testRemove()
{
    // /tmp/qxt_XXXXXX
    QxtTemporaryDir tempDir;
    QDir dir = tempDir.dir();

    // /tmp/qxt_XXXXXX/tst_qxt_temp_file
    QTemporaryFile tempFile(dir.filePath("tst_qxt_temp_file"));
    tempFile.setAutoRemove(false);

    // /tmp/qxt_XXXXXX/qxt_XXXXXX
    QxtTemporaryDir tempSubDir(dir.filePath("qxt"));
    QDir subDir = tempSubDir.dir();

    // /tmp/qxt_XXXXXX/qxt_XXXXXX/tst_qxt_temp_file
    QTemporaryFile tempSubFile(subDir.filePath("tst_qxt_temp_file"));
    tempSubFile.setAutoRemove(false);

    // remove & verify
    QVERIFY(tempDir.remove());
    QVERIFY(!dir.exists());
}

void tst_QxtTemporaryDir::testDirPath()
{
    QxtTemporaryDir tempDir;
    QVERIFY(tempDir.dir() != QDir());
    QVERIFY(!tempDir.path().isNull());
    QCOMPARE(tempDir.dir().path(), tempDir.path());
}

void tst_QxtTemporaryDir::testErrorString()
{
#ifdef Q_OS_UNIX
    QDir dir;
    dir.mkdir("noperms");
    if (dir.cd("noperms"))
    {
        // intentionally change permissions to make QxtTempDir fail
        QFile::Permissions oldPerms = QFile::permissions(dir.path());
        QFile::setPermissions(dir.path(), QFile::Permissions(0));

        // should fail
        QxtTemporaryDir tempDir(dir.filePath("fail"));
        (void) tempDir.dir();
        QVERIFY(!tempDir.errorString().isNull());

        // restore permissions and cleanup
        QFile::setPermissions(dir.path(), oldPerms);
        if (dir.cdUp())
            dir.rmdir("noperms");
    }
#endif // Q_OS_UNIX
}

void tst_QxtTemporaryDir::testSpecialConditions()
{
    {
        // pass nothing but "/tmp"
        QxtTemporaryDir tempDir(QDir::tempPath());
        // let QxtTempDir fill in the rest
        QFileInfo info(tempDir.path());
        QVERIFY(info.baseName() != QDir::temp().dirName());
        QVERIFY(info.baseName().startsWith("qxt"));
    }

    {
        // pass nothing but "."
        QxtTemporaryDir tempDir(".");
        // let QxtTempDir fill in the rest
        QFileInfo info(tempDir.path());
        QDir currentDir(".");
        currentDir.makeAbsolute();
        QVERIFY(info.baseName() != currentDir.dirName());
        QVERIFY(info.baseName().startsWith("qxt"));
    }
}

QTEST_MAIN(tst_QxtTemporaryDir)
#include "tst_qxttemporarydir.moc"
