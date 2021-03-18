#include "iconlookuphelper.h"
#include "iconthemehelper.h"
#include "iconthemedirectory.h"

#include "config.h"

#include <QDir>
#include <QDateTime>

//static
std::string Mere::XDG::IconLookupHelper::path(const std::string &icon)
{
    qDebug() << "===============";
    Config *config = Config::instance();
    config->theme("Adwaita");
    config->size(48);
    config->context("");

    qDebug() << "Lookin for icon: " << icon.c_str();

    auto pos = icon.find("/");
    if(pos == 0) return icon;

    pos = icon.find("./");
    if(pos == 0) return icon;

    quint64 start = QDateTime::currentMSecsSinceEpoch();

    std::string path = LookupIcon(icon);

    qDebug() << "Lookup time: " << (QDateTime::currentMSecsSinceEpoch() - start) << "ms";

    return path;
}

//static
std::string Mere::XDG::IconLookupHelper::LookupIcon(const std::string &icon)
{
    Config *config = Config::instance();

    qDebug() << "CONFIG::================================";
    qDebug() << "Theme  : " << config->theme().c_str();
    qDebug() << "Size   : " << config->size();
    qDebug() << "Context: " << config->context().c_str();
    qDebug() << "CONFIG::================================";

    std::string path;

    quint64 start = QDateTime::currentMSecsSinceEpoch();

    std::vector<Mere::XDG::IconTheme> themes = IconThemeHelper::themes();
    qDebug() << "THEME PARSE time: " << (QDateTime::currentMSecsSinceEpoch() - start) << "ms";

    for(const auto &theme : themes)
    {
        if(theme.hidden()) continue;
        if (!config->theme().empty() && theme.name().compare(config->theme())) continue;

        qDebug() << "Theme : " << theme.name().c_str();

        path = LookupIcon(icon, theme);
        break;
    }

    // fallback
    if (path.empty())
    {
        for(const auto &theme : themes)
        {
            if(!theme.hidden()) continue;

            qDebug() << "Fallback Theme : " << theme.name().c_str();

            path = LookupIcon(icon, theme);
            break;
        }
    }

    // check in base directories
    if (path.empty())
    {
        path = LookupFallbackIcon(icon);
    }

    return path;
}


//static
std::string Mere::XDG::IconLookupHelper::LookupIcon(const std::string &icon, const IconTheme &theme)
{
    if (icon.empty() || !theme.valid()) return "";

    std::vector<IconThemeSubDirectory> directories = theme.subdirectories();
    if (!directories.size()) return "";

    Config *config = Config::instance();

    // filter by context
    if (!config->context().empty())
    {
        auto it = std::remove_if(directories.begin(), directories.end(), [config](const IconThemeSubDirectory &directory)
        {
            return directory.context().compare(config->context());
        });

        directories.erase(it, directories.end());
    }

    std::string iconPath;


    QStringList filters = IconLookupHelper::filters(icon);

    qDebug() << "Looking icon into path: " << theme.path().c_str();
    int minsize = INT_MAX;
    for(const auto &directory : directories)
    {
        std::string p(directory.path());
        QDir dir(directory.path().c_str());
        if (!dir.exists()) continue;

        QStringList list = dir.entryList(filters, QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        if (list.size() == 0) continue;

        if (config->size() == 0 || DirectoryMatchesSize(directory, config->size(), config->scale()))
        {
            iconPath = dir.absolutePath().append("/").append(list.at(0)).toStdString();
            break;
        }
        else
        {
            int distance = DirectorySizeDistance(directory, config->size(), config->scale());
            if( distance < minsize)
            {
                iconPath = dir.absolutePath().append("/").append(list.at(0)).toStdString();
                minsize = distance;
            }
        }
    }

    return iconPath;
}

//static
QStringList Mere::XDG::IconLookupHelper::filters(const std::string &icon)
{
    const QStringList extensions = {".png", ".svg", ".xpm"};

    std::string file(icon);
    if (file.length() > 4)
    {
        std::string ext = icon.substr(icon.length() - 4);
        if (extensions.contains(ext.c_str()))
            file.erase(icon.length() - 4);
    }

    QStringList filters;
    for (const QString &extension : extensions)
        filters << QString::fromStdString(file) + extension;

    return filters;
}

//static
bool Mere::XDG::IconLookupHelper::DirectoryMatchesSize(const IconThemeSubDirectory &def, unsigned int size, unsigned int  scale)
{
    if (def.scale() != scale)
         return false;

    if (def.type().compare("Fixed") == 0)
        return def.size() == size;

    if (def.type().compare("Scaled") == 0)
        return def.minsize() <= size && size <= def.maxsize();

    if (def.type().compare("Threshold") == 0)
        return (def.size() - def.threshold()) <= size && size <= (def.size() + def.threshold());

    return false;
}

//static
int Mere::XDG::IconLookupHelper::DirectorySizeDistance(const IconThemeSubDirectory &def, unsigned int size, unsigned int scale)
{
    if (def.type().compare("Fixed") == 0)
        return def.size() * def.scale() - size * scale;

    if (def.type().compare("Scaled") == 0)
    {
        if (size * scale < def.minsize() * def.scale())
            return def.minsize() * def.scale() - size * scale;

        if (size * scale > def.minsize() * def.scale())
            return size * scale - def.minsize() * def.scale();

        return 0;
    }

    if (def.type().compare("Threshold") == 0)
    {
        if ( size * scale < (def.size() - def.threshold()) * def.scale())
            return def.minsize() * def.scale() - size * scale;

        if ( size * scale > (def.size() + def.threshold()) * def.scale())
            return size * scale - def.maxsize() * def.scale();

        return 0;
    }

    return 0;
}

std::string Mere::XDG::IconLookupHelper::LookupFallbackIcon(const std::string &icon)
{
    std::string path;

    QStringList filters = IconLookupHelper::filters(icon);
    for (const std::string &directory : IconThemeDirectory::base())
    {
        QDir dir(directory.c_str());
        if (!dir.exists()) continue;

        QStringList list = dir.entryList(filters, QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        if (list.size() == 0) continue;

        // FIXME priority .png, .svg, .xpm
        path = dir.absolutePath().append("/").append(list.at(0)).toStdString();
        break;
    }

    return path;
}
