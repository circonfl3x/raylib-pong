#include <raylib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <stdbool.h>
#include <math.h>
#define WIDTH 640 //width is 640px
#define HEIGHT 480 //height is 480px


//define structs
struct player
{
	int x,y; 
	int w = 20;
	int h = 70;
	int score = 0;
};

struct ball
{
	float x,y,bx,by; //movement variables bx and by are updated as fractional numbers so they are declared as floats in this instance
	int w = 15;
	int h = 15;
};
/////////////////////////////////////////////////////////////////////////

//define functions
const char * intTochar(int a);
bool checkCollision(int x1,int x2, int y1, int y2, int w1, int w2, int h1, int h2);
/////////////////////////////////////////////////////////////////////////////////////

int main(void)
{

	struct player ply;
	ply.x = 20; // player initial x position
	ply.y = 100; //player initial y position

	struct player cpu;
	cpu.x = WIDTH-35; // cpu initial x position
	cpu.y = 100; // cpu initial y position

	struct ball b;
	b.x = (WIDTH/2) - b.w; //ball initial x position
	b.y = 120; //ball inital y position
	b.bx = -5; //ball initial x velocity
	b.by = -5; //ball initial y velocity


	

	InitWindow(WIDTH, HEIGHT, "Ping pong"); //Make a window with a resolution of 640x480 and the title "ping pong"
	SetTargetFPS(60); //our preferred frames is 60 or a frame every 16.667 ms

	do
	{
		
		BeginDrawing();
		ClearBackground(BLACK); //draw the color black on the background.
		DrawRectangle(0,0,(WIDTH/2), HEIGHT, BLACK);
		DrawRectangle((WIDTH/2), 0, (WIDTH/2), HEIGHT, WHITE);
		DrawRectangle(ply.x,ply.y,ply.w,ply.h,WHITE); //Draw a rectangle using variables from the struct "ply"
		DrawRectangle(cpu.x,cpu.y,cpu.w,cpu.h,BLACK); //Draw a rectangle using variables from the struct "cpu"
		DrawText( intTochar(ply.score), (WIDTH/2) - 200, 30, 48, WHITE); //write player's score onto screen
		DrawText(intTochar(cpu.score), (WIDTH/2) + 200, 30, 48, BLACK); //write cpu's score onto screen
		
		if(checkCollision(ply.x, b.x, ply.y, b.y, ply.w, b.w, ply.h, b.h) || checkCollision(cpu.x, b.x, cpu.y, b.y, cpu.w, b.w, cpu.h, b.h))
		{
			 b.bx = -1 * b.bx; //if collision with ball and player is true, multiply -1 to reverse the ball's trajectory
		}

		cpu.y = b.y ; //cpu's y position is always equal to the ball's y position

		


		if (b.x < (WIDTH/2) ) DrawRectangle(b.x,b.y,b.w,b.h,WHITE); //draw a rectangle using variables from struct "b"
		else DrawRectangle(b.x,b.y,b.w,b.h,BLACK);
		EndDrawing();

		//updateBall(ply, b);
		b.x += b.bx; //add onto ball x using bx every frame loop
		b.y += b.by; //add onto ball y using by every frame loop

		

		if(b.x < 5)
		{
			//this code is ran if the CPU scores the player

			cpu.score ++; //increment CPU's score
			b.x = (WIDTH/2) - b.w; //restore ball's x position
			b.y = 120; //restore ball's y position
			b.bx = -5; //change ball's directiom to go towards the player
			
		}else if(b.x > WIDTH - 5)
		{
			//this code is ran if the player scores the CPU

			ply.score ++; //increment player's score
			b.x = (WIDTH/2) - b.w; //restore ball's x position
			b.y = 120; //restore ball's y position
			b.bx = 5; //change ball's directiom to go towards the CPU
		}
		if(b.y < 5)
		{
			//this code is ran if the ball hits the top of the frame

			b.by = -1 * b.by; //multiply the negative integer "b.by" by -1 to reverse ball movement
		}else if(b.y > HEIGHT - 5)
		{
			b.by = -(b.by); //add a negative sign to the negative integer "b.by" to reverse ball movement
		}
		

		if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
		{
			//this code is ran if the key W is held down or the key arrow up is held down
			
			if(ply.y < 5) ; //if the player's y position is at the top of the frame, no command is ran 
			else ply.y -= 5; //else the player's position is decremented by 5 moving the player upwards
		}else if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
		{
			//this code is ran if the key S is held down or the key arrow down is held down
			if(ply.y > (HEIGHT-ply.h)) ; // if the player's y position is at the bottom of the frame, no command is ran
			else ply.y += 5; //else the player's position is incremented by 5 moving the player downwards
		}
	}while(!WindowShouldClose());

	CloseWindow(); //destroy window

	return 0;
}


const char* intTochar(int a)
{
	//this function converts an integer into a string, needed to convert our player's scores before printing out
	std::stringstream ss;
	ss << a;
	std::string str;
	ss >> str;

	return str.c_str();
}

bool checkCollision(int x1,int x2, int y1, int y2, int w1, int w2, int h1, int h2)
{
	//this function checks for collision between 2 objects given their x,y,width and height
	if (x1 <= x2 + w2 && y1 <= y2 + h2 &&
		x2 <= x1 + w1 && y2 <= y1 + h1)
		{
			return true; //if x1 is less than or equal to x2 + width2 and y1 is less than or equal to y2 + height2 and so on... the boolean returns true
		}
	else return false; //else false is returned
}





