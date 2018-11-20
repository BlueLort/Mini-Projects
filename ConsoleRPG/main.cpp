#include <iostream>
#include "gamesystem.h"
#include <vector>
#include <fstream>
#include <cstdlib>
using namespace std;
vector<string> screen;
void printScreen(string);
int main()
{
    printScreen("Intro.txt");
    GameSystem Game("Level.txt");
    Game.playGame();

    return 0;
}
void printScreen(string fileName){
    static ifstream file;
    static string Line;
    file.open(fileName);
    if(file.fail()){
            perror (fileName.c_str());
            exit(1);
    }
    while(getline(file,Line)){
        screen.push_back(Line);
    }
    file.close();
    for(int i=0;i<screen.size();i++){
        cout <<screen[i]<<endl;
    }

system("pause");
}
