#ifndef MERE_XDG_DESKTOPENTRYPARSER_H
#define MERE_XDG_DESKTOPENTRYPARSER_H

#include "global.h"
#include "desktopentry.h"

namespace Mere::XDG
{

class MERE_XDG_LIB_SPEC DesktopEntryParser
{
public:
    ~DesktopEntryParser();
    explicit DesktopEntryParser(const std::string &path);
    DesktopEntry parse();

protected:
    std::string id() const;

private:
    std::string base() const;

    std::set<std::string> categories(const std::string &value) const;

    DesktopEntry::Attribute attribute(const std::string &key) const;
private:
    std::string m_path;
};

}

#endif // MERE_XDG_DESKTOPENTRYPARSER_H
