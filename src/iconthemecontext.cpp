#include "iconthemecontext.h"

Mere::XDG::IconThemeContext::IconThemeContext(const std::string &context)
{
    if(!context.compare("Actions"))             m_context = Context::Actions;
    else if(!context.compare("Animations"))     m_context = Context::Animations;
    else if(!context.compare("Applications"))   m_context = Context::Applications;
    else if(!context.compare("Categories"))     m_context = Context::Categories;
    else if(!context.compare("Devices"))        m_context = Context::Devices;
    else if(!context.compare("Emblems"))        m_context = Context::Emblems;
    else if(!context.compare("Emotes"))         m_context = Context::Emotes;
    else if(!context.compare("International"))  m_context = Context::International;
    else if(!context.compare("FileSystems"))    m_context = Context::FileSystems;
    else if(!context.compare("MimeTypes"))      m_context = Context::MimeTypes;
    else if(!context.compare("Places"))         m_context = Context::Places;
    else if(!context.compare("Status"))         m_context = Context::Status;
    else                                        m_context = Context::Unknown;
}

std::string Mere::XDG::IconThemeContext::name() const
{
    std::string name;

    switch (m_context)
    {
        case Context::Actions:
            name = "Actions";
            break;

        case Context::Animations:
            name = "Animations";
            break;

        case Context::Applications:
            name = "Applications";
            break;

        case Context::Categories:
            name = "Categories";
            break;

        case Context::Devices:
            name = "Devices";
            break;

        case Context::Emblems:
            name = "Emblems";
            break;

        case Context::Emotes:
            name = "Emotes";
            break;

        case Context::International:
            name = "International";
            break;

        case Context::FileSystems:
            name = "FileSystems";
            break;

        case Context::MimeTypes:
            name = "MimeTypes";
            break;

        case Context::Places:
            name = "Places";
            break;

        case Context::Status:
            name = "Status";
            break;

        default:
            name = "Unknown";
            break;
    }

    return name;
}

std::string Mere::XDG::IconThemeContext::directory() const
{
    std::string directory;

    switch (m_context)
    {
        case Context::Actions:
            directory = "actions";
            break;

        case Context::Animations:
            directory = "animations";
            break;

        case Context::Applications:
            directory = "apps";
            break;

        case Context::Categories:
            directory = "categories";
            break;

        case Context::Devices:
            directory = "devices";
            break;

        case Context::Emblems:
            directory = "emblems";
            break;

        case Context::Emotes:
            directory = "emotes";
            break;

        case Context::International:
            directory = "intl";
            break;

//        case Context::FileSystems:
//            name = "FileSystems";
//            break;

        case Context::MimeTypes:
            directory = "mimetypes";
            break;

        case Context::Places:
            directory = "places";
            break;

        case Context::Status:
            directory = "status";
            break;

        default:
            directory = "unknown";
            break;

    }

    return directory;
}
