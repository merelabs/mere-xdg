#ifndef BASE_H
#define BASE_H

#include "global.h"

#include <map>
#include <string>

namespace Mere
{
namespace XDG
{

class MERE_XDG_LIB_SPEC BaseEntry
{
public:
    virtual ~BaseEntry() = default;
    BaseEntry() = default;

    std::string file() const;
    void file(const std::string &file);

    std::string get(const int &attribute, bool *set = nullptr) const;
    void set(const int &attribute, const std::string &value);

    std::string  get(const std::string &key, bool *set = nullptr) const;
    void set(const std::string &key, const std::string &value);

private:
    std::string m_file;

    std::map<int, std::string> m_attributes{};
    std::map<std::string, std::string> m_others{};

};

}
}
#endif // BASE_H
