#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>
#include <algorithm>
#include <iomanip>

using namespace std;

struct point
{
    int x;
    int y;
};


struct corners
{
    point topLeft;
    point botRight;
};


struct player
{
    string name;
    string symbol;
    int loses = 0;
    int wins = 0;
    int ties = 0;
    int pieces;
    bool capability;

    void newWins()
    {
        wins++;
    }

    void newLoses()
    {
        loses++;
    }

    void newTies()
    {
        ties++;
    }

    int getScore()
    {
        const int winscore = 3, losescore = -3, tiescore = 1;
        
        return (wins * winscore) + (loses * losescore) + (ties * tiescore);
    }

    string info()
    {
        return (name + " " + to_string(wins) + " " + to_string(loses) + " " + to_string(ties));
    }
};


struct gameData
{
    string saved[100][100];
    player firstPlayer;
    player secondPlayer;
    player currentPlayer;
};


void menu();
void selectMenu();
void space(string **jadval, int n, int m);
void correctMove(corners &box, corners limit, point paresh);
void boldMenu();
void normalMenu();
void print(string **jadval, int n, int m);
void stringToChar(string **jadval, string word, int i, int j);

void newGame(int &savedCounter);
void baseTable();
void find(int arr[], int size, int paresh);
bool search(int dot[], int i, int size);
void houseBolder(corners current);
void SaveTable();
void normalizeHouse(corners current);
int nextMove(corners &current, player &currentPlayer, int &savedCounter);
void printTable(string table[][200], player &currentPlayer);
void correctMoveTable(corners &boldPart, point paresh, corners limit);
void space(string table[][200], int n, int m);
player changeTurn(player &current);
int digits(int number);
int horRight(corners current, player &currentPlayer);
int horLeft(corners current, player &currentPlayer);
int verTop(corners current, player &currentPlayer);
int verBottom(corners current, player &currentPlayer);
int mainDiagonalTop(corners current, player &currentPlayer);
int mainDiagonalBottom(corners current, player &currentPlayer);
int antiDiagonalTop(corners current, player &currentPlayer);
int antiDiagonalBottom(corners current, player &currentPlayer);
void filler(corners current, player &currentPlayer);
bool isAllowed(corners current, player &currentPlayer);
bool endCheck(corners current, player &currentPlayer);
void winnerFind(int &savedCounter);
void saveGame(corners current, player currentPlayer, int &savedCounter, gameData currentGame);
void loadGame(corners current, player currentPlayer, int &savedCounter, gameData currentGame);
void readData();
void update();
void checkName(string name);
bool compareTo(player p1, player p2);
void sortData();
void printRanking();

string **menuTable;
string table[200][200] = { };
string tableCopy[200][200] = { };

int nMenu, mMenu, tableSize, m, n;

corners limitMenu, currentMenu, limitTable;

point jumpMenu, jumpTable;

player firstPlayer, secondPlayer, currentPlayer;

corners current;
gameData currentGame;
int savedCounter;

// data
vector<player> players;

int main()
{
    system("Color 70");
    readData();
    menu();
    return 0;
}


void menu()
{
    nMenu = 17;
    mMenu = 17;
    
    jumpMenu.x = 4;
    jumpMenu.y = 4;
    jumpTable.x = 2;
    jumpTable.y = 6;

    currentMenu.topLeft.x = 0;
    currentMenu.topLeft.y = 0;
    currentMenu.botRight.x = 4;
    currentMenu.botRight.y = 16;

    limitMenu.topLeft.x = 0;
    limitMenu.topLeft.y = 0;
    limitMenu.botRight.x = 16;
    limitMenu.botRight.y = 16;

    menuTable = new string *[nMenu];
    for (int i = 0; i < nMenu; i++)
    {
        menuTable[i] = new string[mMenu];
    }

    space(menuTable, nMenu, mMenu);

    //draw menu table
    menuTable[0][0] = "\u250f";
    for (int j = 1; j < mMenu - 1; j++)
    {
        menuTable[0][j] = "\u2501";
    }
    menuTable[0][mMenu - 1] = "\u2513";

    for (int i = 1; i < nMenu - 1; i++)
    {
        if (i % 4 == 0)
        {
            menuTable[i][0] = "\u2523";
            menuTable[i][mMenu - 1] = "\u252b";
            for (int j = 1; j < mMenu - 1; j++)
            {
                menuTable[i][j] = "\u2501";
            }
        }

        else
        {
            menuTable[i][0] = "\u2503";
            menuTable[i][mMenu - 1] = "\u2503";
        }
    }

    menuTable[nMenu - 1][0] = "\u2517";
    for (int i = 1; i < nMenu - 1; i++)
    {
        menuTable[nMenu - 1][i] = "\u2501";
    }
    menuTable[nMenu - 1][mMenu - 1] = "\u251b";

    // write strings on the menu table
    stringToChar(menuTable, "NEW GAME", 2, 4);
    stringToChar(menuTable, "LOAD GAME", 6, 4);
    stringToChar(menuTable, "RANKING", 10, 4);
    stringToChar(menuTable, "EXIT", 14, 6);

    print(menuTable, nMenu, mMenu);
    system("cls");

    selectMenu();
}


