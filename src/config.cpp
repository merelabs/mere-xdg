#include "config.h"

Mere::XDG::Config::Config(const std::string &path, QObject *parent) :
    Mere::Config::KVConfig(path, parent)
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
    std::string value = this->get("mere.xdg.icon.context");
    if (value.empty()) return "Applications";

    return value;
}

void Mere::XDG::Config::context(const std::string &context)
{
    this->set("mere.xdg.icon.context", context);
}
