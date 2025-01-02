#include "city.h"

City::City(std::string name, int x, int y)
    : m_x(x), m_y(y), m_population(1), m_name(name)
{
    tasks.push_back(CT_SETTLER);
    tasks.push_back(CT_GRANARY);
}

int City::population() { return m_population; }

std::string CityTask_to_Str(CityTask task)
{
    switch (task)
    {
        case CT_SETTLER:
            return "Settler";
        case CT_GRANARY:
            return "Granary";
        default:
            return "ERROR";
    }
}

std::string City::name()
{
    return m_name;
}
