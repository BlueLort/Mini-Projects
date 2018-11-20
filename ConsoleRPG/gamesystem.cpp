#include "gamesystem.h"

GameSystem::GameSystem(string _fileName)
{
    _player.init(1,200,45,35,0,100);
    _level.initLevel(_fileName,_player);
}
void GameSystem::playGame(){
    bool isDone=false;
    while(isDone!=true){
_level.print();
playerMove();
_level.updateMonsters(_player);



    }
}
void GameSystem::playerMove(){
char input;
Sleep(100);
if(_kbhit())
input =_getch();
else input=0;
_level.movePlayer(input,_player);

}

