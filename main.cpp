#include <iostream>
#include <Windows.h>
#include <ctime>
#include "GameManager.h"

using namespace std;

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    srand(time(0));

    GameManager game;
    game.StartGame();

    return 0;
}