//fill the table with space
void space(string **jadval, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            jadval[i][j] = " ";
        }
    }
}


void print(string **jadval, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << jadval[i][j];
        }
        cout << endl;
    }
}


// to decide an option from menu table
void selectMenu()
{

    boldMenu();


    char move = getch();

    while(move != '\r')
    {
        normalMenu();

        if(move == 'w')
        {
            currentMenu.topLeft.x -= jumpMenu.x;
            currentMenu.botRight.x -= jumpMenu.x;
        }

        if(move == 's')
        {
            currentMenu.topLeft.x += jumpMenu.x;
            currentMenu.botRight.x += jumpMenu.x;
        }

        correctMove(currentMenu, limitMenu, jumpMenu);
        system("cls");

        boldMenu();
        move = getch();

    }

    if (move == '\r')
    {
        system("cls");

        if (menuTable[currentMenu.topLeft.x + 2][currentMenu.topLeft.y + 4] == "N")
        {
            int savedCounter = 0;
            newGame(savedCounter);
        }

        else if (menuTable[currentMenu.topLeft.x + 2][currentMenu.topLeft.y + 4] == "L")
        {
            loadGame(current, currentPlayer, savedCounter, currentGame);
        }

        else if (menuTable[currentMenu.topLeft.x + 2][currentMenu.topLeft.y + 4] == "R")
        {
            printRanking();
            cout << "BACK TO MENU? (yes/no)";
            string answer;
            cin >> answer;
            if (answer == "yes")
            {
                menu();
            }
            else
            {
                exit(3);
            }
        }

        else if (menuTable[currentMenu.topLeft.x + 2][currentMenu.topLeft.y + 6] == "E")
        {
            cout << "DO YOU WANT TO QUIT? (yes/no)" << endl;
            string answer;
            cin >> answer;
            if (answer == "yes")
            {
                exit(3);
            }

            else if (answer == "no")
            {
                menu();
            }
        }
    }
}


// put the string we want in the table
void stringToChar(string **jadval, string word, int i, int j)
{
    for (int character = 0; character < word.size(); character++)
    {
        jadval[i][j] = word[character];
        j++;
    }
}


// when we are out of the menu it will bring us back to the right place
void correctMove(corners &box, corners limit, point paresh)
{
    if (box.topLeft.x == limit.botRight.x)
    {
        box.topLeft.x = limit.topLeft.x;
        box.botRight.x = paresh.x;
    }
    
    else if (box.botRight.x == limit.topLeft.x)
    {
        box.topLeft.x = limit.botRight.x - paresh.x;
        box.botRight.x = limit.botRight.x;
    }

}


// to bold a house of a menu
void boldMenu()
{
    // bold arz
    for (int i = currentMenu.topLeft.x + 1; i < currentMenu.botRight.x; i++)
    {
        menuTable[i][0] = "\u2551";
        menuTable[i][16]= "\u2551";
    }

    //bold tool
    for (int j = currentMenu.topLeft.y + 1; j < currentMenu.botRight.y; j++)
    {
        menuTable[currentMenu.topLeft.x][j] = "\u2550";
        menuTable[currentMenu.botRight.x][j]= "\u2550";
    }

    //bold goshe ha
    menuTable[currentMenu.topLeft.x][currentMenu.topLeft.y] = "\u2554";
    menuTable[currentMenu.topLeft.x][currentMenu.botRight.y] = "\u2557";
    menuTable[currentMenu.botRight.x][currentMenu.topLeft.y] = "\u255A";
    menuTable[currentMenu.botRight.x][currentMenu.botRight.y] = "\u255D";

    print(menuTable, nMenu, mMenu);
}


// unbold a house of the menu
void normalMenu()
{
    for (int i = currentMenu.topLeft.x + 1; i < currentMenu.botRight.x; i++)
    {
        menuTable[i][0] = "\u2503";
        menuTable[i][16]= "\u2503";
    }

    for (int j = currentMenu.topLeft.y + 1; j < currentMenu.botRight.y; j++)
    {
        menuTable[currentMenu.topLeft.x][j] = "\u2501";
        menuTable[currentMenu.botRight.x][j]= "\u2501";
    }

    if (currentMenu.topLeft.x == 0 && currentMenu.topLeft.y == 0)
    {
        menuTable[currentMenu.topLeft.x][currentMenu.topLeft.y] = "\u250F";
        menuTable[currentMenu.topLeft.x][currentMenu.botRight.y] = "\u2513";
        menuTable[currentMenu.botRight.x][currentMenu.topLeft.y] = "\u2523";
        menuTable[currentMenu.botRight.x][currentMenu.botRight.y] = "\u252B";
    }
    else if (currentMenu.topLeft.x == 12 && currentMenu.topLeft.y == 0)
    {
        menuTable[currentMenu.topLeft.x][currentMenu.topLeft.y] = "\u2523";
        menuTable[currentMenu.topLeft.x][currentMenu.botRight.y] = "\u252B";
        menuTable[currentMenu.botRight.x][currentMenu.topLeft.y] = "\u2517";
        menuTable[currentMenu.botRight.x][currentMenu.botRight.y] = "\u251B";
    }
    else
    {
        menuTable[currentMenu.topLeft.x][currentMenu.topLeft.y] = "\u2523";
        menuTable[currentMenu.topLeft.x][currentMenu.botRight.y] = "\u252B";
        menuTable[currentMenu.botRight.x][currentMenu.topLeft.y] = "\u2523";
        menuTable[currentMenu.botRight.x][currentMenu.botRight.y] = "\u252B";
    }

}



