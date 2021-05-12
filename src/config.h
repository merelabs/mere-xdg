#ifndef MERE_XDG_CONFIG_H
#define MERE_XDG_CONFIG_H

#include "global.h"
#include "mere/config/kvconfig.h"

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC Config : public Mere::Config::KVConfig
{
    explicit Config(const std::string &path);
public:
    std::string theme() const;
    void theme(const std::string &theme);

    uint size() const;
    void size(const uint &size);

    uint scale() const;
    void scale(const uint &scale);

    std::string context() const;
    void context(const std::string &context);

    static Config* instance(const std::string &path = "mere/xdg.conf")
    {
        static Config *instance = new Config(path);

        return instance;
    }
};
}
}
#endif // MERE_XDG_CONFIG_H
