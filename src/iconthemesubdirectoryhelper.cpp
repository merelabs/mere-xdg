#include "iconthemesubdirectoryhelper.h"
#include "mere/utils/stringutils.h"

#include <iostream>
#include <QSettings>

//static
Mere::XDG::IconThemeSubDirectory Mere::XDG::IconThemeSubDirectoryHelper::parse(const std::string &path, const std::string &directory)
{
    if(Mere::Utils::StringUtils::isBlank(path))
    {
        std::cout << "path can't be blank. please check the path." << std::endl;
        return IconThemeSubDirectory();
    }

    return parse(QFileInfo(path.c_str()), directory);
}

//static
Mere::XDG::IconThemeSubDirectory Mere::XDG::IconThemeSubDirectoryHelper::parse(const QFileInfo &fileInfo, const std::string &directory)
{
    if (!fileInfo.exists())
    {
        std::cout << fileInfo.absoluteFilePath().toStdString() << " does not exists. Please check the path.";
        return IconThemeSubDirectory();
    }

    IconThemeSubDirectory d;

    d.set(IconThemeSubDirectory::Attribute::Id, fileInfo.fileName());

    QSettings settings(fileInfo.absoluteFilePath(), QSettings::IniFormat);

    settings.beginGroup(directory.c_str());

    const QStringList keys = settings.childKeys();
    for (const QString &key : keys)
    {
        QVariant value = settings.value(key);
        if (key == "Type")
            d.set(IconThemeSubDirectory::Attribute::Type, value);
        else if (key == "Context")
            d.set(IconThemeSubDirectory::Attribute::Context, value);
        else if (key == "Scale")
            d.set(IconThemeSubDirectory::Attribute::Scale, value);
        else if (key == "Size")
            d.set(IconThemeSubDirectory::Attribute::Size, value);
        else if (key == "MinSize")
            d.set(IconThemeSubDirectory::Attribute::MinSize, value);
        else if (key == "MaxSize")
            d.set(IconThemeSubDirectory::Attribute::MaxSize, value);
        else if (key == "Threshold")
            d.set(IconThemeSubDirectory::Attribute::Threshold, value);
    }

    settings.endGroup();

    d.path(fileInfo.absolutePath().append("/").append(directory.c_str()).toStdString());

    return d;
}

//static
bool Mere::XDG::IconThemeSubDirectoryHelper::valid(const IconThemeSubDirectory &directory)
{
    return directory.valid();
}