void newGame(int &savedCounter)
{
    //recieving players info
    system("CLS");

    cout << "Enter first player's name:(less than 7 characters)" << endl;
    cin >> firstPlayer.name;
    checkName(firstPlayer.name);

    while (firstPlayer.name.size() > 8)
    {
        system("CLS");
        cout << "Your name if too long, try another name" << endl; 
        cin >> firstPlayer.name;
    }

    system("CLS");

    cout << "Enter second player's name:(less than 7 characters)" << endl;
    cin >> secondPlayer.name;
    checkName(secondPlayer.name);

    while (secondPlayer.name.size() > 8)
    {
        system("CLS");
        cout << "Your name if too long, try another name" << endl; 
        cin >> secondPlayer.name;
    }
    system("CLS");

    //creating default table
    baseTable();
    SaveTable();

    //selecting the first house
    corners current; 

    current.topLeft.x = 0;
    current.topLeft.y = 0;

    current.botRight.x = 2;
    current.botRight.y = 6;

    //filling 4 middle houses
    table[(n - 1) / 2 - 1][(m - 1) / 2 - 3] = "O";
    table[(n - 1) / 2 - 1][(m - 1) / 2 + 3] = "X";
    table[(n - 1) / 2 + 1][(m - 1) / 2 + 3] = "O";
    table[(n - 1) / 2 + 1][(m - 1) / 2 - 3] = "X";

    //players base info
    firstPlayer.symbol = "O";
    secondPlayer.symbol = "X";

    firstPlayer.pieces = 2;
    secondPlayer.pieces = 2;

    firstPlayer.wins = 0;
    secondPlayer.wins = 0;

    firstPlayer.loses = 0;
    secondPlayer.loses = 0;

    firstPlayer.ties = 0;
    secondPlayer.ties = 0;

    firstPlayer.capability = true;
    secondPlayer.capability = true;

    player currentPlayer = firstPlayer;

    //bolding the first house
    houseBolder(current);
    system ("CLS");
    printTable(table, currentPlayer);  
    normalizeHouse(current);

    //moves
    while (firstPlayer.pieces + secondPlayer.pieces != tableSize * tableSize &&
          (firstPlayer.capability == true || secondPlayer.capability == true))
    {
        nextMove(current, currentPlayer, savedCounter);
        table[current.topLeft.x + 1][current.topLeft.y + 3] = currentPlayer.symbol;
        filler(current, currentPlayer);

        if (currentPlayer.symbol == secondPlayer.symbol)
        {
            secondPlayer.pieces ++;
        }

        else
        {
            firstPlayer.pieces ++;
        }
        currentPlayer = changeTurn(currentPlayer);

        system ("CLS");
        printTable(table, currentPlayer);
    }

    winnerFind(savedCounter);
}


void winnerFind(int &savedCounter)
{
    firstPlayer.pieces = 0;
    secondPlayer.pieces = 0;

    for (int i = 0; i < n; i = i + 2)
    {
        for (int j = 0; j < m; j = j + 6)
        {
            if (table[i + 1][j + 3] == firstPlayer.symbol)
            {
                firstPlayer.pieces ++;
            }

            else if (table[i + 1][j + 3] == secondPlayer.symbol)
            {
                secondPlayer.pieces ++;
            }
        }
    }

    if (firstPlayer.pieces > secondPlayer.pieces)
    {
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i].name == firstPlayer.name)
            {
                players[i].newWins();
            }

            if (players[i].name == secondPlayer.name)
            {
                players[i].newLoses();
            }
        }

        cout << "THE WINNER IS : " << firstPlayer.name << endl;
    }

    else if (secondPlayer.pieces > firstPlayer.pieces)
    {
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i].name == secondPlayer.name)
            {
                players[i].newWins();
            }

            if (players[i].name == firstPlayer.name)
            {
                players[i].newLoses();
            }
        }

        cout << "THE WINNER IS : " << secondPlayer.name << endl;
    }

    else
    {
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i].name == secondPlayer.name)
            {
                players[i].newTies();
            }

            if (players[i].name == firstPlayer.name)
            {
                players[i].newTies();
            }
        }
        cout << "TIE" << endl;
    }

    update();

    //check if the user want to end the game or not
    cout << "WISH TO PLAY A NEW GAME?(yes/no)" << endl;
    string answer;
    cin >> answer;
    if (answer == "yes")
    {
        newGame(savedCounter);
    }
    else if (answer == "no")
    {
        menu();
    }
}


