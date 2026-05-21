#include "GameManager.h"
#include <iostream>
#include <cstdlib>

GameManager::GameManager() {
    currentDay = 1;
    hasFoughtToday = false;
    market.UpdateAssortment(1);
}

int GameManager::GetValidInput(int min, int max) {
    int choice;
    std::cin >> choice;
    while (std::cin.fail() || choice < min || choice > max) {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "Ошибка! Введите число от " << min << " до " << max << ": ";
        std::cin >> choice;
    }
    return choice;
}

void GameManager::StartGame() {
    std::cout << "Добро пожаловать в Симулятор Школы Гладиаторов!" << std::endl;
    std::cout << "У вас есть ровно " << MAX_DAYS << " дней, чтобы подготовить Чемпиона. "
                 "И доказать что вы самая лучшая школа" << std::endl;

    while (currentDay <= MAX_DAYS) { // Заменили 30
        ShowMainMenu();
    }
    std::cout << "Игра окончена!" << std::endl;
}

void GameManager::ShowMainMenu() {
    std::cout << "\n ДЕНЬ " << currentDay << " | ЗОЛОТО: " << school.getGold() << " | РЕПУТАЦИЯ: " << school.getReputation() << " ===" << std::endl;
    std::cout << "1. Управление школой (Тренировки и Улучшения)" << std::endl;
    std::cout << "2. Рынок (Магазин и Бойцы)" << std::endl;
    std::cout << "3. Арена (Бои)" << std::endl;
    std::cout << "4. Закончить день" << std::endl;
    std::cout << "0. Выйти из игры" << std::endl;
    std::cout << "Выберите действие: ";

    int choice = GetValidInput(0, 4);

    if (choice == 1) HandleSchoolMenu();
    else if (choice == 2) HandleMarketMenu();
    else if (choice == 3) HandleArenaMenu();
    else if (choice == 4) EndDay();
    else if (choice == 0) ExitGame();
    else std::cout << "Неверный выбор." << std::endl;
}

void GameManager::HandleMarketMenu() {
    std::cout << "\nВАШИ ДЕНЬГИ: " << school.getGold() << std::endl;
    market.ShowAssortment();

    std::cout << "\nЧто хотите купить?\n1. Предмет\n2. Бойца\n0. Назад\nВыбор: ";
    int marketChoice = GetValidInput(0, 2);

    if (marketChoice == 1) {
        std::cout << "Введите номер предмета или 0 для отмены: ";
        int itemIndex = GetValidInput(0, 3);
        if (itemIndex > 0) {
            TransactionResult res = market.BuyItem(itemIndex - 1, school);

            if (res == TransactionResult::SUCCESS) {
                std::cout << "Предмет успешно куплен и добавлен в инвентарь школы!" << std::endl;
            } else if (res == TransactionResult::INSUFFICIENT_FUNDS) {
                std::cout << "Недостаточно золота!" << std::endl;
            } else {
                std::cout << "Неверный номер предмета!" << std::endl;
            }
        }
    }
    else if (marketChoice == 2) {
        std::cout << "Введите номер бойца или 0 для отмены: ";
        int slaveIndex = GetValidInput(0, 3);
        if (slaveIndex > 0) {
            TransactionResult res = market.BuyGladiator(slaveIndex - 1, school);

            if (res == TransactionResult::SUCCESS) {
                std::cout << "Гладиатор куплен и отправлен в Школу!" << std::endl;
            } else if (res == TransactionResult::INSUFFICIENT_FUNDS) {
                std::cout << "Недостаточно золота!" << std::endl;
            } else if (res == TransactionResult::LUDUS_FULL) {
                std::cout << "Школа переполнена! Максимум " << Ludus::MAX_GLADIATORS << " бойцов." << std::endl;
            } else {
                std::cout << "Неверный номер бойца!" << std::endl;
            }
        }
    }
}

