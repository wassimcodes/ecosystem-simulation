#include "EntityManager.h"
#include "raylib/raylib.h"
#include "Plants.h"
#include "WindowDimensions.h"



int main() {
    const int screenWidth = 720;
    const int screenHeight = 480;
    InitWindow(screenWidth, screenHeight, "Ecosystem Simulation");
    SetTargetFPS(60);

    EntityManager entityManager;
    entityManager.SpawnFirstEntities(screenWidth, screenHeight);
    WindowDimensions windowDimensions = { screenWidth, screenHeight };

    while (!WindowShouldClose()) 
    {
        EntityManager::CheckAllEntities(windowDimensions);
        EntityManager::UpdateEntities(screenWidth, screenHeight);

        BeginDrawing();
        ClearBackground(DARKBLUE);
        EntityManager::DrawEntities();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}