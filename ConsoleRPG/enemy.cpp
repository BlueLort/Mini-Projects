#include "enemy.h"
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
Enemy::Enemy(string name,char tile,int level,int attack,int defense,int health,int exp,int value)
{
    _name=name;
    _tile=tile;
    _lvl=level;
    _defense=defense;
     _maxHealth=health;
    _health=_maxHealth;
    _attack=attack;
    _exp=exp;
    _value=value;
}
void Enemy::getPosition(int &x,int &y){
x=_x;
y=_y;
}
void Enemy::setPosition(int x,int y){
_x=x;
_y=y;
}
int Enemy::attack(){
srand(time(NULL));
return (rand()%(_attack/10))+_attack*0.9;
}
int Enemy::takeDamge(int attack){
attack-=_defense;
if(attack>0){
    _health-=attack;
    if(_health<=0){
        return _exp;
    }
}
return 0;
}
char Enemy::getMove(int playerX,int playerY){
    static srand(time(NULL));
int distance;
int dx=playerX-_x;
int dy=playerY-_y;
int adx=abs(playerX-_x);
int ady=abs(playerY-_y);
distance =adx+ady;
if(distance <=5){
if(adx > ady){
if(dx>0){ // MOVING ON X
    return 'd';
    } else {
    return 'a';
    }

}else{
    if (dy>0){ //MOVING ON Y
    return 's';
    }else {
    return 'w';
    }
}
}
switch (rand()%7){
case 0:return 'a';
break;
case 1:return 'd';
break;
case 2:return 'w';
break;
case 3:return 's';
break;
default: return '.';
    break;
}

}