//make our defult othello table
void baseTable()
{
    cout << "Enter your desired table size to play:" << endl;
    cin >> tableSize;

    m = 6 * tableSize + 1;
    n = 2 * tableSize + 1;

    limitTable.topLeft.x = 0;
    limitTable.topLeft.y = 0;
    limitTable.botRight.x = n - 1;
    limitTable.botRight.y = m - 1;

    int horDot[tableSize - 1];
    int verDot[tableSize - 1];

    find(horDot, tableSize, 6);
    find(verDot, tableSize, 2);

    space(table, n, m);


    //first line of the table
    table[0][0] = "\u250f";
    for(int j = 1; j < m - 1; j++)
    {
        if (search(horDot, j, tableSize) == true)
        {
            table[0][j] = "\u2533";
        }

        else
        {
            table[0][j] = "\u2501";
        }
    }
    table[0][m - 1] = "\u2513";


    //lines inside the table
    for ( int i = 1; i < n - 1; i++)
    {
        //first and last index of the line
        if(search(verDot, i, tableSize) == true)
        {
            table[i][0] = "\u2523";
            table[i][m - 1] = "\u252b";
        }

        else
        {
            table[i][0] = "\u2503";
            table[i][m - 1] = "\u2503";
        }

        //middle indexes
        for(int j = 1; j < m - 1; j++)
        {
            if((search(horDot, j, tableSize) == true) && (search(verDot, i, tableSize) == true))
            {
                table[i][j] = "\u254b";
            }

            else if (search(horDot, j, tableSize) == true)
            {
                table[i][j] = "\u2503";
            }

            else if (search(verDot, i, tableSize) == true)
            {
                table[i][j] = "\u2501";
            }
        }
    }

    //last line of the table
    table[n - 1][0] = "\u2517";
    for(int j = 1; j < m - 1; j++)
    {
        if (search(horDot, j, tableSize) == true)
        {
            table[n - 1][j] = "\u253b";
        }

        else
        {
            table[n - 1][j] = "\u2501";
        }
    }

    table[n - 1][m - 1] = "\u251b";
}



//search if the current point should be T shape or not
bool search(int dot[], int i, int size)
{
    for (int j = 0; j < size - 1; j++)
    {
        if (i == dot[j])
        {
            return true;
        }
    }
    return false;
}


//find the points that their shape should be like T
void find(int arr[], int size, int jump)
{
    arr[0] = jump;
    for (int i = 1; i < size - 1; i++)
    {
        arr[i] = arr[i - 1] + jump;
    }
}


//fill the table with space
void space(string table[][200], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            table[i][j] = " ";
        }
    }
}


void houseBolder(corners current)
{
    //bolding corners
    table[current.topLeft.x][current.topLeft.y] = "\u2554";
    table[current.topLeft.x][current.botRight.y] = "\u2557";
    table[current.botRight.x][current.topLeft.y] = "\u255A";
    table[current.botRight.x][current.botRight.y] = "\u255D";

    //bolding horizontal lines
    for (int hor = current.topLeft.y + 1; hor < current.botRight.y; hor++)
    {
        table[current.topLeft.x][hor] = "\u2550";
        table[current.botRight.x][hor] = "\u2550";
    }

    //bolding vertical lines
    for (int ver = current.topLeft.x + 1; ver < current.botRight.x; ver++)
    {
        table[ver][current.botRight.y] = "\u2551";
        table[ver][current.topLeft.y] = "\u2551";
    }
}


// put our table in it's Copy version to save it somewhere and use it in future
void SaveTable()
{
    for (int i; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            tableCopy[i][j] = table[i][j];
        }
    }
}


int digits(int number)
{
    int counter = 1;
    while (number > 0)
    {
        number /= 10;
        counter ++;
    }
    return counter;
}


// to unbold the selected parts
void normalizeHouse(corners current)
{
    //unbolding the corners
    table[current.topLeft.x][current.topLeft.y] = tableCopy[current.topLeft.x][current.topLeft.y];
    table[current.topLeft.x][current.botRight.y] = tableCopy[current.topLeft.x][current.botRight.y];
    table[current.botRight.x][current.topLeft.y] = tableCopy[current.botRight.x][current.topLeft.y];
    table[current.botRight.x][current.botRight.y] = tableCopy[current.botRight.x][current.botRight.y];


    //unbolding horizontal lines
    for (int hor = current.topLeft.y + 1; hor < current.botRight.y; hor++)
    {
        table[current.topLeft.x][hor] = "\u2501";
        table[current.botRight.x][hor] = "\u2501";
    }

    //unbolding vertical lines
    for (int ver = current.topLeft.x + 1; ver < current.botRight.x; ver++)
    {
        table[ver][current.topLeft.y] = "\u2503";
        table[ver][current.botRight.y] = "\u2503";
    }
}


