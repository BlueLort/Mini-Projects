#include "levels.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "player.h"
#include "enemy.h"
#include <string>
#include<sstream>
#include <ctime>
#include <conio.h>
#include <windows.h>
void gotoxy(int x, int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);

    //hide console cursor ///happen after resizing
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
template <typename T>
std::string to_string(T value)
{
    //create an output string stream
    std::ostringstream os ;

    //throw the value into the string stream
    os << value ;

    //convert the string stream into a string and return
    return os.str() ;
}
void levels::getTreasure(Player &player)
{
    srand(time(NULL));
    int number=rand()%6;
    if(number)
    {
        int amount=4000+rand()%8001;
        cout << "Congratulation You got "<<amount<<"!!!!                                 "<<endl;
        player.addMoney(amount);
        system("pause");
        return;
    }
    else
    {
        int damge=4000+rand()%8001;
        player.takeDamge(damge);
        cout << "\n Its a Trap!!                                      \nYou lost "<<damge<<" Health                                \n";
        if(player.getHealth()<=0)
        {

            cout <<"You Died!!                                                          \n";
            system("pause");
            system("cls");

            cout << "Thanks For Playing our text Based Game\nSpecial Thanks:\nMap Design:Abdelrahman Mohamed\n\n";
            printScreen("Lortians Logo.txt");
            exit(0);
        }
    }
}
using namespace std;
void levels::initShops(list<Shop> &shops)
{
    //I added another parameter called count to the Item constructor
    shops.push_back(Shop("Leather Shop"));
    shops.back().addItem(Item("Leather Boots", 5000, 3,0,0,3500,0,5));
    shops.back().addItem(Item("Leather Hat", 5000, 3,0,0,5000,0,6));
    shops.back().addItem(Item("Leather Gloves", 5000, 4,0,50,4000,0,4));
    shops.back().addItem(Item("Leather Gauntlets", 9000, 3,0,1000,700,0,7));
    shops.back().addItem(Item("Leather Chestpiece", 30000, 2,100,0,25000,0,1));

    shops.push_back(Shop("The Blacksmith"));
    shops.back().addItem(Item("Iron Boots", 2500, 2,100,0,1100,0,5));
    shops.back().addItem(Item("Iron Hat", 2000, 3,150,0,650,0,6));
    shops.back().addItem(Item("Iron Gloves", 3200, 2,0,200,600,0,4));
    shops.back().addItem(Item("Iron Gauntlets", 7500, 2,300,600,600,0,7));
    shops.back().addItem(Item("Iron Chestpiece", 12000, 1,1000,0,10000,0,1));
    shops.back().addItem(Item("Iron Sword", 20000, 2,50,3500,0,0,2));
    shops.back().addItem(Item("Iron Shield", 15000, 1,700,0,1500,0,3));
    shops.back().addItem(Item("THE DRAGON SLAYER SWORD!!(Legendary)", 90000, 1,1000,5000,0,0,2));

    shops.push_back(Shop("Fruit Shop"));
    for(int i=0; i<25; i++)
    {
        shops.back().addItem(Item("Grapes", 80, 10,0,0,0,200,8));
        shops.back().addItem(Item("Apple", 100, 50,0,0,0,350,8));
        shops.back().addItem(Item("Orange", 150, 200,0,0,0,1000,8));
        shops.back().addItem(Item("Watermelon", 350, 30,0,0,0,5000,8));
        shops.back().addItem(Item("Tomato", 50, 100,0,0,0,100,8));
    }

}
void levels::enterShop(Player &player, Shop &shop)
{

    bool isDone = false;
    char input;
    string itemName;
    Item newItem("NOITEM", 0, 1,0,0,0,0,0);

    while (isDone == false)
    {
        shop.printShop();
        player.printInventory();
RE_ASK:
        cout << "Would you like to buy or sell? Q to quit. (B/S): ";
        cin >> input;
        cin.ignore(64, '\n');
        cin.clear();

        //If the user types Q, leave the shop
        if (input == 'Q' || input == 'q') return;

        if (input == 'B' || input == 'b')   //buy
        {
            cout << "Enter the item you wish to buy: ";
            getline(cin, itemName);

            if (shop.canAffordItem(itemName, player.getMoney()))
            {

                if (shop.purchaseItem(itemName, newItem) == true)
                {
                    player.addMoney(-newItem.getValue());
                    player.addItem(newItem);
                }
                else
                {
                    cout << "That is an invalid item!\n";
                    system("pause");
                }
            }
            else
            {
                cout << "You don't have enough money!\n";
                system("pause");
            }

        }
        else if(input == 'S' || input == 's')    //sell
        {
            cout << "Enter the item you wish to sell: ";
            getline(cin, itemName);
            if (player.removeItem(itemName, newItem) == true)
            {
                shop.addItem(newItem);
                player.addMoney(newItem.getValue());
            }
            else
            {
                cout << "That is an invalid item!\n";
                system("pause");
            }
        }
        else
        {
            goto RE_ASK;
        }
    }
}
levels::levels()
{
    //ctor
}
void levels::initLevel(string _fileName,Player &player)
{
    // LOADS THE LEVEL
    ifstream fileInput;
    fileInput.open(_fileName);
    if(fileInput.fail())
    {
        perror(_fileName.c_str());
        exit(1);
    }
    string line;
    while(getline(fileInput,line))
    {
        _gameData.push_back(line);
    }
    fileInput.close();
// init market
    initShops(shops);
// PROCESS PLAYER MOVE
    char Tile;
    string FULLLINE=to_string(player.getHealth()) + "/" + to_string(player.getMaxHealth());
    int count=0;
    for(int i=0; i<_gameData.size(); i++)
    {
        for(int j=0; j<_gameData[i].size(); j++)
        {
            Tile=_gameData[i][j];
            switch(Tile)
            {
            //  case 'P':
            // cout << i<<" "<<j<<endl;
            //break;
            case '@':
                player.setPosition(j,i);
                break;
            case ':':
                count+=1;
                switch(count)
                {
                case 1:
                    gameInfo.push_back(player.getName());
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 2:
                    gameInfo.push_back(to_string(player.getLevel()));
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 3:
                    gameInfo.push_back(to_string(player.getAttack()));
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 4:
                    gameInfo.push_back(to_string(player.getDefense()));
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 5:
                    gameInfo.push_back(to_string(FULLLINE));
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 6:
                    gameInfo.push_back(to_string(player.getMoney()));
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 7:

                    gameInfo.push_back("N/A");
                    for(int COUNTER=0; COUNTER<3; COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 8:
                    gameInfo.push_back("N/A");
                    for(int COUNTER=0; COUNTER<3; COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 9:
                    gameInfo.push_back("N/A");
                    for(int COUNTER=0; COUNTER<3; COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 10:
                    gameInfo.push_back("N/A");
                    for(int COUNTER=0; COUNTER<3; COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 11:
                    gameInfo.push_back("N/A");
                    for(int COUNTER=0; COUNTER<3; COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 12:
                    gameInfo.push_back("N/A");
                    for(int COUNTER=0; COUNTER<3; COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;

                case 13:
                    gameInfo.push_back("N/A");
                    for(int COUNTER=0; COUNTER<3; COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                }

            case 'S':
                enemy.push_back(Enemy("Snake",'S',1,50,15,150,50,425));
                enemy.back().setPosition(j,i);
                break;
            case 'G':
                enemy.push_back(Enemy("Goblin",'G',20,690,525,1250,150,700));
                enemy.back().setPosition(j,i);
                break;
            case 'O':
                enemy.push_back(Enemy("Ogre",'O',140,8000,8400,6000,500,4000));
                enemy.back().setPosition(j,i);
                break;
            case 'D':
                enemy.push_back(Enemy("Dragon",'D',9999,25000,6000,100000,30000,10000));
                enemy.back().setPosition(j,i);
                break;
            case 'B':
                enemy.push_back(Enemy("Bandit",'B',70,6250,3200,2500,750,2000));
                enemy.back().setPosition(j,i);
                break;
            default:
                break;
            }
        }
    }

}
void  levels::print()
{
    gotoxy(0,0);
    for(int i=0; i<_gameData.size(); i++)
    {
        cout << _gameData[i]<<endl;
    }
    gotoxy(0,50);
}
void levels::movePlayer(char input,Player &player)
{
    bool done=false;
    char Done;
    int playerX,playerY;
    player.getPosition(playerX,playerY);

    switch (input)
    {
    case (char)224:
        input=_getch();
        if(input==(char)72)
        {
            processMovePlayer(player,playerX,playerY-1);
        }
        else if(input==(char)75)
        {
            processMovePlayer(player,playerX-1,playerY);
        }
        else if(input==(char)80)
        {
            processMovePlayer(player,playerX,playerY+1);
        }
        else if(input==(char)77)
        {
            processMovePlayer(player,playerX+1,playerY);
        }
        break;
    ///WASD CONTROL
    /*case 'w':
    processMovePlayer(player,playerX,playerY-1);
    break;
    case 'a':
    processMovePlayer(player,playerX-1,playerY);
    break;
    case 's':
    processMovePlayer(player,playerX,playerY+1);
    break;
    case 'd':
    processMovePlayer(player,playerX+1,playerY);
    break;
    */

    case 'i':

        while(done==false)
        {
            player.printInventory();
            player.useItem();
            cout <<"\nPress q to close inventory or anything else to try again                               \n                          ";
            Done=_getch();
            if(Done=='q')
            {
                done=true;
            }
        }
        break;
    case'e':
        cout <<"\n*** Equipped Items ***\n\n";
        player.printEquipped();

        break;
    }

}
char levels::getTile(int x,int y)
{
    return _gameData[y][x];
}
char levels::setTile(int targetX,int targetY,char tile)
{
    _gameData[targetY][targetX]=tile;
}
void levels::processMovePlayer(Player &player,int targetX,int targetY)
{
    int playerXX;
    int playerYY;
    bool isDone = false;
    string shopName;
    player.getPosition(playerXX,playerYY);
    switch(getTile(targetX,targetY))
    {
    case'.':
        updateVector(player);
        setTile(playerXX,playerYY,'.');
        setTile(targetX,targetY,'@');
        player.setPosition(targetX,targetY);
        break;
    case '#':
        break;
    case '~':

        while (isDone == false)
        {
            cout << "\n*** Welcome To The Market ***\nShops:\n";
            int i = 1;
            //Print out all the shop names
            for (lit = shops.begin(); lit != shops.end(); lit++)
            {
                cout << i << ". " << (*lit).getName() << endl;
                i++;
            }

            cout << "\nWhat shop would you like to enter? Q to quit: ";
            //Get an entire line of input
            getline(cin, shopName);

            //If the user wants to quit, then quit. Notice I use "Q" and not 'Q' since shopName is a string
            if (shopName == "Q" || shopName == "q")
            {
                isDone = true;
            }
            else
            {

                cout << endl;

                bool validShop = false;
                int shopN=1;
                int valueOfIn;
                sscanf(shopName.c_str(), "%d", &valueOfIn);
                //check to see if the user entered a valid shop
                for (lit = shops.begin(); lit != shops.end(); lit++,shopN++)
                {
                    if ((*lit).getName() == shopName||valueOfIn==shopN)
                    {
                        enterShop(player, (*lit));
                        validShop = true;
                    }
                }

                if (validShop == false)
                {
                    cout << "Invalid Shop!\n";
                    system("pause");

                }
            }

        }


        break;
    case'T':
        getTreasure(player);
        updateVector(player);
        setTile(playerXX,playerYY,'.');
        setTile(targetX,targetY,'@');
        player.setPosition(targetX,targetY);
        break;
    default:
        battleMonster(player,targetX,targetY);
        break;
    }


}
void levels::printScreen(string fileName)
{
    static ifstream file;
    static string Line;
    file.open(fileName);
    while(getline(file,Line))
    {
        _screen.push_back(Line);
    }
    file.close();
    for(int i=0; i<_screen.size(); i++)
    {
        cout <<_screen[i]<<endl;
    }

    system("pause");
}

void levels::battleMonster(Player &player,int targetX,int targetY)
{
    int enemyX;
    int enemyY;
    int playerXx;
    int playerYy;
    int totalDamge;
    bool GameDone=false;
    player.getPosition(playerXx,playerYy);
    int attackRoll;
    int attackResult;
    for(int i=0; i<enemy.size(); i++)
    {
        enemy[i].getPosition(enemyX,enemyY);
        string EnemyName=enemy[i].getName();
        if(targetX ==enemyX && targetY== enemyY)
        {
            string EnemyAttack=to_string(enemy[i].getAttack());
            string EnemyLevel=to_string(enemy[i].getLevel());
            string EnemyDef=to_string(enemy[i].getDefense());
            string EnemyExp=to_string(enemy[i].getExp());
            string FULLLINE2=to_string(enemy[i].getHealth()) + "/" + to_string(enemy[i].getMaxHealth());
            string EnemyValue=to_string(enemy[i].getValue());
            updateVector(player,EnemyName,EnemyAttack,EnemyLevel,EnemyDef,EnemyExp,FULLLINE2,EnemyValue);
            print();
             //battle
            attackRoll=player.attack();

            attackResult=enemy[i].takeDamge(attackRoll);
            totalDamge=attackRoll-enemy[i].getDefense();
            if(totalDamge<0)
            {
                totalDamge=0;
            }
            printf("Player Attacked %s dealt %d Damage\n",EnemyName.c_str(),totalDamge);
            if(attackResult!=0)
            {
                setTile(targetX,targetY,'.');
                if(enemy[i].getTile()=='D')
                {
                    GameDone=true;
                }
                // Removes the Enemy
                player.addMoney(enemy[i].getValue());
                enemy[i]=enemy.back();
                enemy.pop_back();
                if(i!=0)
                {
                    i--;   // to make the counter doesnt ignore the swapped enemy
                }

                printf("\n%s Died!!\n",EnemyName.c_str());


                player.addExp(attackResult);
                if(GameDone)
                {
                    system("cls");
                    cout <<"Congratulations !!! YOU HAVE KILLED THE DRAGON AND SAVED THE WORLD !!                             \n";
                    cout << "Thanks For Playing our text Based Game                        \n                     \n";
                    printScreen("Lortians Logo.txt");
                    exit(0);
                }
                return;
            }
// Monster Turn
            attackRoll=enemy[i].attack();
            totalDamge=attackRoll-player.getDefense();
             if(totalDamge<0){
                        totalDamge=0;
                    }
                   printf("%s Attacked Player dealt %d Damage\n",EnemyName.c_str(),totalDamge);
                   printf("                             ");
                    attackResult=player.takeDamge(attackRoll);
                    if(attackResult!=0){
                            setTile(playerXx,playerYy,'x');
                            printf("\nYou Died!!                             \n");
                       system("pause");
                         system("cls");
                cout <<"You Died!!                            \n";
                cout << "Thanks For Playing our text Based Game              \nMap Design:Abdelrahman Mohamed                 \n                    \n";
                printScreen("Lortians Logo.txt");
                exit(0);
                    }
        }

    }
    system("pause");
}
void levels::updateMonsters(Player &player)
{
    int playerX,playerY,enemyX,enemyY;

    player.getPosition(playerX,playerY);
    char AImove;
    for(int i=0; i<enemy.size(); i++)
    {
        enemy[i].getPosition(enemyX,enemyY);
        AImove=enemy[i].getMove(playerX,playerY);
        switch (AImove)
        {
        case 'w':
            processMonsterMove(player,i,enemyX,enemyY-1);
            break;
        case 'a':
            processMonsterMove(player,i,enemyX-1,enemyY);
            break;
        case 's':
            processMonsterMove(player,i,enemyX,enemyY+1);
            break;
        case 'd':
            processMonsterMove(player,i,enemyX+1,enemyY);
            break;


        }
    }
}
void levels::processMonsterMove(Player &player,int enemyIndex,int targetX,int targetY)
{
    int playerXX;
    int playerYY;
    int enemyX;
    bool flag=true;
    int enemyY;
    string EnemyName=enemy[enemyIndex].getName();
    string EnemyAttack=to_string(enemy[enemyIndex].getAttack());
    string EnemyLevel=to_string(enemy[enemyIndex].getLevel());
    string EnemyDef=to_string(enemy[enemyIndex].getDefense());
    string EnemyExp=to_string(enemy[enemyIndex].getExp());
    string FULLLINE2=to_string(enemy[enemyIndex].getHealth()) + "/" + to_string(enemy[enemyIndex].getMaxHealth());
    string EnemyValue=to_string(enemy[enemyIndex].getValue());
    enemy[enemyIndex].getPosition(enemyX,enemyY);
    player.getPosition(playerXX,playerYY);
    switch(getTile(targetX,targetY))
    {
    case'.':
        setTile(enemyX,enemyY,'.');
        setTile(targetX,targetY,enemy[enemyIndex].getTile());
        enemy[enemyIndex].setPosition(targetX,targetY);
        break;
    case '@':

        battleMonster(player,enemyX,enemyY);
        break;
    }
}
void  levels::updateVector(Player &player)
{
    int count=0;
    string FULLLINE=to_string(player.getHealth()) + "/" + to_string(player.getMaxHealth());
    char Tile;
    for(int i=0; i<_gameData.size(); i++)
    {
        for(int j=0; j<_gameData[i].size(); j++)
        {
            Tile=_gameData[i][j];
            switch(Tile)
            {
            case ':':
                count+=1;
                switch(count)
                {
                case 2:
                    gameInfo[count-1]=to_string(player.getLevel());
                    for(int COUNTER=0; COUNTER<to_string(player.getLevel()).size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 3:
                    gameInfo[count-1]=to_string(player.getAttack());
                    for(int COUNTER=0; COUNTER<to_string(player.getAttack()).size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 4:
                    gameInfo[count-1]=to_string(player.getDefense());
                    for(int COUNTER=0; COUNTER<to_string(player.getDefense()).size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 5:
                    gameInfo[count-1]=FULLLINE;
                    for(int COUNTER=0; COUNTER<FULLLINE.size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 6:
                    gameInfo[count-1]=to_string(player.getMoney())+"     ";
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 7:

                    gameInfo[count-1]="N/A           ";
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;

                case 8:
                    gameInfo[count-1]="N/A           ";
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 9:
                    gameInfo[count-1]="N/A           ";
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 10:
                    gameInfo[count-1]="N/A           ";
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 11:
                    gameInfo[count-1]="N/A           ";
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 12:
                    gameInfo[count-1]="N/A           ";
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 13:
                    gameInfo[count-1]="N/A           ";
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                }
            }
        }
    }
}
void  levels::updateVector(Player &player,string EnemyName,string EnemyAttack,string EnemyLevel,string EnemyDef,string EnemyExp,string FULLLINE2,string EnemyValue)
{
    int count=0;

    string FULLLINE=to_string(player.getHealth()) + "/" + to_string(player.getMaxHealth())+"  ";
    char Tile;
    for(int i=0; i<_gameData.size(); i++)
    {
        for(int j=0; j<_gameData[i].size(); j++)
        {
            Tile=_gameData[i][j];
            switch(Tile)
            {
            case ':':
                count+=1;
                switch(count)
                {
                case 2:
                    gameInfo[count-1]=to_string(player.getLevel())+"     ";
                    for(int COUNTER=0; COUNTER<to_string(player.getLevel()).size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 3:
                    gameInfo[count-1]=to_string(player.getAttack())+"     ";
                    for(int COUNTER=0; COUNTER<to_string(player.getAttack()).size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 4:
                    gameInfo[count-1]=to_string(player.getDefense())+"     ";
                    for(int COUNTER=0; COUNTER<to_string(player.getDefense()).size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 5:
                    gameInfo[count-1]=FULLLINE;
                    for(int COUNTER=0; COUNTER<FULLLINE.size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;

                case 6:
                    gameInfo[count-1]=to_string(player.getMoney())+"     ";
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 7:


                    gameInfo[count-1]=EnemyName+"   ";

                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 8:



                    gameInfo[count-1]=FULLLINE2+"      ";
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 9:


                    gameInfo[count-1]=EnemyLevel+"   ";
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 10:


                    gameInfo[count-1]=EnemyAttack+"    ";
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 11:

                    gameInfo[count-1]=EnemyDef+"    ";
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 12:

                    gameInfo[count-1]=EnemyExp+"    ";
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                case 13:

                    gameInfo[count-1]=EnemyValue+"    ";
                    for(int COUNTER=0; COUNTER<gameInfo[count-1].size(); COUNTER++)
                    {
                        _gameData[i][j+1+COUNTER]=gameInfo[count-1][COUNTER];
                    }
                    break;
                }
            }
        }
    }
}
