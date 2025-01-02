#pragma once

#include <string>
#include <vector>

enum CityTask {
    CT_SETTLER,
    CT_GRANARY
};

std::string CityTask_to_Str(CityTask task);

class City
{
public:
    City(std::string name, int x, int y);
    int population();
    std::string name();

    int m_x;
    int m_y;
    std::vector<CityTask> tasks;

private:
    int m_population;
    CityTask m_task;
    std::string m_name;
};
