#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "item.h"
#include <list>
#include <vector>
#include <cstdio>
using namespace std;
class Player
{
    public:
        int takeDamge(int attack);
        Player();
        int attack();
void addExp(int);
void useItem();
     void   init(int,int,int,int,int,int);
        //setters
void setPosition(int x,int y);
void setName();
//getters
void getPosition(int &x,int &y);
void addMoney(int);
void takeMoney(int);
    void printInventory();
void printEquipped();

    bool removeItem(string name, Item &newItem);
    void addItem(Item newItem);
string getName();
int getLevel(){return _level;}
int getHealth(){return _health;}
int getMaxHealth(){return _maxHealth;}
int getDefense(){return _defense;}
int getAttack(){return _attack;}
int getMoney(){return _money;}
void subtractMoney(int amount);

    private:


        vector<Item>   equipped;
        list<Item> _items;

        //properties
        string _name;
        int _maxHealth;
        int _health;
        int _level;
        int _exp;
        int _defense;
        int _attack;
        int _money;
        int _x;
        int _y;


};

#endif // PLAYER_H
