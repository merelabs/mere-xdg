#ifndef DESKTOPENTRYACTION_H
#define DESKTOPENTRYACTION_H

#include "global.h"

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC DesktopEntryAction
{
public:
    DesktopEntryAction() = default;
    explicit DesktopEntryAction(const std::string &id);

    std::string id() const;
    std::string name() const;
    std::string icon() const;
    std::string exec() const;

    enum class Attribute
    {
        Id,
        Name,
        Icon,
        Exec
    };

    std::string get(const Attribute &attribute, int *set = nullptr) const;
    void set(const Attribute &attribute, const std::string &value);

    bool valid() const;

    bool operator<(const DesktopEntryAction &that) const
    {
        return id() < that.id();
    }

private:
    std::map<Attribute, std::string> m_attributes;
};

}
}
Q_DECLARE_METATYPE(Mere::XDG::DesktopEntryAction);


#endif // DESKTOPENTRYACTION_H
