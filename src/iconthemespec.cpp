#include "iconthemespec.h"
#include "iconthemedirectoryspec.h"

#include "mere/utils/stringutils.h"

#include <stdlib.h>

#include <QDir>
#include <QDirIterator>
#include <QSettings>

//static
std::string Mere::XDG::IconThemeSpec::path(const std::string &icon)
{
    return path(icon, 0);
}

//static
std::string Mere::XDG::IconThemeSpec::path(const std::string &icon, unsigned int size)
{
    return path(icon, size, 0);
}

//static
std::string Mere::XDG::IconThemeSpec::path(const std::string &icon, unsigned int size, unsigned int scale)
{
    return FindIcon(icon, size, scale);
}

//static
std::string Mere::XDG::IconThemeSpec::path(const std::string &icon, unsigned int size, unsigned int scale, const std::string &context)
{
    return FindIcon(icon, size, scale);
}

//static
std::string Mere::XDG::IconThemeSpec::path(const DesktopEntry &entry)
{

}

std::string Mere::XDG::IconThemeSpec::FindIcon(const std::string &icon, unsigned int size, unsigned int scale)
{
   qDebug() << "Looking for icon : " << icon.c_str();
//  filename = FindIconHelper(icon, size, scale, user selected theme);
//  if filename != none
//    return filename

  std::string filepath = FindIconHelper(icon, size, scale, "hicolor");
  if( Mere::Utils::StringUtils::isNotBlank(filepath))
    return filepath;

  return LookupFallbackIcon(icon);
}

std::string Mere::XDG::IconThemeSpec::FindIconHelper(const std::string &icon, unsigned int size, unsigned int  scale, const std::string &theme)
{
  std::string filename = LookupIcon(icon, size, scale, theme);
  if( Mere::Utils::StringUtils::isNotBlank(filename))
    return filename;

//  if theme has parents
//    parents = theme.parents

//  for parent in parents {
//    filename = FindIconHelper (icon, size, scale, parent)
//    if filename != none
//      return filename
//  }

  return LookupFallbackIcon(icon);
}

std::string Mere::XDG::IconThemeSpec::LookupIcon(const std::string &icon, unsigned int size, unsigned int scale, const std::string &theme)
{
    int minsize = INT_MAX;
    std::string iconPath;

    std::vector<std::string> themeDirectories = IconThemeDirectorySpec::themeDirectories(theme);
    for ( const std::string &themeDirectory : themeDirectories)
    {
//        qDebug() << "Theme directory:" << themeDirectory;

        // Lookup into only the desire theme directory
        // it contains all icon size and scale direcoties;
        std::string themeIndex = themeDirectory;

        QSettings iconTheme(themeIndex.append("/").append("index.theme").c_str(), QSettings::IniFormat);
        std::vector<std::string> directories;

        iconTheme.beginGroup("Icon Theme");
        //directories = iconTheme.value("Directories").toStringList();

        for( QString str : iconTheme.value("Directories").toStringList())
        {
            directories.push_back(str.toStdString());
        }

        iconTheme.endGroup();

//        QStringList filters;
//        const QStringList extensions = {"png", "svg", "xpm"};
//        for (const QString &extension : extensions)
//            filters << icon + "." + extension;

        for (const std::string &directory : directories)
        {
//            QDir dir(themeDirectory + QDir::separator() + directory);

            std::string dirpath(themeDirectory);
            dirpath.append("/").append(directory);

            QDir dir(dirpath.c_str());

            QFileInfoList list = dir.entryInfoList(QStringList() << QString::fromStdString(icon) + ".*", QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
            if (list.size() == 0) continue;

            iconTheme.beginGroup(directory.c_str());

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
                return list.at(0).absoluteFilePath().toStdString();
            }
            else
            {
                int distance = DirectorySizeDistance(d, size, scale);
                if( distance < minsize)
                {
                    iconPath = list.at(0).absoluteFilePath().toStdString();
                    minsize = distance;
                }
            }
        }
    }

    return iconPath;
}

std::string Mere::XDG::IconThemeSpec::LookupFallbackIcon (const std::string &icon)
{
    std::vector<std::string> baseDirectories = IconThemeDirectorySpec::baseDirectories();

    const std::vector<std::string> extensions = {"png", "svg", "xpm"};
    for (const std::string &directory : baseDirectories)
    {
        std::string filePath = directory;
        filePath.append("/").append(icon).append(".");

        for (const std::string &extension : extensions)
        {
            // add extension
            filePath.append(extension);

            QFileInfo file(filePath.c_str());
            if (file.exists() && file.isReadable())
                return filePath;

            // remove extension
            filePath.erase(filePath.length() - extension.length());
        }
    }

    return "";
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