// if we are out of the table it will put us back to the right place
int nextMove(corners &current, player &currentPlayer, int &savedCounter)
{
    char currentMove = getch();
    while (currentMove != '\r')
    {
        normalizeHouse(current);

        if (currentMove == 'w')
        {
            current.topLeft.x -= 2;
            current.botRight.x -= 2;
        }

        else if (currentMove == 's')
        {
            current.topLeft.x += 2;
            current.botRight.x += 2;
        }

        else if (currentMove == 'a')
        {
            current.topLeft.y -= 6;
            current.botRight.y -= 6;
        }

        else if (currentMove == 'd')
        {
            current.topLeft.y += 6;
            current.botRight.y += 6;
            
        }

        else if (currentMove == 'v')
        {
            saveGame(current, currentPlayer, savedCounter, currentGame);
        }

        else if (currentMove == 'e')
        {
            menu();
            return 0;
        }

        correctMoveTable(current, jumpTable, limitTable);

        houseBolder(current);
        system ("CLS");
        printTable(table, currentPlayer); 

        currentMove = getch();
    }

    //to check if the house is not already full
    if (table[current.topLeft.x + 1][current.topLeft.y + 3] != " ")
    {
        return nextMove(current, currentPlayer, savedCounter);
    }

    //to check if it can take any other house or not
    if (isAllowed(current, currentPlayer) == false)
    {
        //checking if our player can choose a different house or there is no more option for them
        if (endCheck(current, currentPlayer) == true)
        {
            if (currentPlayer.name == firstPlayer.name)
            {
                firstPlayer.capability = false;
            }

            else
            {
                secondPlayer.capability = false;
            }

            currentPlayer = changeTurn(currentPlayer);
            system ("CLS");
            printTable(table, currentPlayer); 
        }

        return nextMove(current, currentPlayer, savedCounter);
    }

    //reseting capability status if it has been falsed previously
    firstPlayer.capability = true;
    secondPlayer.capability = true;
    return 0;
}


// if next move is somewhere out of the table it will make us come back inside
void correctMoveTable(corners &boldPart, point paresh, corners limit)
{
    if (boldPart.topLeft.x == limit.botRight.x)
    {
        boldPart.topLeft.x = limit.topLeft.x;
        boldPart.botRight.x = paresh.x;
    }

    else if (boldPart.botRight.x == limit.topLeft.x)
    {
        boldPart.topLeft.x = limit.botRight.x - paresh.x;
        boldPart.botRight.x = limit.botRight.x;
    }

    else if (boldPart.botRight.y == limit.topLeft.y)
    {
        boldPart.topLeft.y = limit.botRight.y - paresh.y;
        boldPart.botRight.y = limit.botRight.y;
    }

    else if (boldPart.topLeft.y == limit.botRight.y)
    {
        boldPart.topLeft.y = limit.topLeft.y;
        boldPart.botRight.y = paresh.y;
    }
}


bool isAllowed(corners current, player &currentPlayer)
{
    if (horRight(current, currentPlayer) == -1 && horLeft(current, currentPlayer) == 1000 && 
        verTop(current, currentPlayer) == 1000 && verBottom(current, currentPlayer) == -1 &&
        mainDiagonalTop(current, currentPlayer) == 1000 && mainDiagonalBottom(current, currentPlayer) == -1 &&
        antiDiagonalTop(current, currentPlayer) == 1000 && antiDiagonalBottom(current, currentPlayer) == -1)
    {
        return false;
    } 
    return true; 
}


bool endCheck(corners current, player &currentPlayer)
{
    corners temp;
    for (int i = 0; i < n; i = i + 2)
    {
        for (int j = 0; j < m - 2; j = j + 6)
        {
            temp.topLeft.x = i;
            temp.topLeft.y = j;

            if (table[i + 1][j + 3] == " ");
            {
                if (isAllowed(temp, currentPlayer) == true)
                {
                    cout << "HINT : you can put your disc on row " << (i + 1) / 2 + 1 << " column " << (j + 3) / 6 + 1<< endl;
                    return false;
                }
            }
        }
    }
    return true;
}


int horRight(corners current, player &currentPlayer)
{
    for (int index = current.topLeft.y + 3 + 6; index < m - 3; index = index + 6)
    {
        if (table[current.topLeft.x + 1][index] == " ")
        {
            return -1;
        }

        if (table[current.topLeft.x + 1][index] == currentPlayer.symbol)
        {
            if (current.topLeft.y + 3 + 6 == index)
            {
                return -1;
            }
            return index;
        }
    }

    return -1;
}


int horLeft(corners current, player &currentPlayer)
{
    for (int index = current.topLeft.y + 3 - 6; index > 2; index = index - 6)
    {
        if (table[current.topLeft.x + 1][index] == " ")
        {
            return 1000;
        }
        
        if (table[current.topLeft.x + 1][index] == currentPlayer.symbol)
        {
            if (current.topLeft.y + 3 - 6 == index)
            {
                return 1000;
            }
            return index;
        }
    }
    return 1000;
}


