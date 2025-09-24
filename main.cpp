#include <iostream>
#include <algorithm>
#include <raylib.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int ball_x = 800 / 2;
int ball_y = 600 / 2;
int ball_speed_x = 5;
int ball_speed_y = 5;
int ball_radius = 15;

int Lpaddle_x = 20;
int Lpaddle_y = SCREEN_HEIGHT / 2;

int Rpaddle_x = SCREEN_WIDTH - 20;
int Rpaddle_y = SCREEN_HEIGHT / 2;

bool game_over = false;

int LScore = 0;
int RScore = 0;

int ScoreFontSize = 30;
int RestartFontSize = 20;

void InvertValue(int& value){
    value *= -1;
}

void Restart(){
    game_over = false;

    LScore = 0;
    RScore = 0;

    ball_x = 800 / 2;
    ball_y = 600 / 2;
    
    Lpaddle_x = 20;
    Lpaddle_y = SCREEN_HEIGHT / 2;

    Rpaddle_x = SCREEN_WIDTH - 20;
    Rpaddle_y = SCREEN_HEIGHT / 2;

}

bool CheckCollisionWithLightRightWalls(int ball_x, int ball_radius, int screen_width){
    if(ball_x + ball_radius >= screen_width || ball_x - ball_radius <= 0)
        return true;
    return false;
}

bool CheckCollisionWithRectangle(){
    return false;
}

int Clamp(int value, int min, int max){
    return std::max(min, std::min(value, max));
}



int main () {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){ 
        if(IsKeyDown(KEY_UP)) Rpaddle_y -= 10;
        if(IsKeyDown(KEY_DOWN)) Rpaddle_y += 10;

        if(IsKeyDown(KEY_W)) Lpaddle_y -= 10;
        if(IsKeyDown(KEY_S)) Lpaddle_y += 10;

        if(game_over && IsKeyDown(KEY_R)) Restart();
        
        ball_x += ball_speed_x;
        ball_y += ball_speed_y;

        if(CheckCollisionWithLightRightWalls(ball_x, ball_radius, SCREEN_WIDTH))
        {
            game_over = true;
        }
        
        if(game_over != true){

            if(ball_x >= Rpaddle_x - 10 && (ball_y <= Rpaddle_y + (100 / 2) && ball_y >= Rpaddle_y - (100 / 2))){
                ball_speed_x = Clamp(ball_speed_x + 1, -15, 15);
                ball_speed_y = Clamp(ball_speed_y + 1, -15, 15);
                InvertValue(ball_speed_x);
                RScore++;
            }

            if(ball_x <= Lpaddle_x + 10 && (ball_y <= Lpaddle_y + (100 / 2) && ball_y >= Lpaddle_y - (100 / 2))){
                ball_speed_x = Clamp(ball_speed_x + 1, -15, 15);
                ball_speed_y = Clamp(ball_speed_y + 1, -15, 15);
                InvertValue(ball_speed_x);
                LScore++;
                
            }

            if(ball_y + ball_radius >= SCREEN_HEIGHT || ball_y - ball_radius <= 0)
            {
                InvertValue(ball_speed_y);
            }
        }

        string winner;
        if(LScore > RScore){
            winner = "Left Player Wins!";
        }else if(RScore > LScore){
            winner = "Right Player Wins!";
        }else{
            winner = "It's a Tie!";
        }

        string game_over_text = "GAME OVER : " + winner;

        int GAME_OVER_TEXT_SIZE = MeasureText(game_over_text.c_str(), 40);
        int SCORE_TEXT_SIZE = MeasureText(("Score: " + to_string(LScore) + " - " + to_string(RScore)).c_str(), ScoreFontSize);
        int RESTART_TEXT_SIZE = MeasureText("Press R to Restart", RestartFontSize);
        
        int GameOverX = (SCREEN_WIDTH - GAME_OVER_TEXT_SIZE - 10) / 2;
        int ScoreX = (SCREEN_WIDTH - SCORE_TEXT_SIZE) / 2;
        int RestartX = (SCREEN_WIDTH - RESTART_TEXT_SIZE) / 2;

        int GameOverY = (SCREEN_HEIGHT - 40) / 2;
        int ScoreY = GameOverY - ScoreFontSize;
        int RestartY = (GameOverY + RestartFontSize) + 20;
        
    
        BeginDrawing();
        if(game_over){
            ClearBackground(BLACK);
            DrawText(game_over_text.c_str(), GameOverX, GameOverY, 40, RED);
            DrawText(("Score: " + to_string(LScore) + " - " + to_string(RScore)).c_str(), ScoreX, ScoreY, ScoreFontSize, GREEN);
            DrawText("Press R to Restart", RestartX, RestartY, RestartFontSize, GREEN);
        }
        else{
            ClearBackground(BLACK);
            DrawCircle(ball_x,ball_y,ball_radius, WHITE);
            DrawRectangle(Lpaddle_x, Lpaddle_y, 10, 100, RED);
            DrawRectangle(Rpaddle_x, Rpaddle_y, 10, 100, RED);
            DrawRectangle(SCREEN_WIDTH / 2 - 5, 0, 10, SCREEN_HEIGHT, GRAY);
            DrawText(to_string(LScore).c_str(), 10 , 10 , 50, GREEN);
            DrawText(to_string(RScore).c_str(), SCREEN_WIDTH - 30 , 10 , 50, GREEN);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
