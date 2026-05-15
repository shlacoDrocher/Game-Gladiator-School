//
// Created by Sigma on 12.05.2026.
//

#ifndef CODE_GAMEMANAGER_H
#define CODE_GAMEMANAGER_H
#include "../Systems/Ludus.h"
#include "../Systems/Market.h"
#include "../Combat/Arena.h"

class GameManager {
    Ludus school;
    Market market;
    Arena arena;

    int currentDay;
    bool hasFoughtToday;

    void ShowMainMenu();
    void HandleMarketMenu();
    void HandleArenaMenu();
    void HandleSchoolMenu();
    void RandomEvent();
    void EndDay();
    static void ExitGame();
    static int GetValidInput(int min, int max);
    public:
    GameManager();
    void StartGame();
};


#endif //CODE_GAMEMANAGER_H