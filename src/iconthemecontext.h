#ifndef ICONTHEMECONTEXT_H
#define ICONTHEMECONTEXT_H

#include "global.h"

namespace Mere::XDG
{

class MERE_XDG_LIB_SPEC IconThemeContext
{
public:
    IconThemeContext() = default;
    explicit IconThemeContext(const std::string &context);

    std::string name() const;
    std::string directory() const;

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
    Context m_context;

};

}

#endif // ICONTHEMECONTEXT_H
