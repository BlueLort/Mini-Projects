#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H
#include "levels.h"
#include "player.h"
#include <windows.h>
#include <vector>
#include <string>
#include <conio.h>
#include <iostream>
#include <cstdlib>
using namespace std;
class GameSystem
{
    public:
        GameSystem(string);

        void playGame();
        void playerMove();
    private:
        Player _player;
        levels _level;


};

#endif // GAMESYSTEM_H
