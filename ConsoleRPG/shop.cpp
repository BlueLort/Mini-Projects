#include "shop.h"

#include <iostream>

//shop constructor
Shop::Shop(string name)
{
    _name = name;
}

//prints out the shop to the screen
void Shop::printShop()
{
    cout << "*** Welcome to " << _name << " ***                         \n                                \n";
    list<Item>::iterator lit;

    int i = 0;

    for (lit = _items.begin(); lit != _items.end(); lit++) {
        cout << i+1 << ". " << (*lit).getName() << " x " << (*lit).getCount() << " Price: " << (*lit).getValue() << " GP" << endl;
        cout << "Defense:"<<(*lit).getDefense()<<" Attack Power:"<<(*lit).getAttackPower()<<" Health:"<<(*lit).getHealth()<<" +HP:"<<(*lit).getHP()<<endl;
        i++;
    }

    cout << endl;

}

//returns true if the the item costs <= money
bool Shop::canAffordItem(string name, int money)
{
    list<Item>::iterator lit;
    int itemN=1;
    int valueOfIn;
    sscanf(name.c_str(), "%d", &valueOfIn);
    for (lit = _items.begin(); lit != _items.end(); lit++,itemN++) {
        if ((*lit).getName() == name ||valueOfIn==itemN) {
            if ((*lit).getValue() <= money) {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

//buy an item from the shop. Returs true if the item is there
bool Shop::purchaseItem(string name, Item &newItem)
{
    list<Item>::iterator lit;
    int itemN=1;
    int valueOfIn;
    sscanf(name.c_str(), "%d", &valueOfIn);
    for (lit = _items.begin(); lit != _items.end(); lit++,itemN++) {
        if ((*lit).getName() == name||valueOfIn==itemN) {

            newItem = (*lit);

            newItem.setCount(1);
            (*lit).removeOne();

            //if the item has a count of 0, we can remove it
            if ((*lit).getCount() == 0) {
                _items.erase(lit);
            }
            return true;
        }
    }
    return false;
}

//add an item to the shop
void Shop::addItem(Item newItem)
{
    list<Item>::iterator lit;

    for (lit = _items.begin(); lit != _items.end(); lit++) {
        //if the item is already in the shop, just increase count and return
      if ((*lit).getName() == newItem.getName()) {

            (*lit).addOne();
            return;
        }
    }

    //if the item isnt in the shop, add it to the shop
    _items.push_back(newItem);
    _items.back().setCount(1);
}
