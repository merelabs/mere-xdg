#ifndef ICONTHEMESUBDIRECTORY_H
#define ICONTHEMESUBDIRECTORY_H

#include "global.h"
#include "baseentry.h"

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC IconThemeSubDirectory : public BaseEntry
{
public:
    ~IconThemeSubDirectory() = default;
    IconThemeSubDirectory() = default;

    IconThemeSubDirectory(const IconThemeSubDirectory &that) = default;
    IconThemeSubDirectory& operator=(const IconThemeSubDirectory &that) = default;

    IconThemeSubDirectory(IconThemeSubDirectory &&that) = default ;
    IconThemeSubDirectory& operator=(IconThemeSubDirectory &&that) = default;

    std::string id() const;

    std::string home() const;
    void home(const std::string &home);

    uint size() const;
    uint minsize() const;
    uint maxsize() const;

    uint scale() const;
    uint threshold() const;

    std::string type() const;
    std::string context() const;

    enum Attribute
    {
        Id,
        Size,
        Scale,
        Context,
        Type,
        MaxSize,
        MinSize,
        Hidden,
        Threshold,
        Others /* rest */
    };

    bool valid() const;

private:
    std::string m_home;
    std::map<Attribute, QVariant> m_attributes;
};

}
}

Q_DECLARE_METATYPE(Mere::XDG::IconThemeSubDirectory);
#endif // ICONTHEMESUBDIRECTORY_H
