#include "player.h"
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
Player::Player(){
}
void Player::addExp(int expValue){
_exp+=expValue;
while (_exp>=50){
        cout<<"\nLEVEL UP!                                                              \n";
        _money+=40;
    _exp-=50;
    _attack+=32;
    _defense+=30;
    _health+=60;
    _maxHealth+=60;
    _level++;

}
}
void Player::init(int level,int health,int attack,int defense,int exp,int money)
{
    _money=money;
    setName();
    _level=level;
    _maxHealth=health;
    _health=_maxHealth;
    _attack=attack;
    _defense=defense;
    _exp=exp;
    equipped.push_back(Item("NO ITEM",0,0,0,0,0,0,0));
    equipped.push_back(Item("NO ITEM",0,0,0,0,0,0,0));
    equipped.push_back(Item("NO ITEM",0,0,0,0,0,0,0));
    equipped.push_back(Item("NO ITEM",0,0,0,0,0,0,0));
    equipped.push_back(Item("NO ITEM",0,0,0,0,0,0,0));
    equipped.push_back(Item("NO ITEM",0,0,0,0,0,0,0));
    equipped.push_back(Item("NO ITEM",0,0,0,0,0,0,0));
}
void Player::getPosition(int &x,int &y){
x=_x;
y=_y;
}
void Player::setPosition(int x,int y){
_x=x;
_y=y;
}
int Player::attack(){
srand(time(NULL));
return (rand()%(_attack/10))+_attack*0.9;
}
int Player::takeDamge(int attack){
attack-=_defense;
if(attack>0){
    _health-=attack;
    if(_health<=0){
        return 1;
    }
}
return 0;
}
string Player::getName(){
    return _name;
}
void Player::setName(){
    string Name;
cout << "\n Please Enter Your Name:";
getline(cin,Name);
//cin.ignore(250,'\n');
cin.clear();
_name=Name;
}
void  Player::addMoney(int value){
_money+=value;
}
void Player::subtractMoney(int amount) { _money -= amount; }
void Player::printInventory()
{

    cout << "\n*** " << _name << "'s inventory ***                                    \n                                                          \n";
    cout << "Money: " << _money << " GP                                               \n                                                     \n";
    list<Item>::iterator lit;

    int i = 0;

    for (lit = _items.begin(); lit != _items.end(); lit++) {
        cout << i+1 << ". " << (*lit).getName() << " x " << (*lit).getCount() << " Price: " << (*lit).getValue() << " GP                                                      " << endl;
        i++;
    }
}
void Player::printEquipped(){
    int q=1;
string name;
 cout<<endl;
for(int i=0;i<equipped.size();i++){

        switch(q){
    case 1:
        name="Upper Body:";
    break;
     case 2:
        name="Hand:";
    break;
     case 3:
        name="Shield:";
    break;
     case 4:
        name="Gloves:";
    break;
     case 5:
        name="Boots:";
    break;
     case 6:
        name="Hat:";
    break;
     case 7:
        name="Gauntlets:";
    break;
        }
    cout<<name<<equipped[i].getName()<<string(100,' ')<<endl;
    q++;
}
system("pause");
}
void Player::useItem(){
    string name;
    cout <<"Please Enter Name of The Item You want to use:"<<string(100,' ')<<endl;
    getline(cin,name);
list<Item>::iterator lit;
   int itemN=1;
    int valueOfIn;
    sscanf(name.c_str(), "%d", &valueOfIn);
    for (lit = _items.begin(); lit != _items.end(); lit++,itemN++) {
       if((*lit).getName()==name||valueOfIn==itemN){
        _defense+=(*lit).getDefense();
        _attack+=(*lit).getAttackPower();
        _health+=(*lit).getHP();
    if(_health >_maxHealth){
        _health=_maxHealth;
    }
        _maxHealth+=(*lit).getHealth();

       if((*lit).getType()>0 && (*lit).getType()<8){
            if(equipped[(*lit).getType()-1].getType()>0){
                addItem(equipped[(*lit).getType()-1]);
            }
        equipped[(*lit).getType()-1]=(*lit);

       }
          (*lit).removeOne();
        if((*lit).getCount()==0){
            _items.erase(lit);
        }

       return;}
       }
       cout <<"\nWrong Name!!                           \n";
    }

bool Player::removeItem(string name, Item &newItem)
{
    list<Item>::iterator lit;
    int itemN=1;
    int valueOfIn;
    sscanf(name.c_str(), "%d", &valueOfIn);
    for (lit = _items.begin(); lit != _items.end(); lit++,itemN++) {
        if ((*lit).getName() == name||valueOfIn==itemN) {
            newItem = (*lit);
            (*lit).removeOne();
            if ((*lit).getCount() == 0) {
                _items.erase(lit);
            }
            return true;
        }
    }
    return false;
}
void Player::addItem(Item newItem)
{
    list<Item>::iterator lit;

    for (lit = _items.begin(); lit != _items.end(); lit++) {
        //if the item is already in the inventory, just increase the count
        if ((*lit).getName() == newItem.getName()) {
            (*lit).addOne();
            return;
        }
    }
    //if the item isnt in the inventory, add it
    _items.push_back(newItem);
    _items.back().setCount(1);
}

