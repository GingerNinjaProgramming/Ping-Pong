#include <iostream>
#include <algorithm>
#include <raylib.h>

using namespace std;

void InvertValue(int& value){
    value *= -1;
}

void Die(){
    cout << "You Died!" << endl;
}

bool CheckCollisionWithLightRightWalls(int ball_x, int ball_radius, int screen_width){
    if(ball_x + ball_radius >= screen_width || ball_x - ball_radius <= 0)
        return true;
    return false;
}

bool CheckCollisionWithRectangle(){
    return false;
}



int main () {
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    int ball_x = 100;
    int ball_y = 100;
    int ball_speed_x = 5;
    int ball_speed_y = 5;
    int ball_radius = 15;

    int Lpaddle_x = 10;
    int Lpaddle_y = SCREEN_HEIGHT / 2;

    int Rpaddle_x = SCREEN_WIDTH - 20;
    int Rpaddle_y = SCREEN_HEIGHT / 2;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){ 
        if(IsKeyDown(KEY_UP)) Rpaddle_y -= 10;
        if(IsKeyDown(KEY_DOWN)) Rpaddle_y += 10;

        if(IsKeyDown(KEY_W)) Lpaddle_y -= 10;
        if(IsKeyDown(KEY_S)) Lpaddle_y += 10;
        
        ball_x += ball_speed_x;
        ball_y += ball_speed_y;

        if(CheckCollisionWithLightRightWalls(ball_x, ball_radius, SCREEN_WIDTH))
        {
            Die();
        }

        if((ball_x + ball_radius >= Rpaddle_x && ball_x + ball_radius <= Rpaddle_x && ball_y + ball_radius >= Rpaddle_y && ball_y - ball_radius <= Rpaddle_y + 100))
        {
            InvertValue(ball_speed_x);
        }

        if(ball_y + ball_radius >= SCREEN_HEIGHT || ball_y - ball_radius <= 0)
        {
            InvertValue(ball_speed_y);
        }
        
        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircle(ball_x,ball_y,ball_radius, WHITE);
            DrawRectangle(Lpaddle_x, Lpaddle_y, 10, 100, RED);
            DrawRectangle(Rpaddle_x, Rpaddle_y, 10, 100, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
