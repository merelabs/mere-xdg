#ifndef DISKCACHE_H
#define DISKCACHE_H

#include <map>

#include <QObject>

namespace Mere
{
namespace XDG
{

class IconLinkCache : public QObject
{
    Q_OBJECT
public:
    explicit IconLinkCache(QObject *parent = nullptr);

    enum class Type
    {
        Disk,
        Memory
    };

    void setAge(unsigned int age, const Type &type);
    void setCapacity(unsigned int capacity);

    void setCache(const std::string &path);

    std::string get(const std::string &key);
    void set(const std::string &key, const std::string &link);

signals:

private:
    static unsigned int g_mage;
    static unsigned int g_dage;
    static unsigned int g_capacity;

    static std::string g_path;

    static std::map<std::string, unsigned int> g_age;
    static std::map<std::string, std::string> g_cache;
};

}
}

#endif // DISKCACHE_H
