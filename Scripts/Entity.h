#pragma once
#include "raylib/raylib.h"  

class Entity
{
protected:
    static int s_idCounter;

protected:
    int m_id;
    Vector2 m_position;
    Color m_color;
    int m_foodValue;
    float m_radius;
    const float m_zoneRadius = 70.0f;
    

public:
    Entity(Vector2 position, float radius, Color color, int foodValue);
    virtual ~Entity();

    virtual void Update(int screenWidth, int screenHeight) = 0;
    virtual void DrawEntity() = 0;

    int GetID() const;
    float GetRadius() const;
    int GetFoodValue() const;

    Vector2 GetPosition() const;
    void SetPosition(const Vector2& position);

    

};
