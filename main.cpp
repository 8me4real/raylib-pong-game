#include <raylib.h>

int playerscore = 0;
int cpuscore = 0;

class Ball
{
public:
	float x, y, speed_x, speed_y, radius;
	
	void Reset() {
		if (x >= GetScreenWidth())
		{
			x = GetScreenWidth() / 2;
			y = GetScreenHeight() / 2;
			cpuscore++;
		}
		if (x <= 0)
		{
			x = GetScreenWidth() / 2;
			y = GetScreenHeight() / 2;
			playerscore++;
		}
	}

	void Draw() 
	{
		DrawCircle(x, y, radius, BLUE);
	}

	void Move() 
	{
		Reset();
		x += speed_x;
		y += speed_y;
		if (y + radius >= GetScreenHeight() || y - radius <= 0) 
		{
			speed_y *= -1;
		}
		if (x >= GetScreenWidth() || x <= 0)
		{
			speed_x *= -1;
		}
	}
};

extern Ball ball;

class Kirpich
{
public:
	float x, y, speed, width, height;

	void Draw()
	{
		Rectangle evf = { x, y - height / 2, width, height};
		DrawRectangleRounded(evf, 1.3, 0, DARKBLUE);
	}

	void Move() 
	{
		if (IsKeyDown(KEY_UP) && y - height / 2 - 5 >= 0)
		{
			y -= speed;
		}
		if (IsKeyDown(KEY_DOWN) && y + height / 2 + 5 <= GetScreenHeight())
		{
			y += speed;
		}
	}
};

class CPU
{
public:
	float x, y, speed, width, height;

	void Draw()
	{
		Rectangle evf = { x, y - height / 2, width, height };
		DrawRectangleRounded(evf, 1.3, 0, DARKBLUE);
	}

	void Move()
	{
		if (ball.y <= y  && y - height / 2 - 5 >= 0)
		{
			y -= speed;
		}
		if (ball.y > y  && y + height / 2 + 5 <= GetScreenHeight())
		{
			y += speed;
		}
	}
};

Kirpich player;
CPU cpu;
Ball ball;

int main() {

	int screenwidth = 1280, screenheight = 800;
	InitWindow(screenwidth, screenheight, "pong");
	SetTargetFPS(70);

	player.x = screenwidth - 40;
	player.y = screenheight / 2;
	player.speed = 6;
	player.width = 20;
	player.height = 100;

	cpu.x = 20;
	cpu.y = screenheight / 2;
	cpu.speed = 6;
	cpu.width = 20;
	cpu.height = 100;

	ball.radius = 20;
	ball.x = screenwidth / 2;
	ball.y = screenheight / 2;
	ball.speed_x = 7;
	ball.speed_y = 7;

	while (!WindowShouldClose()) 
	{
		BeginDrawing();
		ClearBackground(ORANGE);
		DrawCircle(screenwidth / 2, screenheight / 2, 100, DARKBLUE);
		DrawLine(screenwidth / 2, 0, screenwidth / 2, screenheight, DARKBLUE);
		DrawCircle(screenwidth / 2, screenheight / 2, 99, ORANGE);

		ball.Move();
		ball.Draw();
		
		player.Move();
		player.Draw();

		cpu.Move();
		cpu.Draw();

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y - player.height / 2, player.width, player.height })) {
			ball.speed_x *= -1;
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpu.x, cpu.y - cpu.height / 2, cpu.width, cpu.height })) {
			ball.speed_x *= -1;
		}

		DrawText(TextFormat("%i",cpuscore), screenwidth / 4 - 20, 20, 80, BLUE);
		DrawText(TextFormat("%i", playerscore), screenwidth * 3 / 4 + 20, 20, 80, BLUE);

		EndDrawing();
	}
	CloseWindow();

}
