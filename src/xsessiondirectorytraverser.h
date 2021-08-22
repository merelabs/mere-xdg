#ifndef MERE_XDG_XSESSIONDIRECTORYTRAVERSER_H
#define MERE_XDG_XSESSIONDIRECTORYTRAVERSER_H

#include "desktopentry.h"

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC XSessionDirectoryTraverser
{
public:
    XSessionDirectoryTraverser() = default;
    std::vector<Mere::XDG::DesktopEntry> traverse() const;

    std::vector<Mere::XDG::DesktopEntry> traverse(const std::string &path) const;

private:
    std::vector<Mere::XDG::DesktopEntry> m_entries;
};

}
}
#endif // MERE_XDG_XSESSIONDIRECTORYTRAVERSER_H
