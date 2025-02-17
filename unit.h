#pragma once

enum UnitType {
    U_Settler,
    U_Warrior
};

class Unit {
public:
    Unit(UnitType, int x, int y);
    UnitType type();
    bool is_alive();
    void consume();

    bool is_settler();
    int m_x;
    int m_y;

private:
    UnitType m_type;
    bool m_alive;
};
