#pragma once
#include "Entity.h"
#include "Plants.h"
#include "Animals.h"
#include <vector>
#include "WindowDimensions.h"

class EntityManager {
private:
    static std::vector<Entity*> s_entities;
	static std::vector<Entity*> s_entitiesToRemove;

public:
    EntityManager();
    virtual ~EntityManager();
    
    static void AddEntity(Entity* entity);
    static void RemoveEntity(Entity* entity);

    static const std::vector<Entity*>& GetEntities();

    static void UpdateEntities(int screenWidth, int screenHeight);
    static void DrawEntities();
    static void CheckAllEntities(const WindowDimensions& windowDimensions);

	static bool IsEntityOverlapping(Entity* entity);
   
    void SpawnFirstEntities(int screenWidth, int screenHeight);
};
