#include "desktopentryhelper.h"
#include "desktopentryparser.h"

#include "mere/utils/stringutils.h"

#include <iostream>

//static
Mere::XDG::DesktopEntry Mere::XDG::DesktopEntryHelper::parse(const std::string &path)
{
    if(Mere::Utils::StringUtils::isBlank(path))
    {
        std::cout << "path can't be blank. please check the path." << std::endl;
        return DesktopEntry();
    }

    return parse(QFileInfo(path.c_str()));
}

//static
Mere::XDG::DesktopEntry Mere::XDG::DesktopEntryHelper::parse(const QFileInfo &fileInfo)
{
    DesktopEntryParser parser(fileInfo.absoluteFilePath().toStdString());
    return parser.parse();
}

//static
bool Mere::XDG::DesktopEntryHelper::valid(DesktopEntry &entry)
{
    return entry.valid();
}
