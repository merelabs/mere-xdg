#ifndef ICONTHEMEPARSER_H
#define ICONTHEMEPARSER_H

#include "global.h"
#include "icontheme.h"

#include <set>

namespace Mere::XDG
{

class MERE_XDG_LIB_SPEC IconThemeParser
{
public:
    ~IconThemeParser();
    explicit IconThemeParser(const std::string &path);

    IconTheme parse();

private:
    std::string id() const;

    IconTheme::Attribute attribute(const std::string &key) const;
    IconThemeSubDirectory::Attribute subattribute(const std::string &key) const;

private:
    std::string m_path;
};

}

#endif // ICONTHEMEPARSER_H
