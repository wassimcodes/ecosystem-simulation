#include "EntityManager.h"
#include "raylib/raylib.h"
#include "Plants.h"


std::vector<Entity*> EntityManager::s_entities;
std::vector<Entity*> EntityManager::s_entitiesToRemove;


EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
    for (int i = 0; i < s_entities.size(); ++i)
    {
        delete s_entities[i];
    }
    s_entities.clear();

    for (int i = 0; i < s_entitiesToRemove.size(); ++i) 
    {
        delete s_entitiesToRemove[i];
    }
    s_entitiesToRemove.clear();
}



void EntityManager::AddEntity(Entity* entity) 
{
     s_entities.push_back(entity);
}

void EntityManager::RemoveEntity(Entity* entity)
{
    for (int i = 0; i < s_entities.size(); ++i) 
    {
        if (s_entities[i] == entity)
        {
            for (int j = i; j < s_entities.size() - 1; ++j) 
            {
                s_entities[j] = s_entities[j + 1];
            }
            s_entities.pop_back();
            s_entitiesToRemove.push_back(entity);
            break;
        }
    }
}


const std::vector<Entity*>& EntityManager::GetEntities() 
{
    return s_entities;
}

bool EntityManager::IsEntityOverlapping(Entity* newEntity)
{
    for (int i = 0; i < s_entities.size(); ++i)
    {
        Entity* entity = s_entities[i];

        float squaredDistance = (pow((newEntity->GetPosition().x - entity->GetPosition().x),2) + (pow((newEntity->GetPosition().y - entity->GetPosition().y), 2)));
        float squaredRadiusSum = pow(newEntity->GetRadius() + entity->GetRadius(), 2);

        if (squaredDistance < squaredRadiusSum)
        {
                return true;
        }

     }
    
    return false;
}

void EntityManager::SpawnFirstEntities(int screenWidth, int screenHeight)
{
   
   for (int i = 0; i < 30; ++i)
   {
       Entity* newPlant = new Plant({ (float)(rand() % screenWidth), (float)(rand() % screenHeight) }, 10);
       AddEntity(newPlant);
   }

   for (int i = 0; i < 5; ++i)
   {
       Entity* newRabbit = new Rabbit({ (float)(rand() % screenWidth), (float)(rand() % screenHeight) });
       AddEntity(newRabbit);
   }

   for (int i = 0; i < 3; ++i)
   {
       Entity* newFox = new Fox({ (float)(rand() % screenWidth), (float)(rand() % screenHeight) });
       AddEntity(newFox);
   }
}



void EntityManager::UpdateEntities(int screenWidth, int screenHeight)
{
    std::vector<Entity*> entitiesToUpdate = s_entities;

    for (Entity* entity : entitiesToUpdate) 
    {
       entity->Update(screenWidth, screenHeight);
    }
}

void EntityManager::DrawEntities() 
{
    std::vector<Entity*> entitiesToDraw = s_entities;
    for (Entity* entity : entitiesToDraw)
    {
      entity->DrawEntity();
    }
}

void EntityManager::CheckAllEntities(const WindowDimensions& windowDimensions)
{
    int plantCount = 0;
    int rabbitCount = 0;

    for (int i = 0; i < s_entities.size(); ++i)
    {
        Plant* plant = dynamic_cast<Plant*>(s_entities[i]);
        Rabbit* rabbit = dynamic_cast<Rabbit*>(s_entities[i]);

        if (plant)
        {
            ++plantCount;
        }
        else if (rabbit)
        {
            ++rabbitCount;
        }
    }


    if (plantCount < 10) 
    {
        for (int i = 0; i < 20; ++i) 
        {
            Entity* newPlant = new Plant({ (float)(rand() % (windowDimensions.width)), (float)(rand() % (windowDimensions.height)) }, 10);
            if (!IsEntityOverlapping(newPlant)) 
            {
                AddEntity(newPlant);
            }
        }
    }

    if (rabbitCount < 3) 
    {
        for (int i = 0; i < 3; ++i) 
        {
            Entity* newRabbit = new Rabbit({ (float)(rand() % (windowDimensions.width)), (float)(rand() % (windowDimensions.height)) });
            if (!IsEntityOverlapping(newRabbit))
            {
                AddEntity(newRabbit);
            }
        }
    }
}

