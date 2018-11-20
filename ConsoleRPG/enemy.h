#ifndef ENEMY_H
#define ENEMY_H
#include <string>
using namespace std;

class Enemy
{
    public:
        Enemy(string name,char tile,int level,int attack,int defense,int health,int exp,int value);

//setters
void setPosition(int x,int y);
//getters
char getTile(){return _tile;}
void getPosition(int &x,int &y);
string getName(){return _name;}
int attack();
int takeDamge(int attack);
int getDefense(){return _defense;}
// GETS AI MOVE COMMAND

int getLevel(){return _lvl;}
int getHealth(){return _health;}
int getMaxHealth(){return _maxHealth;}

int getAttack(){return _attack;}
int getExp(){return _exp;}
char getMove(int,int);
int getValue(){return _value;}
    private:
        string _name;
        char _tile;
int _maxHealth;
        int _attack;
        int _defense;
        int _health;
        int _exp;
        int _lvl;
        int _value;
        int _x;
        int _y;
};
#endif // ENEMY_H
