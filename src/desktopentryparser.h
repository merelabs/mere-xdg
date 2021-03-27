#ifndef MERE_XDG_DESKTOPENTRYPARSER_H
#define MERE_XDG_DESKTOPENTRYPARSER_H

#include "global.h"
#include "desktopentry.h"
#include "desktopentryaction.h"

#include <QObject>

namespace Mere
{
namespace XDG
{

class DesktopEntryParser : public QObject
{
    Q_OBJECT
public:
    ~DesktopEntryParser();
    explicit DesktopEntryParser(const std::string &path, QObject *parent = nullptr);
    bool parse();

    DesktopEntry entry() const;

private:
    std::string id() const;
    std::string base() const;

    bool comment(const std::string &line) const;
    std::string key(const std::string &line) const;
    std::string value(const std::string &line) const;

    std::set<std::string> categories(const std::string &value) const;
    std::set<DesktopEntryAction> actions(std::ifstream &file, std::string &line) const;

signals:
private:
    std::string m_path;
    DesktopEntry m_entry;
};

}
}

#endif // MERE_XDG_DESKTOPENTRYPARSER_H
