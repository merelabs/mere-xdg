#ifndef ICONTHEMESUBDIRECTORY_H
#define ICONTHEMESUBDIRECTORY_H

#include <QObject>

namespace Mere
{
namespace XDG
{

class IconThemeSubDirectory
{
public:
    IconThemeSubDirectory() = default;

    std::string id() const;

    std::string path() const;
    void path(const std::string &path);

    uint size() const;
    uint minsize() const;
    uint maxsize() const;

    uint scale() const;
    uint threshold() const;

    std::string type() const;
    std::string context() const;

    enum class Attribute
    {
        Id,
        Size,
        Scale,
        Context,
        Type,
        MaxSize,
        MinSize,
        Hidden,
        Threshold
    };

    QVariant get(const Attribute &attribute) const;
    void set(const Attribute &attribute, const QVariant &value);

    bool valid() const;

private:
    std::string m_path;

    std::map<Attribute, QVariant> m_attributes;

};

}
}

Q_DECLARE_METATYPE(Mere::XDG::IconThemeSubDirectory);
#endif // ICONTHEMESUBDIRECTORY_H
