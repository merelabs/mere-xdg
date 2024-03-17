#ifndef ICONTHEMEDIRECTORYTRAVERSER_H
#define ICONTHEMEDIRECTORYTRAVERSER_H

#include "global.h"
#include "icontheme.h"

#include <QObject>

namespace Mere::XDG
{

class MERE_XDG_LIB_SPEC IconThemeDirectoryTraverser : public QObject
{
    Q_OBJECT
public:
    explicit IconThemeDirectoryTraverser(QObject *parent = nullptr);

    std::vector<Mere::XDG::IconTheme> traverse() const;
    std::vector<Mere::XDG::IconTheme> traverse(const std::string &path) const;

private:
    std::map<std::string, std::vector<std::string> > files() const;
    std::vector<std::string> files(const std::string &path) const;

signals:
    void traversed(const std::string &path) const;
    void processed(const Mere::XDG::IconTheme &theme) const;

};
}


#endif // ICONTHEMEDIRECTORYTRAVERSER_H
