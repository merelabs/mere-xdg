#include "autostartdirectorytraverser.h"
#include "autostartdirectory.h"
#include "desktopentrydirectorytraverser.h"

Mere::XDG::AutostartDirectoryTraverser::AutostartDirectoryTraverser(QObject *parent) : QObject(parent)
{

}

std::vector<Mere::XDG::DesktopEntry> Mere::XDG::AutostartDirectoryTraverser::traverse() const
{
    std::vector<Mere::XDG::DesktopEntry> entries;

    std::vector<std::string> directoris = AutostartDirectory::directories();
    for(const std::string &directory : directoris)
    {
        std::vector<Mere::XDG::DesktopEntry> _entries = this->traverse(directory);
        if (_entries.empty()) continue;

        entries.insert(entries.end(), std::make_move_iterator(_entries.begin()), std::make_move_iterator(_entries.end()));
    }

    return entries;
}

std::vector<Mere::XDG::DesktopEntry> Mere::XDG::AutostartDirectoryTraverser::traverse(const std::string &path) const
{
    DesktopEntryDirectoryTraverser traverser;
    return traverser.traverse(path);
}