int verTop(corners current, player &currentPlayer)
{
    for (int index = current.topLeft.x + 1 - 2; index > 0; index = index - 2)
    {
        if (table[index][current.topLeft.y + 3] == " ")
        {
            return 1000;
        }

        if (table[index][current.topLeft.y + 3] == currentPlayer.symbol)
        {
            if (current.topLeft.x + 1 - 2 == index)
            {
                return 1000;
            }
            return index;
        }
    }
    return 1000;
}


int verBottom(corners current, player &currentPlayer)
{
    for (int index = current.topLeft.x + 1 + 2; index < n; index = index + 2)
    {
        if (table[index][current.topLeft.y + 3] == " ")
        {
            return -1;
        }

        if (table[index][current.topLeft.y + 3] == currentPlayer.symbol)
        {
            if (current.topLeft.x + 1 + 2 == index)
            {
                return -1;
            }
            return index;
        }
    } 
    return -1; 
}


int mainDiagonalTop(corners current, player &currentPlayer)
{
    int indexj = current.topLeft.y + 3 - 6;
    for (int indexi = current.topLeft.x + 1 - 2; indexi > 0; indexi = indexi - 2)
    {
        if (table[indexi][indexj] == " ")
        {
            return 1000;
        }

        if (table[indexi][indexj] == currentPlayer.symbol)
        {
            if (current.topLeft.x + 1 - 2 == indexi)
            {
                return 1000;
            }
            return indexi;
        }
        indexj -= 6;
    }
    return 1000;
}


int mainDiagonalBottom(corners current, player &currentPlayer)
{
    int indexj = current.topLeft.y + 3 + 6;
    for (int indexi = current.topLeft.x + 1 + 2; indexi < n; indexi = indexi + 2)
    {
        if (table[indexi][indexj] == " ")
        {
            return -1;
        }

        if (table[indexi][indexj] == currentPlayer.symbol)
        {
            if (current.topLeft.x + 1 + 2 == indexi)
            {
                return -1;
            }
            return indexi;
        }
        indexj += 6;
    }
    return -1;
}


int antiDiagonalTop(corners current, player &currentPlayer)
{
    int indexj = current.topLeft.y + 3 + 6;
    for (int indexi = current.topLeft.x + 1 - 2; indexi > 0; indexi = indexi - 2)
    {
        if (table[indexi][indexj] == " ")
        {
            return 1000;
        }

        if (table[indexi][indexj] == currentPlayer.symbol)
        {
            if (current.topLeft.x + 1 - 2 == indexi)
            {
                return 1000;
            }
            return indexi;
        }
        indexj += 6;
    }
    return 1000;
}


int antiDiagonalBottom(corners current, player &currentPlayer)
{
    int indexj = current.topLeft.y + 3 - 6;
    for (int indexi = current.topLeft.x + 1 + 2; indexi < n; indexi = indexi + 2)
    {
        if (table[indexi][indexj] == " ")
        {
            return -1;
        }

        if (table[indexi][indexj] == currentPlayer.symbol)
        {
            if (current.topLeft.x + 1 + 2 == indexi)
            {
                return -1;
            }
            return indexi;
        }
        indexj -= 6;
    }
    return -1;
}


void filler(corners current, player &currentPlayer)
{
    //horizontal
    int temphorRight = horRight(current, currentPlayer);
    for (int k = current.topLeft.y + 3; k <= temphorRight; k = k + 6)
    {
        table[current.topLeft.x + 1][k] = currentPlayer.symbol;
    }

    int temphorLeft = horLeft(current, currentPlayer);
    for (int k = current.topLeft.y + 3 - 6; k >= temphorLeft; k = k - 6)
    {
        table[current.topLeft.x + 1][k] = currentPlayer.symbol;
    }

    //vertical
    int tempverTop = verTop(current, currentPlayer);
    for (int k = current.topLeft.x + 1 - 2; k >= tempverTop; k = k - 2)
    {
        table[k][current.topLeft.y + 3] = currentPlayer.symbol;
    }

    int tempverBottom = verBottom(current, currentPlayer);
    for (int k = current.topLeft.x + 1 + 2; k <= tempverBottom; k = k + 2)
    {
        table[k][current.topLeft.y + 3] = currentPlayer.symbol;
    }

    //main diagonal
    int tempmainDiagonalTop = mainDiagonalTop(current, currentPlayer);
    int indexj = current.topLeft.y + 3 - 6;
    for (int k = current.topLeft.x + 1 - 2; k >= tempmainDiagonalTop; k = k - 2)
    {
        table[k][indexj] = currentPlayer.symbol;
        indexj -= 6;
    }

    int tempmainDiagonalBottom = mainDiagonalBottom(current, currentPlayer);
    indexj = current.topLeft.y + 3 + 6;
    for (int k = current.topLeft.x + 1 + 2; k <= tempmainDiagonalBottom; k = k + 2)
    {
        table[k][indexj] = currentPlayer.symbol;
        indexj += 6;
    }

    //anti diagonal
    int tempAntiDiagonalTop = antiDiagonalTop(current, currentPlayer);
    indexj = current.topLeft.y + 3 + 6;
    for (int k = current.topLeft.x + 1 - 2; k >= tempAntiDiagonalTop; k = k - 2)
    {
        table[k][indexj] = currentPlayer.symbol;
        indexj += 6;
    }

    int tempAntiDiagonalBottom = antiDiagonalBottom(current, currentPlayer);
    indexj = current.topLeft.y + 3 - 6;
    for (int k = current.topLeft.x + 1 + 2; k <= tempAntiDiagonalBottom; k = k + 2)
    {
        table[k][indexj] = currentPlayer.symbol;
        indexj -= 6;
    }
}


