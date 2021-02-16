#include "basedirectoryspec.h"

#include "mere/utils/envutils.h"
#include "mere/utils/stringutils.h"

#include <QDir>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QByteArray>

Mere::XDG::BaseDirectorySpec::BaseDirectorySpec()
{

}

unsigned int Mere::XDG::BaseDirectorySpec::setupEnv()
{
    int result = 0;

    result += setupDataHomeEnv();
    result += setupConfigHomeEnv();
    result += setupDataDirsEnv();
    result += setupConfigDirsEnv();
    result += setupCacheHomeEnv();
    result += setupRuntimeDirEnv();

    return result;
}

unsigned int Mere::XDG::BaseDirectorySpec::setupEnvVar(const char* env, const char* value, unsigned int err)
{
    QString valueStr(value);
    Mere::Utils::EnvUtils::expandEnvVar(valueStr);

//    char* data = valueStr.toLatin1().data();
    char* data = new char[valueStr.length() + 1];
    for(int i = 0; i < valueStr.length(); i++)
    {
        data[i]  = valueStr.at(i).toLatin1();
    }
    data[valueStr.length()] = '\0';

    int result = setenv(env, data, 1);
    delete[] data;

    if (result != 0) return err;

    QDir valueDir = QDir(valueStr);
    if (!valueDir.exists())
        createPath(valueDir.absolutePath());

    return 0;
}

unsigned int Mere::XDG::BaseDirectorySpec::setupDesktopEnv()
{
    int result = setenv(XDG::SESSION_DESKTOP, XDG::BaseDirectory::SESSION_DESKTOP, 1);
    if (result != 0) return XDG::ErrorMask::SESSION_DESKTOP;

    result = setenv(XDG::CURRENT_DESKTOP, XDG::BaseDirectory::CURRENT_DESKTOP, 1);
    if (result != 0) return XDG::ErrorMask::CURRENT_DESKTOP;

    return 0;
}

unsigned int Mere::XDG::BaseDirectorySpec::setupDataHomeEnv()
{
    return BaseDirectorySpec::setupEnvVar(XDG::DATA_HOME, XDG::BaseDirectory::DATA_HOME, XDG::ErrorMask::DATA_HOME);
}

unsigned int Mere::XDG::BaseDirectorySpec::setupConfigHomeEnv()
{
    return BaseDirectorySpec::setupEnvVar(XDG::CONFIG_HOME, XDG::BaseDirectory::CONFIG_HOME, XDG::ErrorMask::CONFIG_HOME);
}

unsigned int Mere::XDG::BaseDirectorySpec::setupDataDirsEnv()
{
    int result = setenv(XDG::DATA_DIRS, XDG::BaseDirectory::DATA_DIRS, XDG::ErrorMask::DATA_DIRS);
    if (result != 0) return 4;

    QString dataDirs(getenv(XDG::DATA_DIRS));

//    QDir cacheHomeDir = QDir(dataDirs);
//    if (!cacheHomeDir.exists())
//        createPath(cacheHomeDir.absolutePath());

    return 0;
}

unsigned int Mere::XDG::BaseDirectorySpec::setupConfigDirsEnv()
{
    int result = setenv(XDG::CONFIG_DIRS, XDG::BaseDirectory::CONFIG_DIRS, XDG::ErrorMask::CONFIG_DIRS);
    if (result != 0) return 8;

    QString configDirs(getenv(XDG::CONFIG_DIRS));

    return 0;
}

unsigned int Mere::XDG::BaseDirectorySpec::setupCacheHomeEnv()
{
    return BaseDirectorySpec::setupEnvVar(XDG::CACHE_HOME, XDG::BaseDirectory::CACHE_HOME, XDG::ErrorMask::CACHE_HOME);
}

unsigned int Mere::XDG::BaseDirectorySpec::setupRuntimeDirEnv()
{
    return BaseDirectorySpec::setupEnvVar(XDG::RUNTIME_DIR, XDG::BaseDirectory::RUNTIME_DIR, XDG::ErrorMask::RUNTIME_DIR);
}

QString Mere::XDG::BaseDirectorySpec::userDataDirectory()
{
    QString dataHome = QString(getenv(XDG::DATA_HOME));

    if(Mere::Utils::StringUtils::isBlank(dataHome))
        dataHome = QString(XDG::BaseDirectory::DATA_HOME);

    Mere::Utils::EnvUtils::expandEnvVar(dataHome);

    QDir dataHomeDir = QDir(dataHome);
    if (!dataHomeDir.exists())
        createPath(dataHomeDir.absolutePath());

    return dataHome;
}

QString Mere::XDG::BaseDirectorySpec::userConfigDirectory()
{
    QString configHome = QString(getenv(XDG::CONFIG_HOME));
    if(Mere::Utils::StringUtils::isBlank(configHome))
        configHome = QString(XDG::BaseDirectory::CONFIG_HOME);

    Mere::Utils::EnvUtils::expandEnvVar(configHome);

    QDir configHomeDir = QDir(configHome);
    if (!configHomeDir.exists())
        createPath(configHomeDir.absolutePath());

    return configHome;
}

QString Mere::XDG::BaseDirectorySpec::userCacheDirectory()
{
    QString cacheHome = QString(getenv(XDG::CACHE_HOME));
    if(Mere::Utils::StringUtils::isBlank(cacheHome))
        cacheHome = QString(XDG::BaseDirectory::CACHE_HOME);

    Mere::Utils::EnvUtils::expandEnvVar(cacheHome);

    QDir cacheHomeDir = QDir(cacheHome);
    if (!cacheHomeDir.exists())
        createPath(cacheHomeDir.absolutePath());

    return cacheHome;
}

QStringList Mere::XDG::BaseDirectorySpec::dataSearchDirectories()
{    
    QString dataDirectories = QString(getenv(XDG::DATA_DIRS));
    if(Mere::Utils::StringUtils::isBlank(dataDirectories))
        dataDirectories = QString(XDG::BaseDirectory::DATA_DIRS);

    QStringList dirs = dataDirectories.split(":", QString::SkipEmptyParts);

    if (!dirs.isEmpty())
    {
        for (int i = 0; i < dirs.size(); i++)
        {
            QString dir = dirs.at(i);
            Mere::Utils::EnvUtils::expandEnvVar(dir);

            QDir _dir = QDir(dir);
            if (!QDir(_dir).exists())
                createPath(_dir.absolutePath());
        }
    }

    return dirs;
}

QStringList Mere::XDG::BaseDirectorySpec::configSearchDirectories()
{
    QString configDirectories = QString(getenv(XDG::CONFIG_DIRS));
    if(Mere::Utils::StringUtils::isBlank(configDirectories))
        configDirectories = QString(XDG::BaseDirectory::CONFIG_DIRS);

    QStringList dirs = configDirectories.split(":", QString::SkipEmptyParts);

    if (!dirs.isEmpty())
    {
        for (int i = 0; i < dirs.size(); i++)
        {
            QString dir = dirs.at(i);
            Mere::Utils::EnvUtils::expandEnvVar(dir);

            QDir _dir = QDir(dir);
            if (!QDir(_dir).exists())
                createPath(_dir.absolutePath());
        }
    }

    return dirs;
}

bool Mere::XDG::BaseDirectorySpec::createPath(const QString path)
{
    qInfo() << "Going to create folder " << path;
    bool created = QDir().mkpath(path);
    if (!created)
        qWarning() << "Unabled to create " << path;

    return created;
}
