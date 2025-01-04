#pragma once

#include <string>
#include <vector>

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
};
