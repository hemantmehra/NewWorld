#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "tile.h"

enum TaskKind {
    CT_SETTLER,
    CT_GRANARY
};

struct CityTask {
    TaskKind kind;
    int production;
};

std::string CityTask_to_Str(CityTask task);

enum SettlementKind {
    S_Village,
    S_Town,
    S_City
};

class Settlement
{
public:
    Settlement(SettlementKind kind, std::string name, int x, int y);
    int population();
    // void update_food_storage();
    void next_turn(int m_map[50][50]);
    void inc_population();
    void dec_population();
    std::string name();
    SettlementKind kind();

    int m_x;
    int m_y;
    std::vector<CityTask> tasks;

private:
    SettlementKind m_kind;
    int m_population;
    CityTask m_task;
    std::string m_name;
    int m_food;
    int m_gold;
    int m_production;
    // int m_food_storage;
};
