#include "config.h"

Mere::XDG::Config::Config(const std::string &path) :
    Mere::Config::KVConfig(path)
{
    load();
}

std::string Mere::XDG::Config::theme() const
{
    std::string value = this->get("mere.xdg.icon.theme");
    if (value.empty()) return "hicolor";

    return value;
}

void Mere::XDG::Config::theme(const std::string &theme)
{
    this->set("mere.xdg.icon.theme", theme);
}

uint Mere::XDG::Config::size() const
{
    std::string value = this->get("mere.xdg.icon.size");
    if (value.empty()) return 0;

    return std::stoi(value);
}

void Mere::XDG::Config::size(const uint &size)
{
    this->set("mere.xdg.icon.size", std::to_string(size));
}

uint Mere::XDG::Config::scale() const
{
    std::string value = this->get("mere.xdg.icon.scale");
    if (value.empty()) return 0;

    return std::stoi(value);
}

void Mere::XDG::Config::scale(const uint &scale)
{
    this->set("mere.xdg.icon.scale", std::to_string(scale));
}

std::string Mere::XDG::Config::context() const
{
    int set = 0;
    std::string value = this->get("mere.xdg.icon.context", &set);
    if (!set) return "Applications";

    return value;
}

void Mere::XDG::Config::context(const std::string &context)
{
    this->set("mere.xdg.icon.context", context);
}
