#pragma once
#include "Entity.h"
#include "raylib/raylib.h"

enum AnimalState
{
    Sleeping,
    LookingForFood,
	Escaping,
};


class Animal : public Entity 
{
public:
    Animal(Vector2 position, float maxEnergy, Color color);
    virtual ~Animal();

    void Update(int screenWidth, int screenHeight) override;
    void DrawEntity() override;
    void Eat(Entity* food);
    AnimalState GetState();
    void SetSpeed(float speed);

protected:
    float m_energy;
    float m_maxEnergy;
    float m_speed;
    AnimalState m_state;

private:
	const float m_energyDecreaseRate = 0.3f;
    void RecoverEnergy();

};





class Rabbit : public Animal {
public:
    Rabbit(Vector2 position);
    ~Rabbit();

    void Update(int screenWidth, int screenHeight) override;
    void DrawEntity() override;

    void EscapeFromPredator(int screenWidth, int screenHeight);
    void SearchForFood(int screenWidth, int screenHeight); 

private:
    float m_PredatorDistance;
    float m_plantDistance;
    Entity* m_nearestPlant;
};





class Fox : public Animal {
public:
    Fox(Vector2 position);
    ~Fox();

    void Update(int screenWidth, int screenHeight) override;
    void DrawEntity() override;

    void Hunt(int screenWidth, int screenHeight);

private:
	Entity* m_nearestRabbit;
};
