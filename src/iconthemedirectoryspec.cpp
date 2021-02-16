#include "iconthemedirectoryspec.h"
#include "basedirectoryspec.h"

#include "mere/utils/envutils.h"
#include "mere/utils/stringutils.h"

#include <QDir>

Mere::XDG::IconThemeDirectorySpec::IconThemeDirectorySpec()
{

}

//static
QStringList Mere::XDG::IconThemeDirectorySpec::baseDirectories()
{
    QStringList iconDirectories;

    QString userIconHome = IconThemeDirectorySpec::userIconDirectory();
    expandEnvVars(userIconHome);
    if (Mere::Utils::StringUtils::isNotBlank(userIconHome))
        iconDirectories << userIconHome;

    // Not in specification
    QString userDataDirectory = BaseDirectorySpec::userDataDirectory();
    expandEnvVars(userDataDirectory);
    if (Mere::Utils::StringUtils::isNotBlank(userDataDirectory))
        iconDirectories << iconDirectory(userDataDirectory);

    const QStringList dataSearchDirectories = BaseDirectorySpec::dataSearchDirectories();
    foreach (QString dataSearchDirectory, dataSearchDirectories)
    {
        expandEnvVars(dataSearchDirectory);
        if (Mere::Utils::StringUtils::isNotBlank(dataSearchDirectory))
            iconDirectories << iconDirectory(dataSearchDirectory);
    }

    // Not in specification
    iconDirectories << "/usr/local/share/pixmaps";

    iconDirectories << "/usr/share/pixmaps";

    return iconDirectories;
}

//static
QStringList Mere::XDG::IconThemeDirectorySpec::themeDirectories(const QString &theme)
{
    QStringList themeDirectories;

    QStringList baseDirectories = IconThemeDirectorySpec::baseDirectories();
    for ( const QString &baseDirectory : baseDirectories  )
    {
        QString themeDirectory = baseDirectory;
        themeDirectory.append(QDir::separator()).append(theme);

        QString indexThemeFilePath = themeDirectory;
        indexThemeFilePath.append(QDir::separator()).append("index.theme");

        QFileInfo indexThemeFile(indexThemeFilePath);
        if (indexThemeFile.exists())
            themeDirectories << themeDirectory;
    }

    return themeDirectories;
}

//static
QString Mere::XDG::IconThemeDirectorySpec::iconDirectory(const QString &path)
{
    QString iconDirectory(path);

    if (iconDirectory.endsWith(QDir::separator()))
        iconDirectory = iconDirectory.append(QString(XDG::ICON_DIRECTORY));
    else
        iconDirectory = iconDirectory.append(QString(QDir::separator()).append(QString(XDG::ICON_DIRECTORY)));

    return iconDirectory;
}

//static
void Mere::XDG::IconThemeDirectorySpec::expandEnvVars(QString &path)
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

//static
QString Mere::XDG::IconThemeDirectorySpec::userIconDirectory()
{
    QString iconHome = QString(getenv(XDG::ICON_HOME));

    if(Mere::Utils::StringUtils::isBlank(iconHome))
        iconHome = QString(XDG::BaseDirectory::ICON_HOME);

    Mere::Utils::EnvUtils::expandEnvVar(iconHome);

    QDir iconHomeDir = QDir(iconHome);
    if (!iconHomeDir.exists())
        createPath(iconHomeDir.absolutePath());

    return iconHome;
}

//static
bool Mere::XDG::IconThemeDirectorySpec::createPath(const QString &path)
{
    qInfo() << "Going to create folder " << path;
    bool created = QDir().mkpath(path);
    if (!created)
        qWarning() << "Unabled to create " << path;

    return created;
}
