#ifndef MERE_XDG_BASE_H
#define MERE_XDG_BASE_H

#include "global.h"

#include <map>
#include <string>

namespace Mere::XDG
{

class MERE_XDG_LIB_SPEC BaseEntry
{
public:
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

#endif // MERE_XDG_BASE_H
