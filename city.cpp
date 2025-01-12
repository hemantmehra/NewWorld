#include "city.h"

City::City(std::string name, int x, int y)
    : m_x(x), m_y(y), m_population(1), m_name(name), m_food(0), m_gold(0), m_production(0)
{
    tasks.push_back((CityTask) {CT_GRANARY, 3});
}

int City::population() { return m_population; }

// void City::update_food_storage()
// {
//     m_food_storage += m_food * m_population - m_population * 2;

//     if (m_food_storage > 5) {
//         m_population++;
//     }
// }

void City::next_turn(int m_map[50][50])
{
    for (int i=-1; i<=1; i++) {
        for (int j=-1; j<=1; j++) {
            switch(m_map[m_x + i][m_y + j]) {
                case T_SEA:
                    m_food++;
                    m_gold+=2;
                    break;
                case T_HILL:
                    m_gold++;
                    m_production++;
                    break;
                case T_GRASS:
                    m_food +=2;
                    m_production++;
                    break;
                case T_RIVER:
                    m_gold++;
                    m_food += 2;
                    m_production++;
                    break;
                default:
                    break;
            }
        }
    }
    // std::cout << "Food: " << m_food << '\n';
    // std::cout << "Gold: " << m_gold << '\n';
    // std::cout << "Production: " << m_production << '\n';
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
