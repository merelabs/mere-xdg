#include "desktopentry.h"

Mere::XDG::DesktopEntry::~DesktopEntry()
{

}

Mere::XDG::DesktopEntry::DesktopEntry()
{

}

Mere::XDG::DesktopEntry::DesktopEntry(QString &path)
{
    Q_UNUSED(path);
}

QVariant Mere::XDG::DesktopEntry::get(Attribute attrbute)
{
    return this->attributes.value(attrbute);
}

void Mere::XDG::DesktopEntry::set(Attribute attrbute, QVariant value)
{
    this->attributes.insert(attrbute, value);
}
