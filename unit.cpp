#include "unit.h"

Unit::Unit(UnitType type, int x, int y)
    : m_type(type), m_x(x), m_y(y), m_alive(true) {}

UnitType Unit::type()
{
    return m_type;
}

bool Unit::is_alive() { return m_alive; }

void Unit::consume() { m_alive = false; }
