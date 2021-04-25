#ifndef DESKTOPENTRYDIRECTORYTRAVERSER_H
#define DESKTOPENTRYDIRECTORYTRAVERSER_H

#include "global.h"
#include "desktopentry.h"

#include <QObject>

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC DesktopEntryDirectoryTraverser : public QObject
{
    Q_OBJECT
public:
    explicit DesktopEntryDirectoryTraverser(QObject *parent = nullptr);
    std::vector<Mere::XDG::DesktopEntry> traverse() const;
    std::vector<Mere::XDG::DesktopEntry> traverse(DesktopEntry::TypeId type) const;

    std::vector<Mere::XDG::DesktopEntry> traverse(const std::string &path) const;
    std::vector<Mere::XDG::DesktopEntry> traverse(const std::string &path, DesktopEntry::TypeId type) const;

private:
    std::map<std::string, std::vector<std::string> > files() const;
    std::vector<std::string> files(const std::string &path) const;

signals:
    void traversed(const std::string &path) const;
    void processed(const Mere::XDG::DesktopEntry &entry) const;

private:
    std::vector<Mere::XDG::DesktopEntry> m_entries;
};

}
}

#endif // DESKTOPENTRYDIRECTORYTRAVERSER_H
