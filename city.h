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

class City
{
public:
    City(std::string name, int x, int y);
    int population();
    // void update_food_storage();
    void next_turn(int m_map[50][50]);
    void inc_population();
    void dec_population();
    std::string name();

    int m_x;
    int m_y;
    std::vector<CityTask> tasks;

private:
    int m_population;
    CityTask m_task;
    std::string m_name;
    int m_food;
    int m_gold;
    int m_production;
    // int m_food_storage;
};
