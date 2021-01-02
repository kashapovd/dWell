#include "ubook.h"
#include "config.h"

#include <QFile>

user::utype ubook::findUser(const QString &name, const QString &passwd) const
{
    for (const auto &it : mEntries)
        if (it.name() == name.trimmed() and it.passwd() == passwd.trimmed())
            return it.type();

    return user::utype::UNKNOWN;
}

user::utype ubook::findUserByName(const QString &name) const
{
     for (const auto &it : mEntries)
         if(it.name() == name.trimmed())
             return it.type();

     return user::utype::UNKNOWN;
}

bool ubook::insert(user &user)
{
    if (findUser(user.name(), user.passwd()) == user::UNKNOWN)
    {
        mEntries.push_back(std::move(user));
        saveToFile(config::fileUsers);
        return true;
    }
    return false;
}

bool ubook::remove(const uint &idx)
{
    if (idx <= uint(mEntries.size()))
    {
        mEntries.erase(std::next(mEntries.begin(), idx));
        saveToFile(config::fileUsers);
        return true;
    }
    return false;
}

ubook *ubook::getUbook()
{
    ubook *u = new ubook;
    u->loadFromFile(config::fileUsers);
    return u;
}

void ubook::touchFile()
{
    saveToFile(config::fileUsers);
}
