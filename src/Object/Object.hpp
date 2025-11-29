/*
** EPITECH PROJECT, 2025
** GrowAZ
** File description:
** AObject
*/

#ifndef OBJECT_HPP_
#define OBJECT_HPP_
#include <string>

enum StatBuff
{
    TREE_SIZE,
    LEAF_DROP,
    MALUS_DROP,
    CLIENT_DROP,
    COPS_DROP,
    AUTO_CLICK,
};

class Object
{
public:
    Object() = default;

    Object(StatBuff stat, double buff, const char *name, long long price)
        : _stat(stat), _buff(buff), _name(name), _price(price) {}

    ~Object() = default;

    inline double getBuff(void) const { return _buff; }

    inline StatBuff getStatToBuff(void) const { return _stat; }

    inline std::string getName(void) const { return _name; }

    inline long long getPrice(void) const { return _price; }

    void operator= (const Object &other);

protected:
private:
    StatBuff _stat;
    double _buff;
    std::string _name;
    long long _price;
};

#endif /* !AOBJECT_HPP_ */
