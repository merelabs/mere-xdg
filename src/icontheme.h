#ifndef MERE_XDG_ICONTHEME_H
#define MERE_XDG_ICONTHEME_H

#include "global.h"
#include "baseentry.h"
#include "iconthemesubdirectory.h"

namespace Mere::XDG
{

class MERE_XDG_LIB_SPEC IconTheme : public BaseEntry
{
public:
    ~IconTheme() = default;
    IconTheme() = default;

    IconTheme(const IconTheme &that) = default;
    IconTheme& operator=(const IconTheme &that) = default;

    IconTheme(IconTheme &&that) = default ;
    IconTheme& operator=(IconTheme &&that) = default;

    std::string id() const;
    std::string name() const;
    std::string comment() const;
    std::vector<std::string> directories() const;

    bool hidden() const;

    std::string home() const;
    void home(const std::string &home);

    enum class Flag
    {
        None    = 0,
        Hidden  = 1,
        Visible = 2,
        All     = 4
    };

    enum Attribute
    {
        Id,
        Name,
        Comment,
        Inherits,
        Directories,
        ScaledDirectories,
        Hidden,
        Example,
        Others /* not listed */
    };


    bool valid() const;
    std::vector<IconThemeSubDirectory> subdirectories() const;
    void subdirectory(const IconThemeSubDirectory &sub);

    enum class Context
    {
        Actions         , /* actions */
        Animations      , /* animations */
        Applications    , /* apps */
        Categories      , /* categories */
        Devices         , /* devices */
        Emblems         , /* emblems */
        Emotes          , /* emotes */
        International   , /* intl */
        FileSystems     , /* .. */
        MimeTypes       , /* mimetypes */
        Places          , /* places */
        Status          , /* status */
        Unknown           /* unknown - custom for error checking */
    };

private:
    std::string m_home;
    std::vector<IconThemeSubDirectory> m_subdirectories;
};

}

Q_DECLARE_METATYPE(Mere::XDG::IconTheme);

#endif // MERE_XDG_ICONTHEME_H
