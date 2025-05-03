#include "Animals.h"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "EntityManager.h"
#include "Plants.h"
#include <iostream>

Animal::Animal(Vector2 position, float maxEnergy, Color color)
    :Entity(position, 10.0f, color, 0)
{
	m_maxEnergy = maxEnergy;
	m_energy = maxEnergy;
	m_state = LookingForFood;
}

Animal::~Animal() 
{
}


void Animal::Update(int screenWidth, int screenHeight)
{
    if (m_state == Sleeping) 
    {
        RecoverEnergy();
        if (m_energy >= m_maxEnergy / 2) 
        {
            m_state = LookingForFood;
        }
    }
    else
    {
        m_energy -= m_energyDecreaseRate;

        if (m_energy <= 0) {
            m_state = Sleeping;
            m_energy = 0;
        }
    }
}

void Animal::DrawEntity() 
{
    DrawCircleV(m_position, m_radius, m_color);
}

void Animal::Eat(Entity* food) 
{
        m_energy += food->GetFoodValue();
        if (m_energy > m_maxEnergy) {
            m_energy = m_maxEnergy;
        }
    
}

AnimalState Animal::GetState()
{
    return m_state;
}

void Animal::SetSpeed(float speed)
{
	m_speed = speed;
}

void Animal::RecoverEnergy()
{
    if (m_energy < m_maxEnergy) {
        m_energy += m_energyDecreaseRate * 3;
    }
    if (m_energy > m_maxEnergy) {
        m_energy = m_maxEnergy;
    }
}






Rabbit::Rabbit(Vector2 pos)
    : Animal(pos, 100.0f, WHITE) 
{
    m_nearestPlant = nullptr;
	SetSpeed(.5f);
	std::cout << "Rabbit spawned at: " << pos.x << ", " << pos.y << std::endl;
}

Rabbit::~Rabbit() 
{
	std::cout << "Rabbit destroyed" << std::endl;
}

void Rabbit::Update(int screenWidth, int screenHeight) 
{
    Animal::Update(screenWidth, screenHeight);

    std::vector<Entity*> entities = EntityManager::GetEntities();
    for (int i = 0; i < entities.size(); ++i)
    {
        Fox* fox = dynamic_cast<Fox*>(entities[i]);
        if (fox)
        {
            m_PredatorDistance = sqrt(pow((m_position.x - fox->GetPosition().x),2) + pow((m_position.x - fox->GetPosition().x),2));
            if (m_PredatorDistance < m_zoneRadius)
            {
                m_state = Escaping;
                EscapeFromPredator(screenWidth, screenHeight);
            }
            else
            {
                m_state = LookingForFood;
                SearchForFood(screenWidth, screenHeight);
            }
        }
    }
}

void Rabbit::DrawEntity() 
{
    Animal::DrawEntity();
}

void Rabbit::SearchForFood(int screenWidth, int screenHeight)
{
    float closestDistance = 10000;

    std::vector<Entity*> entities = EntityManager::GetEntities();
    for (int i = 0; i < entities.size(); ++i)
    {
        Plant* plant = dynamic_cast<Plant*>(entities[i]);
        if (plant)
        {
            m_plantDistance = sqrt(pow((m_position.x - plant->GetPosition().x),2) + pow((m_position.y - plant->GetPosition().y), 2));

            if (m_plantDistance < closestDistance)
            {
                closestDistance = m_plantDistance;
                m_nearestPlant = plant;
            }
        }
    }

    if (m_nearestPlant)
    {
        float distanceX = m_nearestPlant->GetPosition().x - m_position.x;
        float distanceY = m_nearestPlant->GetPosition().y - m_position.y;

        float length = sqrt(pow(distanceX, 2) + pow(distanceY, 2));

        m_position.x += (distanceX / length) * m_speed;
        m_position.y += (distanceY / length) * m_speed;

        float finalDistance = sqrt(pow((m_position.y - m_nearestPlant->GetPosition().y), 2) + pow((m_position.x - m_nearestPlant->GetPosition().x), 2));

        if (finalDistance < m_radius + m_nearestPlant->GetRadius())
        {
            Eat(m_nearestPlant);
            EntityManager::RemoveEntity(m_nearestPlant);
        }
    }


}


void Rabbit::EscapeFromPredator(int screenWidth, int screenHeight)
{
    std::vector<Entity*> entities = EntityManager::GetEntities();
    for (int i = 0; i < entities.size(); ++i)
    {
        Fox* fox = dynamic_cast<Fox*>(entities[i]);
        if (fox) 
        {
            float distanceX = m_position.x - fox->GetPosition().x;
            float distanceY = m_position.y - fox->GetPosition().y;

            float length = sqrt(pow(distanceX, 2) + pow(distanceY, 2));

            if (length < m_zoneRadius)
            {
                float directionX = distanceX / length;
                float directionY = distanceY / length;

                m_position.x += directionX * m_speed;
                m_position.y += directionY * m_speed;

                // Screen limits
                if (m_position.x < 0)
                {
                    m_position.x = 0;
                }
                    
                if (m_position.x > screenWidth)
                {
                    m_position.x = screenWidth;
                }
                if (m_position.y < 0)
                {
                    m_position.y = 0;
                }
                if (m_position.y > screenHeight)
                {
                    m_position.y = screenHeight;
                }
            }
        }
    }
}






Fox::Fox(Vector2 pos)
    : Animal(pos, 150.0f, RED) 
{
	m_nearestRabbit = nullptr;
    SetSpeed(1.0f);
}

Fox::~Fox() 
{
	std::cout << "Fox destroyed" << std::endl;
}

void Fox::Update(int screenWidth, int screenHeight)
{
    Animal::Update(screenWidth, screenHeight);

    if (m_state == LookingForFood) 
    {
        Hunt(screenWidth, screenHeight);
    }
}

void Fox::Hunt(int screenWidth, int screenHeight) 
{
    float closestDistance = 10000.0f;

    std::vector<Entity*> entities = EntityManager::GetEntities();
    for (int i = 0; i < entities.size(); ++i) 
    {
        Rabbit* rabbit = dynamic_cast<Rabbit*>(entities[i]);
        if (rabbit && rabbit->GetState() != Sleeping) 
        {
            float length = sqrt(pow((m_position.x - rabbit->GetPosition().x), 2) + pow((m_position.y - rabbit->GetPosition().y), 2));

            if (length < closestDistance)
            {
                closestDistance = length;
                m_nearestRabbit = rabbit;
            }
        }
    }

    if (m_nearestRabbit) 
    {
        float distanceX = m_nearestRabbit->GetPosition().x - m_position.x;
        float distanceY = m_nearestRabbit->GetPosition().y - m_position.y;

        float length = sqrt(pow(distanceX, 2) + pow(distanceY, 2));

        m_position.x += (distanceX / length) * m_speed;
        m_position.y += (distanceY / length) * m_speed;

        float finalDistance = sqrt(pow(m_position.x - m_nearestRabbit->GetPosition().x, 2) + pow(m_position.y - m_nearestRabbit->GetPosition().y, 2));

        if (finalDistance < m_radius + m_nearestRabbit->GetRadius()) 
        {
            Eat(m_nearestRabbit);
            EntityManager::RemoveEntity(m_nearestRabbit);
        }
    }
}


void Fox::DrawEntity() 
{
    Animal::DrawEntity();
}
