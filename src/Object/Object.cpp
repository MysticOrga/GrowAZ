/*
** EPITECH PROJECT, 2025
** GrowAZ
** File description:
** Object
*/

#include "Object.hpp"

void Object::operator=(const Object &other)
{
    this->_stat = other._stat;
    this->_price = other._price;
    this->_name = other._name;
    this->_buff = other._buff;
}
