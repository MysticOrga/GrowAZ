/*
** EPITECH PROJECT, 2025
** GrowAZ
** File description:
** Shop
*/

#ifndef SHOP_HPP_
#define SHOP_HPP_
#include <map>
#include <vector>
#include "Object.hpp"

typedef std::map<std::string, Object> ObjectList;
typedef std::vector<std::pair<std::string, long long>> ShopList;

class Shop
{
public:
    Shop() = default;
    ~Shop() = default;

    void addObject(std::string name, Object object);

    bool buyObject(std::string name, Object &obj, long long &money);

    inline ShopList getObjectList(void) const { return _ShopList; }

protected:
private:
    ObjectList _ObjectList;
    ShopList _ShopList;
};

#endif /* !SHOP_HPP_ */
