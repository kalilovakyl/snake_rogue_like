#include "raylib.h"
#include <stdio.h>

typedef struct {
    int w;
    int h;
} Screen;

typedef struct {
	float x;
	float y;
	float speed;
	int width;
	Color color;
} Player;

void input_handling(Player *p1, float dt, Screen srn); 

int main(void) {
    Screen srn;

    InitWindow(800, 450, "snake_game");

    int monitor = GetCurrentMonitor();
    srn.w = GetMonitorWidth(monitor);
    srn.h = GetMonitorHeight(monitor);

    SetWindowSize(srn.w, srn.h);
    ToggleFullscreen();

    Player p1;
    p1.x = 0;
    p1.y = 0;
    p1.width = 40;
    p1.speed = 800.0f;
    p1.color = WHITE;
    
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
	    float dt = GetFrameTime();
	    input_handling(&p1, dt, srn);

        BeginDrawing();
        ClearBackground(BLACK);

	    DrawRectangle(p1.x, p1.y, p1.width, p1.width, p1.color);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void input_handling(Player *p1, float dt, Screen srn) {
  float fatness_w = srn.w - p1->width;
  float fatness_y = srn.h - p1->width;

  if (p1->x >= 0 && p1->x <= fatness_w && p1->y >= 0 && p1->y <= fatness_y) {
      if (IsKeyDown(KEY_D)) p1->x += p1->speed * dt;
      if (IsKeyDown(KEY_A)) p1->x -= p1->speed * dt;
      if (IsKeyDown(KEY_W)) p1->y -= p1->speed * dt;
      if (IsKeyDown(KEY_S)) p1->y += p1->speed * dt;
  } else {
	if (p1->x < 0) p1->x = 0;
	if (p1->x > fatness_w) p1->x = fatness_w;
	if (p1->y < 0) p1->y = 0;
	if (p1->y > fatness_y) p1->y = fatness_y;
  }
}


