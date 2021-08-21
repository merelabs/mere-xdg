#ifndef MERE_XDG_XSESSIONDIRECTORY_H
#define MERE_XDG_XSESSIONDIRECTORY_H

#include "global.h"

namespace Mere
{
namespace XDG
{
class MERE_XDG_LIB_SPEC XSessionDirectory
{
    XSessionDirectory() = default;
public:
    static std::vector<std::string> directories();
    static std::string directory(const std::string &path);

private:
    static const std::string XSESSION_DIRECTORY;

};
}
}
#endif // MERE_XDG_XSESSIONDIRECTORY_H
