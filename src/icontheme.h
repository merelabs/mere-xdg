#ifndef MERE_XDG_ICONTHEME_H
#define MERE_XDG_ICONTHEME_H

#include "global.h"
#include "iconthemesubdirectory.h"

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC IconTheme
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

    std::string path() const;
    void path(const std::string &path);

    enum Flag
    {
        None    = 0,
        Hidden  = 1,
        Visible = 2,
        All     = 4
    };

    enum class Attribute
    {
        Id,
        Name,
        Comment,
        Inherits,
        Directories,
        ScaledDirectories,
        Hidden,
        Example
    };

    QVariant  get(const Attribute &attribute) const;
    void set(const Attribute &attribute, const QVariant &value);

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
    std::string m_path;
    std::vector<IconThemeSubDirectory> m_subdirectories;

    std::map<Attribute, QVariant> m_attributes;
};

}
}

Q_DECLARE_METATYPE(Mere::XDG::IconTheme);

#endif // MERE_XDG_ICONTHEME_H
