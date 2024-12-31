#include "city.h"

City::City(int x, int y)
    : m_x(x), m_y(y), m_population(1) {}

int City::population() { return m_population; }
