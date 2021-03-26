#ifndef DESKTOPENTRYDIRECTORYTRAVERSER_H
#define DESKTOPENTRYDIRECTORYTRAVERSER_H

#include "desktopentry.h"

#include <QObject>

namespace Mere
{
namespace XDG
{

class DesktopEntryDirectoryTraverser : public QObject
{
    Q_OBJECT
public:
    explicit DesktopEntryDirectoryTraverser(QObject *parent = nullptr);
    std::vector<Mere::XDG::DesktopEntry> traverse();
    std::vector<Mere::XDG::DesktopEntry> traverse(DesktopEntry::Type type);

    std::vector<Mere::XDG::DesktopEntry> traverse(const std::string &path);
    std::vector<Mere::XDG::DesktopEntry> traverse(const std::string &path, DesktopEntry::Type type);

private:
    std::map<std::string, std::vector<std::string> > files() const;
    std::vector<std::string> files(const std::string &path) const;

signals:
    void traversed(const std::string &path);
    void processed(const Mere::XDG::DesktopEntry &entry);

private:
    std::vector<Mere::XDG::DesktopEntry> m_entries;
};

}
}

#endif // DESKTOPENTRYDIRECTORYTRAVERSER_H
