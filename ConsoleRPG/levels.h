#ifndef LEVELS_H
#define LEVELS_H
#include <string>
#include <vector>
#include "player.h"
#include <list>
#include "enemy.h"
#include "shop.h"
using namespace std;
class levels
{
    public:
        void getTreasure(Player &player);
        void updateMonsters(Player &player);
        void  updateVector(Player &player,string EnemyName,string EnemyAttack,string EnemyLevel,string EnemyDef,string EnemyExp,string FULLLINE2,string EnemyValue);
        levels();
      void  initLevel(string,Player&);
      void  print();
      void updateVector(Player&);
    void movePlayer(char,Player&);
    char getTile(int,int);
    int attack();
    char setTile(int,int,char);
    void processMovePlayer(Player&,int,int);
    void processMonsterMove(Player&,int,int,int);
    void battleMonster(Player &player,int targetX,int targetY);
    void initShops(list<Shop> &shops);
void enterShop(Player &player, Shop &shop);
void printScreen(string);
    private:
         vector<string> _screen;
            list<Shop> shops;
        vector<string> gameInfo;
        vector<Enemy> enemy;
        vector<string> _gameData;
        //Iterator
    list<Shop>::iterator lit;
};

#endif // LEVELS_H
