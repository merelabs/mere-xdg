#include "desktopentrydirectoryspec.h"
#include "basedirectoryspec.h"

#include "mere/utils/stringutils.h"

#include <QDir>
#include <QStringList>

Mere::XDG::DesktopEntryDirectorySpec::DesktopEntryDirectorySpec()
{

}

//static
QStringList Mere::XDG::DesktopEntryDirectorySpec::applicationDirectories()
{
    QStringList applicationDirectories;

    QString userDatHome = Mere::XDG::BaseDirectorySpec::userDataDirectory();
    expandEnvVars(userDatHome);
    if (Mere::Utils::StringUtils::isNotBlank(userDatHome))
        applicationDirectories << applicationDirectory(userDatHome);

    const QStringList dataSearchDirectories = BaseDirectorySpec::dataSearchDirectories();
    foreach (QString dataSearchDirectory, dataSearchDirectories)
    {
        expandEnvVars(dataSearchDirectory);
        if (Mere::Utils::StringUtils::isNotBlank(dataSearchDirectory))
            applicationDirectories << applicationDirectory(dataSearchDirectory);
    }

    return applicationDirectories;
}

//static
QString Mere::XDG::DesktopEntryDirectorySpec::applicationDirectory(const QString &path)
{
    QString applicationDirectory(path);

    if (applicationDirectory.endsWith(QDir::separator()))
        applicationDirectory = applicationDirectory.append(QString(Mere::XDG::APPLICATION_DIRECTORY));
    else
        applicationDirectory = applicationDirectory.append(QString(QDir::separator()).append(QString(XDG::APPLICATION_DIRECTORY)));

    return applicationDirectory;
}

//static
void Mere::XDG::DesktopEntryDirectorySpec::expandEnvVars(QString &path)
{
    if (path.contains("$HOME"))
    {
        const QString home(getenv("HOME"));
        path = path.replace("$HOME", home);
    }

    if (path.contains("$USER"))
    {
        const QString user(getenv("USER"));
        path = path.replace("$USER", user);
    }
}
