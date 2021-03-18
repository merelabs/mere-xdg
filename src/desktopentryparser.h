#ifndef DESKTOPENTRYPARSER_H
#define DESKTOPENTRYPARSER_H

#include "global.h"
#include "desktopentry.h"

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
    bool comment(const std::string &line) const;
    std::string key(const std::string &line) const;
    std::string value(const std::string &line) const;

    std::set<std::string> categories(const std::string &value) const;

signals:
private:
    std::string m_path;
    DesktopEntry m_entry;
};

}
}

#endif // DESKTOPENTRYPARSER_H
