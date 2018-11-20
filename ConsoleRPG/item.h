#ifndef ITEM_H
#define ITEM_H


#include <string>
using namespace std;
class Item
{
public:
    //constructor
    Item(string name, int value, int counter,int defense,int attack,int health,int hp,int type);
    Item();

    void addOne();
    void removeOne();

    //Getters
    string getName() { return _name; }
    int getValue() { return _value; }
    int getCount() { return _count; }
    int getHP() { return _hp; }
    int getHealth() { return _health; }
    int getAttackPower() { return _attackPower; }
    int getDefense(){return _defense;}
    int getType(){return _type;}

    //Setters
    void setType(int type){_type=type;}
    void setCount(int amount) { _count = amount; }
    void setHP(int hp) { _hp=hp; }
    void setHealth(int health) { _health=health; }
    void setAttackPower(int ad) { _attackPower=ad; }
    void setDefense(int def){_defense=def;}

private:
    string _name;
    int _hp;
    int _attackPower;
    int _defense;
    int _health;
    int _value;
    int _count;
    int _type;
};
#endif // ITEM_H
