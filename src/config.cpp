#include "config.h"

Mere::XDG::Config::Config(const std::string &path, QObject *parent) :
    Mere::Config::KVConfig(path, parent)
{
    load();
}

std::string Mere::XDG::Config::theme() const
{
    QVariant value = this->get("mere.xdg.icon.theme");
    if (!value.isValid()) return "hicolor";

    return value.toString().toStdString();
}

void Mere::XDG::Config::theme(const std::string &theme)
{
    this->set("mere.xdg.icon.theme", theme.c_str());
}

uint Mere::XDG::Config::size() const
{
    QVariant value = this->get("mere.xdg.icon.size");
    if (!value.isValid()) return 0;

    return value.toUInt();
}

void Mere::XDG::Config::size(const uint &size)
{
    this->set("mere.xdg.icon.size", size);
}

uint Mere::XDG::Config::scale() const
{
    QVariant value = this->get("mere.xdg.icon.scale");
    if (!value.isValid()) return 0;

    return value.toUInt();
}

void Mere::XDG::Config::scale(const uint &scale)
{
    this->set("mere.xdg.icon.scale", scale);
}

std::string Mere::XDG::Config::context() const
{
    QVariant value = this->get("mere.xdg.icon.context");
    if (!value.isValid()) return "apps";

    return value.toString().toStdString();
}

void Mere::XDG::Config::context(const std::string &context)
{
    this->set("mere.xdg.icon.context", context.c_str());
}
