#include "xsessiondirectorytraverser.h"
#include "desktopentrydirectorytraverser.h"
#include "xsessiondirectory.h"

std::vector<Mere::XDG::DesktopEntry> Mere::XDG::XSessionDirectoryTraverser::traverse() const
{
    std::vector<Mere::XDG::DesktopEntry> entries;

    for(const std::string &directory : XSessionDirectory::directories())
    {
        std::vector<Mere::XDG::DesktopEntry> _entries = this->traverse(directory);
        if (_entries.empty()) continue;

        entries.insert(entries.end(), std::make_move_iterator(_entries.begin()), std::make_move_iterator(_entries.end()));
    }

    return entries;
}

std::vector<Mere::XDG::DesktopEntry> Mere::XDG::XSessionDirectoryTraverser::traverse(const std::string &path) const
{
    DesktopEntryDirectoryTraverser traverser;
    return traverser.traverse(path);
}
