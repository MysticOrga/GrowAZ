/*
** EPITECH PROJECT, 2025
** GrowAZ
** File description:
** Malus
*/

#ifndef MALUS_HPP_
#define MALUS_HPP_
#include <string>

enum MalusType
{
    MONEY,
    LEAF,
    TREE,
};

class Malus
{
public:
    Malus() = default;

    Malus(MalusType malus, double penalty, std::string name)
        : _malus(malus), _penalty(penalty), _name(name) {}

    ~Malus() = default;

    inline MalusType getMalusType(void) { return _malus; }

    inline double getPenalty(void) { return _penalty; }

    inline std::string getName(void) { return _name; }

protected:
private:
    MalusType _malus;
    double _penalty;
    std::string _name;
};

#endif /* !MALUS_HPP_ */
