#include "Plants.h"
#include <iostream>

Plant::Plant(Vector2 position, int foodValue)
    : Entity(position, 5.0f, GREEN, foodValue) 
{
    //std::cout << "Plant created." << std::endl;
}

Plant::~Plant()
{
    //std::cout << "Plant destroyed." << std::endl;
}


void Plant::Update(int screenWidth, int screenHeight)
{
}

void Plant::DrawEntity() 
{
    DrawCircleV(m_position, m_radius, m_color);
}
