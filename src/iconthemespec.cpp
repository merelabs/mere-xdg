#include "iconthemespec.h"
#include "iconthemedirectoryspec.h"

#include "mere/utils/stringutils.h"

#include <stdlib.h>

#include <QDir>
#include <QDirIterator>
#include <QSettings>

Mere::XDG::IconThemeSpec::~IconThemeSpec()
{

}

Mere::XDG::IconThemeSpec::IconThemeSpec()
{

}

//static
QString Mere::XDG::IconThemeSpec::path(const QString &icon)
{
    return path(icon, 0);
}

//static
QString Mere::XDG::IconThemeSpec::path(const QString &icon, unsigned int size)
{
    return path(icon, size, 0);
}

//static
QString Mere::XDG::IconThemeSpec::path(const QString &icon, unsigned int size, unsigned int scale)
{
    return FindIcon(icon, size, scale);
}

//static
QString Mere::XDG::IconThemeSpec::path(const QString &icon, unsigned int size, unsigned int scale, const QString &context)
{
    return FindIcon(icon, size, scale);
}

//static
QString Mere::XDG::IconThemeSpec::path(const DesktopEntry &entry)
{

}

QString Mere::XDG::IconThemeSpec::FindIcon(const QString &icon, unsigned int size, unsigned int scale)
{
   qDebug() << "Looking for icon : " << icon;
//  filename = FindIconHelper(icon, size, scale, user selected theme);
//  if filename != none
//    return filename

  QString filepath = FindIconHelper(icon, size, scale, "hicolor");
  if( Mere::Utils::StringUtils::isNotBlank(filepath))
    return filepath;

  return LookupFallbackIcon (icon);
}

QString Mere::XDG::IconThemeSpec::FindIconHelper(const QString &icon, unsigned int size, unsigned int  scale, const QString &theme)
{
  QString filename = LookupIcon(icon, size, scale, theme);
  if( Mere::Utils::StringUtils::isNotBlank(filename))
    return filename;

//  if theme has parents
//    parents = theme.parents

//  for parent in parents {
//    filename = FindIconHelper (icon, size, scale, parent)
//    if filename != none
//      return filename
//  }

  return LookupFallbackIcon (icon);
}

QString Mere::XDG::IconThemeSpec::LookupIcon(const QString &icon, unsigned int size, unsigned int scale, const QString &theme)
{
    int minsize = INT_MAX;
    QString iconPath;

    QStringList themeDirectories = IconThemeDirectorySpec::themeDirectories(theme);
    for ( const QString &themeDirectory : themeDirectories)
    {
        qDebug() << "Theme directory:" << themeDirectory;

        // Lookup into only the desire theme directory
        // it contains all icon size and scale direcoties;
        QString themeIndex = themeDirectory;
        QSettings iconTheme(themeIndex.append(QDir::separator()).append("index.theme"), QSettings::IniFormat);
        QStringList directories;

        iconTheme.beginGroup("Icon Theme");
        directories = iconTheme.value("Directories").toStringList();
        iconTheme.endGroup();

//        QStringList filters;
//        const QStringList extensions = {"png", "svg", "xpm"};
//        for (const QString &extension : extensions)
//            filters << icon + "." + extension;

        for (const QString &directory : directories)
        {
            QDir dir(themeDirectory + QDir::separator() + directory);
            QFileInfoList list = dir.entryInfoList(QStringList() << icon + ".*", QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
            if (list.size() == 0) continue;

            iconTheme.beginGroup(directory);

            IconDirectoryDefinition d;
            d.type      = iconTheme.value("Type").toString();

            d.scale = 1;
            if( iconTheme.contains("Scale"))
                d.scale = iconTheme.value("Scale").toInt();

            d.size      = iconTheme.value("Size").toInt();

            d.minsize = d.size;
            if( iconTheme.contains("MinSize"))
                d.minsize   = iconTheme.value("MinSize").toInt();

            d.maxsize = d.size;
            if( iconTheme.contains("MaxSize"))
                d.maxsize   = iconTheme.value("MaxSize").toInt();

            d.threshold = 2;
            if( iconTheme.contains("Threshold"))
                d.threshold = iconTheme.value("Threshold").toInt();

            d.context   = iconTheme.value("Context").toString();
            iconTheme.endGroup();

            if (DirectoryMatchesSize(d, size, scale))
            {
                return list.at(0).absoluteFilePath();
            }
            else
            {
                int distance = DirectorySizeDistance(d, size, scale);
                if( distance < minsize)
                {
                    iconPath = list.at(0).absoluteFilePath();
                    minsize = distance;
                }
            }
        }
    }

    return iconPath;
}

QString Mere::XDG::IconThemeSpec::LookupFallbackIcon (const QString &icon)
{
    QStringList baseDirectories = IconThemeDirectorySpec::baseDirectories();

    const QStringList extensions = {"png", "svg", "xpm"};
    for (const QString &directory : baseDirectories)
    {
        QString filePath = directory;
        filePath.append(QDir::separator()).append(icon).append(".");

        for (const QString &extension : extensions)
        {
            filePath.append(extension);
            QFileInfo file(filePath);
            if (file.exists() && file.isReadable())
                return filePath;

            filePath.chop(extension.size());
        }

    }

    return QString();
}

//static
bool Mere::XDG::IconThemeSpec::DirectoryMatchesSize(const IconDirectoryDefinition &def, unsigned int size, unsigned int  scale)
{
    if (scale && def.scale != scale)
         return false;

    if (def.type.compare("Fixed") == 0)
        return (def.size == size);

    if (def.type.compare("Scaled") == 0)
        return (def.minsize <= size && size <= def.maxsize);

    if (def.type.compare("Threshold") == 0)
        return def.size - def.threshold <= size && size <= def.size + def.threshold;
}

int Mere::XDG::IconThemeSpec::DirectorySizeDistance(const IconDirectoryDefinition &def, unsigned int size, unsigned int scale)
{
    if (def.type.compare("Fixed") == 0)
        return def.size * def.scale - size * scale;

    if (def.type.compare("Scaled") == 0)
    {
        if (size * scale < def.minsize * def.scale)
            return def.minsize * def.scale - size * scale;

        if (size * scale > def.minsize * def.scale)
            return size * scale - def.minsize * def.scale;

        return 0;
    }

    if (def.type.compare("Threshold") == 0)
    {
        if ( size * scale < (def.size - def.threshold) * def.scale)
            return def.minsize * def.scale - size * scale;

        if ( size * scale > (def.size + def.threshold) * def.scale)
            return size * scale - def.maxsize * def.scale;

        return 0;
    }

    return 0;
}
