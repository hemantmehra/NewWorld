#pragma once

class City
{
public:
    City(int x, int y);
    int m_x;
    int m_y;
    int population();

private:
    int m_population;
};