void saveGame(corners current, player currentPlayer, int &savedCounter, gameData currentGame)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            currentGame.saved[i][j] = table[i][j];
        }
    }
    ofstream save("saved.txt", ios::out);
    save << currentGame.firstPlayer.name << " " << currentGame.firstPlayer.pieces << " " <<
    currentGame.firstPlayer.capability << "\n";
    save << currentGame.secondPlayer.name << " " << currentGame.secondPlayer.pieces << " " <<
    currentGame.secondPlayer.capability << "\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            save << currentGame.saved[i][j];
        }
    }
    save.close();
}


void loadGame(corners current, player currentPlayer, int &savedCounter, gameData currentGame)
{
    ifstream load("saved.txt", ios::in);

    load >> currentGame.firstPlayer.name >> currentGame.firstPlayer.pieces >>
    currentGame.firstPlayer.capability;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            load >> table[i][j];
        }
    }

    load.close();
    //bolding the first house
    houseBolder(current);
    system ("CLS");
    printTable(table, currentPlayer);  
    normalizeHouse(current);

    //moves
    while (firstPlayer.pieces + secondPlayer.pieces != tableSize * tableSize &&
          (firstPlayer.capability == true || secondPlayer.capability == true))
    {
        nextMove(current, currentPlayer, savedCounter);
        table[current.topLeft.x + 1][current.topLeft.y + 3] = currentPlayer.symbol;
        filler(current, currentPlayer);
        if (currentPlayer.symbol == secondPlayer.symbol)
        {
            secondPlayer.pieces ++;
        }
        else
        {
            firstPlayer.pieces ++;
        }
        currentPlayer = changeTurn(currentPlayer);

        system ("CLS");
        printTable(table, currentPlayer);
    }
    winnerFind(savedCounter);
}


player changeTurn(player &current)
{
    if (current.name == firstPlayer.name)
    {
        return secondPlayer;
    }
    return firstPlayer;
}


void printTable(string table[][200], player &currentPlayer)
{
    //top of the table
    for (int i = 0; i < 6; i++)
    {
        //first elemnt of lines
        cout << "\u2588";
        //lines
        if (i == 0 || i == 2)
        {
            for (int j = 0; j < 2 * m - 2; j++)
            {
                cout << "\u2580";
            }
        }
        if (i == 1)
        {
            for (int j = 0; j < (2 * m - 13) / 2 - 2 ; j++)
            {
                cout << "\u2580";
            }
            cout << " OTHELLO GAME ";
            for (int j = 0; j < (2 * m - 12) / 2 - 1; j++)
            {
                cout << "\u2580";
            }
        }
        if (i == 3)
        {
            cout << " first player's name:" << firstPlayer.name;
            for (int j = 0; j < (2 * m - 40 - firstPlayer.name.size() - digits(firstPlayer.pieces)); j++)
            {
                cout << " ";
            }
            cout << "symbol:O    moves:" << firstPlayer.pieces;
        }
        if (i == 4)
        {
            cout << " second player's name:" << secondPlayer.name;
            for (int j = 0; j < (2 * m - 41 - secondPlayer.name.size() - digits(secondPlayer.pieces)); j++)
            {
                cout << " ";
            }
            cout << "symbol:X    moves:" << secondPlayer.pieces;
        }
        if (i == 5)
        {
            for (int j = 0; j < (2 * m - currentPlayer.name.size() - 9) / 2 - 1; j++)
            {
                cout << "\u2580";
            }
            cout << " " << currentPlayer.name << "'s turn ";
            for (int j = 0; j < (2 * m - currentPlayer.name.size() - 8) / 2 - 1; j++)
            {
                cout << "\u2580";
            }
        }
        //last element of lines
        cout << "\u2588" << endl;
    }

    //the othello table
    for (int i = 0; i < n; i++)
    {
        //first element
        cout << "\u2588";

        //table structure
        for (int j = 0; j < m / 2 - 1; j++)
        {
            cout << " ";
        }
        for (int j = 0; j < m; j++)
        {
            cout << table[i][j];
        }
        for (int j = 0; j < m / 2; j++)
        {
            cout << " ";
        }
        //last element
        cout << "\u2588" << endl;
    }

    //bottom of the table
    for (int i = n + 13 - 7; i < n + 13; i++)       
    {
        //first element of lines
        if (i == n + 13 - 1)
        {
            cout << "\u2580";
        }
        else
        {
           cout << "\u2588"; 
        }
        //lines
        if (i == 13 + n - 1 || i == 13 + n - 7)
        {
            for (int j = 0; j < 2 * m - 2; j++)
            {
                cout << "\u2580";
            }
        }
        if (i == n + 13 - 6)
        {
            for (int i = 0; i < (2 * m - 13) / 2; i++)
            {
                cout << " ";
            }
            cout << "Instructions:";
            for (int i = 0; i < (2 * m - 13) / 2 - 1; i++)
            {
                cout << " ";
            }
        }
        if (i == n + 13 - 5)
        {
            cout << " Press these to move:";
            for (int i = 0; i < 2 * m - 38; i++)
            {
                cout << " ";
            }
            cout << "Select: Enter  ";
        }
        if (i == n + 13 - 4)
        {
            cout <<"        Up: W";
            for (int i = 0; i < 2 * m - 30; i++)
            {
                 cout << " ";
            }
            cout << "Down: S        ";
        }
        if (i == n + 13 - 3)
        {
            cout << "        Left: A";
            for (int i = 0; i < 2 * m - 32; i++)
            {
                cout << " ";
            }
            cout << "Right: D       ";
        }
        if (i == n + 13 - 2)
        {
            cout << "        Save: V";
            for (int i = 0; i < 2 * m - 32; i++)
            {
                cout << " ";
            }
            cout << "Exit: E        ";
        }
        //last element of lines
        if (i == n + 12)
        {
            cout << "\u2580" << endl;
        }
        else
        {
           cout << "\u2588" << endl; 
        }
    }
}


