// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "raylib.h"
#include <deque>
#include <raymath.h>

Color neonBlue = { 0, 230, 255, 255 };
Color darkGreen = { 43, 51, 24, 255 };
Color cream = { 255, 243, 202, 255 };

int cellSize = 30;
int cellCount = 25; // Grid is 25cells x 25cells. 

double lastUpdateTime = 0;

// Method to check if it's time to update the snake movement otherwise
// the snake updates 60 times per second/along with the framerate
bool eventTriggered(double interval) 
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }

    return false;
}

class Snake
{
public:
    std::deque<Vector2> body = { Vector2{6,9}, Vector2{5, 9}, Vector2{4, 9} };
    Vector2 direction = { 1, 0 };

    void Draw()
    {
        for (unsigned int i = 0; i < body.size(); i++)
        {
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{ x * cellSize, y * cellSize, (float)cellSize, (float)cellSize };
            DrawRectangleRounded(segment, 0.5, 6, neonBlue);
        }
    }

    void Update()
    {
        body.pop_back();
        body.push_front(Vector2Add(body[0], direction));
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
        DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE); // White means no color filter is being applied
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

        if (eventTriggered(0.2))
        {
            snake.Update();
        }

        ClearBackground(cream);
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
* Create Snake - Done
* Move Snake
* Make Snake eat Food
* Make Snake grow longer
* Check for collisions with edges and tail
* Add title and frame
* Keep score
* Add sound effects

*/