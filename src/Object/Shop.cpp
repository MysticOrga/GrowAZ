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

void Shop::addObject(StatBuff stat, double buff, const char *name, long long price)
{
    Object obj(stat, buff, name, price);

    _ObjectList[name] = obj;
    _ShopList.push_back(std::make_pair(obj.getName(), obj.getPrice()));
}

void Shop::addObject(Object object)
{
    _ObjectList[object.getName()] = object;
    _ShopList.push_back(std::make_pair(object.getName(), object.getPrice()));
}