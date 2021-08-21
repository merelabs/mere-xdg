#ifndef MERE_XDG_AUTOSTARTDIRECTORYTRAVERSER_H
#define MERE_XDG_AUTOSTARTDIRECTORYTRAVERSER_H

#include "desktopentry.h"
#include <QObject>

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC AutostartDirectoryTraverser : public QObject
{
    Q_OBJECT
public:
    explicit AutostartDirectoryTraverser(QObject *parent = nullptr);
    std::vector<Mere::XDG::DesktopEntry> traverse() const;
    std::vector<Mere::XDG::DesktopEntry> traverse(DesktopEntry::TypeId type) const;

    std::vector<Mere::XDG::DesktopEntry> traverse(const std::string &path) const;
    std::vector<Mere::XDG::DesktopEntry> traverse(const std::string &path, DesktopEntry::TypeId type) const;

private:
    std::vector<Mere::XDG::DesktopEntry> m_entries;

};

}
}
#endif // MERE_XDG_AUTOSTARTDIRECTORYTRAVERSER_H
