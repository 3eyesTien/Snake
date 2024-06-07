// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "raylib.h"
#include <deque>


Color neonBlue = { 0, 230, 255, 255 };
Color darkGreen = { 43, 51, 24, 255 };
Color cream = { 255, 243, 202, 255 };

int cellSize = 30;
int cellCount = 25; // Grid is 25cells x 25cells. 

class Snake
{
public:
    std::deque<Vector2> body = { Vector2{6,9}, Vector2{5, 9}, Vector2{4, 9} };

    void Draw()
    {
        for (int i = 0; i < body.size(); i++)
        {
            int x = body[i].x;
            int y = body[i].y;
            DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, darkGreen);
        }
    }
};

class Food {

public: 
    Vector2 position;
    Texture2D texture;

    Food()
    {
        Image image = LoadImage("Graphics/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos();
    }

    ~Food()
    {
        UnloadTexture(texture);
    }

    void Draw() {
        DrawTexture(texture, position.x * cellSize, position.y * cellSize, cream); // White means no color filter is being applied
    }

    Vector2 GenerateRandomPos()
    {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{ x, y };
    }
};

int main()
{
    std::cout << "Starting the game" << std::endl;
    InitWindow(cellSize * cellCount, cellSize * cellCount, "Snake");
    SetTargetFPS(60);
    Food food = Food();
    Snake snake = Snake();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        food.Draw();
        snake.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

/* Steps to do */
/*
* Create Blank Canvas and Game Loop - Done
* Create Food - Done
* Create Snake
* Move Snake
* Make Snake eat Food
* Make Snake grow longer
* Check for collisions with edges and tail
* Add title and frame
* Keep score
* Add sound effects

*/