#include "Entity.h"
#include <iostream>

int Entity::s_idCounter = 0;

Entity::Entity(Vector2 position, float radius, Color color, int foodValue)
{
	m_id = s_idCounter++;
	m_position = position;
	m_radius = radius;
	m_color = color;
	m_foodValue = foodValue;
	std::cout << "Entity created. ID: " << m_id << std::endl;

}

Entity::~Entity()
{
	std::cout << "Entity Destroyed" << std::endl;
}

int Entity::GetID() const 
{
    return m_id;
}

Vector2 Entity::GetPosition() const
{
    return m_position;
}

float Entity::GetRadius() const
{
    return m_radius;
}

int Entity::GetFoodValue() const 
{
    return m_foodValue;
}

void Entity::SetPosition(const Vector2& position) 
{
    m_position = position;
}
