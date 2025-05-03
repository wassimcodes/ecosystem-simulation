#pragma once
#include "Entity.h"

class Plant : public Entity {
public:
    Plant(Vector2 position, int foodValue);
    virtual ~Plant();

    void Update(int screenWidth, int screenHeight) override;
    void DrawEntity() override;
};
