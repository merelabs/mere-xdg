#ifndef ICONTHEMESUBDIRECTORYHELPER_H
#define ICONTHEMESUBDIRECTORYHELPER_H

#include "global.h"
#include "iconthemesubdirectory.h"

#include <QFileInfo>

namespace Mere
{
namespace XDG
{

class IconThemeSubDirectoryHelper
{
    IconThemeSubDirectoryHelper() = default;
public:
    static IconThemeSubDirectory parse(const std::string &path, const std::string &directory);
    static IconThemeSubDirectory parse(const QFileInfo &fileInfo, const std::string &directory);
    static bool valid(const IconThemeSubDirectory &directory);
};

}
}

#endif // ICONTHEMESUBDIRECTORYHELPER_H
