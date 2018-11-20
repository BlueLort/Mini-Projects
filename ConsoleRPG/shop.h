#ifndef SHOP_H
#define SHOP_H
#include <string>
#include <list>
#include <cstdio>
#include "item.h"
using namespace std;
class Shop
{
public:
    Shop(string name);

    void printShop();
    bool canAffordItem(string name, int money);
    bool purchaseItem(string name, Item &newItem);
    void addItem(Item newItem);


    //Getters
    string getName() { return _name; }

private:
    string _name;
    list<Item> _items;

};

#endif // SHOP_H