void checkName(string name)
{
    bool exists = false;
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i].name == name)
        {
            exists = true;
        }
    }

    if (!exists)
    {
        player newPlayer;
        newPlayer.name = name;
        players.insert(players.end(), newPlayer);
        update();
    }
}


void readData()
{
    ifstream reader("ranking.txt");

    while (!reader.eof())
    {
        player p;
        reader >> p.name >> p.wins >> p.loses >> p.ties;
        if (p.name != "")
        {
            players.insert(players.end(), p);
        }
    }

    reader.close();
}


void update()
{
    ofstream writer;
    writer.open("ranking.txt");

    for (int i = 0; i < players.size(); i++)
    {
        writer << players[i].info() << endl;
    }

    writer.close();
}


// take two player and compare them
bool compareTo(player p1, player p2)
{
    return (p1.getScore() > p2.getScore());
}


// sort players based on their scors
void sortData()
{
    sort(players.begin(), players.end(), compareTo);
}


void printRanking()
{
    sortData();
    system("cls");
    //system("Color 0A");

    cout << "           \a   " << "* RANKING *" << endl << "\u250c";
    
    for (int o = 0; ; o++)
    {
        if (o == 3 || o == 18 || o == 22 || o == 27 || o == 31)
        {
            cout << "\u252c";
        }
        
        else if (o == 37)
        {
            cout << "\u2510" << endl;
            break;
        }
        
        else
        {
            cout << "\u2500";
        }
    }
    
    cout << "\u2502   \u2502" << setw(9) << "Name";
    cout << "     \u2502win\u2502lose\u2502tie\u2502Score\u2502";
    cout << endl << "\u251c";
    
    for (int u = 0; ; u++)
    {
        if(u == 3 || u == 18 || u == 22 || u == 27 || u == 31)
        {
            cout << "\u253c";
        }
        
        else if (u == 37)
        {
            cout << "\u2524" << endl;
            break;
        }
        
        else
        {
            cout << "\u2500";
        }
    }

    for (int i = 0; i < players.size(); i++)
    {
        cout << "\u2502" << left << setw(3) << i + 1 << "\u2502" << setw(14) << players[i].name;
        cout << "\u2502" << setw(3) << players[i].wins << "\u2502" << setw(4);
        cout << players[i].loses << "\u2502" << setw(3) << players[i].ties;
        cout << "\u2502" << setw(5) << players[i].getScore() << "\u2502" << endl;
            
        if(i == players.size() - 1)
        {
            cout << "\u2514\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500";
            cout << "\u2500\u2500\u2500\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2534\u2500";
            cout << "\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2500\u2500\u2518" << endl;
        }
            
        else 
        {
            cout << "\u251c\u2500\u2500\u2500\u253c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500";
            cout << "\u2500\u2500\u2500\u2500\u2500\u253c\u2500\u2500\u2500\u253c\u2500\u2500\u2500\u2500";
            cout << "\u253c\u2500\u2500\u2500\u253c\u2500\u2500\u2500\u2500\u2500\u2524" << endl;
        }
    }
}
