#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>

const int st_pt_x = 0;
const int st_pt_y = 200;

typedef struct {
    int w;
    int h;
} Screen;

typedef struct {
	float x;
	float y;
	float speed;
	int width;
    bool move_right; // used for moving enemy function 
    bool move_up; // used for moving enemy function 
	Color color;
} Player;

void input_handling(Player *p1, float dt, Screen srn); 
void enemy_move(Player *p1, float dt, Screen srn); 

int main(void) {
    Screen srn;

    InitWindow(800, 450, "snake_game");

    int monitor = GetCurrentMonitor();
    srn.w = GetMonitorWidth(monitor);
    srn.h = GetMonitorHeight(monitor);

    SetWindowSize(srn.w, srn.h);
    ToggleFullscreen();

    Player p1;
    p1.x = st_pt_x;
    p1.y = st_pt_y;
    p1.width = 40;
    p1.speed = 800.0f;
    p1.color = WHITE;

    Player enemy;
    enemy.x = srn.w;
    enemy.y = st_pt_y; 
    enemy.width = 40;
    enemy.speed = 400.0f;
    enemy.color = RED;
    enemy.move_right = true;
    enemy.move_up = true;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
	    float dt = GetFrameTime();
	    input_handling(&p1, dt, srn);
        enemy_move(&enemy, dt, srn);

        BeginDrawing();
        ClearBackground(BLACK);
        
        int thickness = 20;
        DrawLineEx((Vector2){ st_pt_x - thickness, st_pt_y - thickness }, (Vector2){ srn.w, st_pt_y - thickness }, thickness, BLUE);

	    DrawRectangle(p1.x, p1.y, p1.width, p1.width, p1.color);
	    DrawRectangle(enemy.x, enemy.y, enemy.width, enemy.width, enemy.color);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void input_handling(Player *p1, float dt, Screen srn) {
  float fatness_w = srn.w - p1->width;
  float fatness_y = srn.h - p1->width;

  if (p1->x >= st_pt_x && p1->x <= fatness_w && p1->y >= st_pt_y && p1->y <= fatness_y) {
      if (IsKeyDown(KEY_D)) p1->x += p1->speed * dt;
      if (IsKeyDown(KEY_A)) p1->x -= p1->speed * dt;
      if (IsKeyDown(KEY_W)) p1->y -= p1->speed * dt;
      if (IsKeyDown(KEY_S)) p1->y += p1->speed * dt;
  } else {
	if (p1->x < st_pt_x) p1->x = st_pt_x;
	if (p1->x > fatness_w) p1->x = fatness_w;
	if (p1->y < st_pt_y) p1->y = st_pt_y;
	if (p1->y > fatness_y) p1->y = fatness_y;
  }
}

void enemy_move(Player *p1, float dt, Screen srn) {
  float fatness_w = srn.w - p1->width;
  float fatness_y = srn.h - p1->width;

  if (p1->x >= st_pt_x && p1->x <= fatness_w && p1->y >= st_pt_y && p1->y <= fatness_y) {
      if (p1->move_right) {
        p1->x += p1->speed * dt;
      } else {
        p1->x -= p1->speed * dt;
      }
      if (p1->move_up) {
        p1->y -= p1->speed * dt;
      } else {
        p1->y += p1->speed * dt;
      }
  } else {
        if (p1->x < st_pt_x) {
            p1->x = st_pt_x;
            p1->move_right = true;
        }
        if (p1->x > fatness_w) {
            p1->x = fatness_w;
            p1->move_right = false;
        }
        if (p1->y < st_pt_y) {
            p1->y = st_pt_y;
            p1->move_up = false;
        }
        if (p1->y > fatness_y) {
            p1->y = fatness_y;
            p1->move_up = true;
        }
  }
}
