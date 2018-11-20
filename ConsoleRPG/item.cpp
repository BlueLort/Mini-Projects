#include "Item.h"

//item constructor
Item::Item(string name, int value, int counter,int defense,int attack,int health,int hp,int type)
{
    _name = name;
    _value = value;
    _count = counter;
    _defense=defense;
    _attackPower=attack;
    _health=health;
    _hp=hp;
    _type=type;
}

//adds an item
void Item::addOne()
{
    _count++;
}

//removes an item
void Item::removeOne()
{
    if (_count > 0) {
        _count--;
    }
}
