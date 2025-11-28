/*
** EPITECH PROJECT, 2025
** GrowAZ
** File description:
** Shop
*/

#include "Shop.hpp"
#include <utility>

bool Shop::buyObject(std::string name, Object &obj, long long &money)
{
    Object toBuy = _ObjectList[name];

    if (toBuy.getPrice() > money)
        return false;
    obj = toBuy;
    money -= obj.getPrice();
    return true;
}

void Shop::addObject(std::string name, Object object)
{
    _ObjectList[name] = object;
    _ShopList.push_back(std::make_pair(name, object.getPrice()));
}