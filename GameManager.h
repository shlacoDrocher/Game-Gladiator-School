//
// Created by Sigma on 12.05.2026.
//

#ifndef CODE_GAMEMANAGER_H
#define CODE_GAMEMANAGER_H
#include "Ludus.h"
#include "Market.h"
#include "Arena.h"

class GameManager {
    Ludus school;
    Market market;
    Arena arena;

    int currentDay;
    bool hasFoughtToday;

    void ShowMainMenu();
    void HandleSchoolMenu();
    void EndDay();
    public:
    GameManager();
    void StartGame();
};


#endif //CODE_GAMEMANAGER_H