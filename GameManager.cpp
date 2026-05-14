//
// Created by Sigma on 12.05.2026.
//

#include "GameManager.h"
#include <iostream>

GameManager::GameManager() {
    currentDay = 1;
    hasFoughtToday = false;
    market.UpdateAssortment();
}

void GameManager::StartGame() {
    std::cout << "Добро пожаловать в Симулятор Школы Гладиаторов!" << std::endl;
    std::cout << "У вас есть ровно 30 дней, чтобы подготовить Чемпиона. "
                 "И доказать что вы самая лучшая школа" << std::endl;
    while (currentDay <= 30) {
        ShowMainMenu();
    }
    std::cout << "Игра окончена!" << std::endl;
}

void GameManager::ShowMainMenu() {
    std::cout << "\n ДЕНЬ " << currentDay << " | ЗОЛОТО: " << school.getGold() << " | РЕПУТАЦИЯ: " << school.getReputation() << " ===" << std::endl;
    std::cout << "1. Управление школой (Тренировки и Улучшения)" << std::endl;
    std::cout << "2. Рынок (Магазин и Рабы)" << std::endl;
    std::cout << "3. Арена (Бои)" << std::endl;
    std::cout << "4. Закончить день" << std::endl;
    std::cout << "Выберите действие: ";

    int choice; std::cin >> choice;

    if (choice == 1) HandleSchoolMenu();
    else if (choice == 2) HandleMarketMenu();
    else if (choice == 3) HandleArenaMenu();
    else if (choice == 4) EndDay();
    else std::cout << "Неверный выбор." << std::endl;
}

void GameManager::HandleMarketMenu() {
    std::cout << "\nВАШИ ДЕНЬГИ: " << school.getGold() << std::endl;
    market.ShowAssortment();

    std::cout << "\nЧто хотите купить?\n1. Предмет\n2. Раба\n0. Назад\nВыбор: ";
    int marketChoice;
    std::cin >> marketChoice;

    if (marketChoice == 1) {
        std::cout << "Введите номер предмета (1-3) или 0 для отмены: ";
        int itemIndex; std::cin >> itemIndex;
        if (itemIndex > 0) market.BuyItem(itemIndex - 1, school);
    }
    else if (marketChoice == 2) {
        std::cout << "Введите номер раба (1-2) или 0 для отмены: ";
        int slaveIndex; std::cin >> slaveIndex;
        if (slaveIndex > 0) market.BuyGladiator(slaveIndex - 1, school);
    }
}

void GameManager::HandleArenaMenu() {
    if (school.GetGladiatorCount() == 0) {
        std::cout << "\nУ вас нет гладиаторов! Сначала купите раба на Рынке." << std::endl;
        return;
    }

    std::cout << "\n ВЫБОР БОЙЦА ДЛЯ АРЕНЫ ---" << std::endl;
    school.ShowRoster();
    std::cout << "Введите номер бойца (или 0 для отмены): ";
    int fighterIndex; std::cin >> fighterIndex;

    if (fighterIndex == 0) return;

    Gladiator* fighter = school.GetGladiator(fighterIndex - 1);
    if (fighter == nullptr) {
        std::cout << "Неверный номер бойца!" << std::endl;
        return;
    }

    bool isVictorious = false;

    if (currentDay == 30) {
        std::cout << "\n!!! ГРАНД-ФИНАЛ !!! ИМПЕРАТОР СМОТРИТ НА ВАС !!!" << std::endl;
        std::cout << "Ваш противник - Чемпион Рима!" << std::endl;

        auto boss = std::make_unique<Gladiator>("ЧЕМПИОН РИМА", 300, 35, 0);
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
        std::cout << "\nУ вас нет гладиаторов! Сначала купите раба на Рынке." << std::endl;
        return;
    }

    school.ShowRoster();
    std::cout << "\nДействия в школе:" << std::endl;
    std::cout << "1. Тренировать бойца" << std::endl;
    std::cout << "2. Улучшить Тренировочный Манекен (50 золота)" << std::endl;
    std::cout << "3. Улучшить Лазарет (50 золота)" << std::endl;
    std::cout << "4. Использовать/Надеть предмет со склада" << std::endl;
    std::cout << "0. Назад в Главное Меню" << std::endl;
    std::cout << "Выбор: ";

    int schoolChoice; std::cin >> schoolChoice;
    if (schoolChoice == 1) {
        std::cout << "Введите номер бойца для тренировки: ";
        int trainIndex; std::cin >> trainIndex;
        school.TrainGladiator(trainIndex - 1);
    } else if (schoolChoice == 2) {
        school.UpgradeDummy();
    } else if (schoolChoice == 3) {
        school.UpgradeInfirmary();
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
    market.UpdateAssortment();
}