void GameManager::HandleArenaMenu() {
    if (school.GetGladiatorCount() == 0) {
        std::cout << "\nУ вас нет гладиаторов! Сначала купите бойца на Рынке." << std::endl;
        return;
    }

    std::cout << "\n ВЫБОР БОЙЦА ДЛЯ АРЕНЫ ---" << std::endl;
    school.ShowRoster();
    std::cout << "Введите номер бойца (или 0 для отмены): ";
    int fighterIndex = GetValidInput(0, school.GetGladiatorCount());

    if (fighterIndex == 0) return;

    Gladiator* fighter = school.GetGladiator(fighterIndex - 1);
    if (fighter == nullptr) {
        std::cout << "Неверный номер бойца!" << std::endl;
        return;
    }

    bool isVictorious = false;

    if (currentDay == MAX_DAYS) {
        std::cout << "\n!!! ГРАНД-ФИНАЛ !!! ИМПЕРАТОР СМОТРИТ НА ВАС !!!" << std::endl;
        std::cout << "Ваш противник - Чемпион Рима!" << std::endl;

        auto boss = std::make_unique<Boss>("ЧЕМПИОН РИМА", 300, 35, 0);
        isVictorious = arena.FightBoss(fighter, boss.get());

        if (isVictorious) {
            std::cout << "\nПОБЕДА! ВЫ ПРОШЛИ ИГРУ! ВАША ШКОЛА ВЕЛИЧАЙШАЯ В РИМЕ!" << std::endl;
            exit(0);
        }
    }
    else {
        isVictorious = arena.StartTournament(fighter, currentDay);
    }

    if (isVictorious) {
        int goldReward = 100 + (currentDay * 20);
        std::cout << "Школа получает " << goldReward << " золота и 10 репутации!" << std::endl;
        school.AddGold(goldReward);
        school.AddReputation(10);
    }

    school.RemoveDeadGladiators();
    hasFoughtToday = true;
}

void GameManager::HandleSchoolMenu() {
    std::cout << "\n ШКОЛА ГЛАДИАТОРОВ " << std::endl;
    if (school.GetGladiatorCount() == 0) {
        std::cout << "\nУ вас нет гладиаторов! Сначала купите бойца на Рынке." << std::endl;
        return;
    }

    school.ShowRoster();
    std::cout << "\nДействия в школе:" << std::endl;
    std::cout << "1. Тренировать бойца" << std::endl;
    std::cout << "2. Улучшить Тренировочный Манекен (" << school.GetDummyUpgradeCost() << " золота)" << std::endl;
    std::cout << "3. Улучшить Лазарет (" << school.GetInfirmaryUpgradeCost() << " золота)" << std::endl;
    std::cout << "4. Использовать/Надеть предмет со склада" << std::endl;
    std::cout << "0. Назад в Главное Меню" << std::endl;
    std::cout << "Выбор: ";

    int schoolChoice = GetValidInput(0, 4);
    if (schoolChoice == 1) {
        std::cout << "Введите номер бойца для тренировки: ";
        int trainIndex = GetValidInput(0, school.GetGladiatorCount());
        TrainingResult res = school.TrainGladiator(trainIndex - 1);

        if (res == TrainingResult::SUCCESS) {
            std::cout << "Гладиатор был успешно усилен!" << std::endl;
        } else if (res == TrainingResult::ALREADY_TRAINED) {
            std::cout << "Этот боец слишком устал сегодня." << std::endl;
        } else {
            std::cout << "Неверный номер гладиатора!" << std::endl;
        }
    } else if (schoolChoice == 2) {
        if (school.UpgradeDummy()) std::cout << "Манекен успешно улучшен!" << std::endl;
        else std::cout << "Не хватает золота для улучшения!" << std::endl;
    } else if (schoolChoice == 3) {
        if (school.UpgradeInfirmary()) std::cout << "Лазарет успешно улучшен!" << std::endl;
        else std::cout << "Не хватает золота для улучшения!" << std::endl;
    } else if (schoolChoice == 4) {
        school.EquipItemMenu();
    }
}

void GameManager::RandomEvent() {
    int eventChance = rand() % 100;
    if (eventChance < 15) {
        std::cout << "\n[СЛУЧАЙНОЕ СОБЫТИЕ] Толпа восхищена вашей школой! Местный патриций пожертвовал вам 50 золота!" << std::endl;
        school.AddGold(50);
    } else if (eventChance > 85) {
        if (school.getGold() >= 20) {
            std::cout << "\n[СЛУЧАЙНОЕ СОБЫТИЕ] Ночью крысы испортили часть припасов... Вы потеряли 20 золота на восстановление." << std::endl;
            school.SpendGold(20);
        }
    }
}

void GameManager::EndDay() {
    if (hasFoughtToday == false) {
        std::cout << "\nВы не можете завершить день! Отправьте кого-нибудь на Арену проливать кровь!" << std::endl;
        return;
    }

    std::cout << "\n ДЕНЬ " << currentDay << " ЗАВЕРШЕН " << std::endl;
    RandomEvent();
    currentDay++;

    hasFoughtToday = false;
    school.NightHeal();
    market.UpdateAssortment(currentDay);
}

void GameManager::ExitGame() {
    std::cout << "Вы покинули игру. До встречи на Арене!" << std::endl;
    std::exit(0);
}