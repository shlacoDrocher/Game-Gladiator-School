
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
    public:
    GameManager();
    void StartGame();
    static int GetValidInput(int min, int max);
};


#endif //CODE_GAMEMANAGER_H