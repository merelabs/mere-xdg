#include "baseentry.h"

Mere::XDG::BaseEntry::~BaseEntry()
{

}

Mere::XDG::BaseEntry::BaseEntry()
{

}

std::string Mere::XDG::BaseEntry::file() const
{
    return m_file;
}

void Mere::XDG::BaseEntry::file(const std::string &file)
{
    m_file = file;
}

std::string Mere::XDG::BaseEntry::get(const int &attribute, int *set) const
{
    auto find = m_attributes.find(attribute);
    if (find != m_attributes.end())
    {
        if (set) *set = 1;
        return find->second;
    }

    if (set) *set = 0;

    return "";
}

void Mere::XDG::BaseEntry::set(const int &attribute, const std::string &value)
{
    this->m_attributes.insert({attribute, value});
}

std::string Mere::XDG::BaseEntry::get(const std::string &attribute, int *set) const
{
    auto find = m_others.find(attribute);
    if (find != m_others.end())
    {
        if (set) *set = 1;
        return find->second;
    }

    if (set) *set = 0;

    return "";
}

void Mere::XDG::BaseEntry::set(const std::string &attribute, const std::string &value)
{
    this->m_others.insert({attribute, value});
}
