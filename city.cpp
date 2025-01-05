#include "city.h"

City::City(std::string name, int x, int y)
    : m_x(x), m_y(y), m_population(1), m_name(name), m_food(3), m_food_storage(2)
{
    tasks.push_back((CityTask) {CT_GRANARY, 3});
}

int City::population() { return m_population; }

void City::update_food_storage()
{
    m_food_storage += m_food * m_population - m_population * 2;

    if (m_food_storage > 5) {
        m_population++;
    }
}

void City::inc_population()
{
    m_population++;
}

void City::dec_population()
{
    m_population--;
}

std::string CityTask_to_Str(CityTask task)
{
    switch (task.kind)
    {
        case CT_SETTLER:
            return "Settler <4>";
        case CT_GRANARY:
            return "Granary <3>";
        default:
            return "ERROR";
    }
}

std::string City::name()
{
    return m_name;
}
