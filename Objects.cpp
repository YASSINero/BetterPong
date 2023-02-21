#define RAYGUI_IMPLEMENTATION

#include "Objects.h"



void Ball::CollisionToColliders()
{
	const float circle_wid = circle_.width;
	const float circle_hei = circle_.height;
	const Rectangle ball_rect = { x,y, circle_wid, circle_hei };

	if (CheckCollisionRecs(ball_rect, l_padd_ptr->colliders_.mid_collider))
	{
		x = l_padd_ptr->getPos().x + l_padd_ptr->getPaddleText().width;
		x_speed *= -1.1f;
	}
	else if (CheckCollisionRecs(ball_rect,l_padd_ptr->colliders_.top_collider))
	{
		x = l_padd_ptr->getPos().x + l_padd_ptr->getPaddleText().width;

		x_speed *= -1.2f;
		y_speed *= y_speed < 0 ? 1.2f : -1.2f;
	}
	else if (CheckCollisionRecs(ball_rect, l_padd_ptr->colliders_.bottom_collider))
	{
		x = l_padd_ptr->getPos().x + l_padd_ptr->getPaddleText().width;

		x_speed *= -1.2f;
		y_speed *= y_speed < 0 ? -1.2f : 1.2f;
	}

	//===============================R C o ll i d e r R======================

	if (CheckCollisionRecs(ball_rect, r_padd_ptr->colliders_.mid_collider))
	{
		x = r_padd_ptr->getPos().x - circle_wid;
		x_speed *= -1.1f;
	}
	else if (CheckCollisionRecs(ball_rect, r_padd_ptr->colliders_.top_collider))
	{
		x = r_padd_ptr->getPos().x - circle_wid;
		x_speed *= -1.2f;
		y_speed *= y_speed < 0 ? 1.2f : -1.2f;
	}
	else if (CheckCollisionRecs(ball_rect, r_padd_ptr->colliders_.bottom_collider))
	{
		x = r_padd_ptr->getPos().x - circle_wid;
		x_speed *= -1.2f;
		y_speed *= y_speed < 0 ? -1.2f : 1.2f;
	}

}


void Ball::objInit()
{


	Image ball_img = LoadImage("empty.png");
	ImageResize(&ball_img, 14, 14);

	for (int radius = 6; radius > 0; --radius)
	{
		ImageDrawCircle(&ball_img, 7, 7, radius, GREEN);
		
	}

	circle_ = LoadTextureFromImage(ball_img);
	
	x = circle_.width;
	y = 400 - circle_.height;

	UnloadImage(ball_img);
}

void Ball::objUpdate() 
{
	if (x < 0 || x > GetScreenWidth())
	{
		//todo Minimise use of literal values => (encapsulate gui values)
		if(GuiMessageBox({ GetScreenWidth()/2.f - 150.f, GetScreenHeight()/2.f - 100.f, 300, 200 }, "Ball out", "PONGERS!!", "restart") == 1)
		{
			x = GetScreenWidth() / 2;
			x_speed = y_speed = init_speed;
		}
			std::cout << "X Speed: " << x_speed << " || Y Speed: " << y_speed << '\n' << std::endl;
		return;
	}
	 
	CollisionToColliders();

	if (y > GetScreenHeight() - circle_.height)
	{
		x_speed += x_speed > init_speed * 2 ? GetRandomValue(-25, 25) : 5; //avoids same trajectory
		y = GetScreenHeight() - circle_.height;
		y_speed *= -1;
	}
	if (y < 0)
	{
		x_speed += x_speed > init_speed * 2 ? GetRandomValue(-25, 25) : 5; //avoids same trajectory
		y = 0;
		y_speed *= -1;
	}
	

	x += x_speed * GetFrameTime();
	y += y_speed * GetFrameTime();

}

void Ball::objDraw()
{
	DrawTexture(circle_, x, y, WHITE);
}

void Ball::objUnloadTex()
{
	UnloadTexture(circle_);
}


void Paddle::objInit()
{
	Image padd_img = LoadImage("empty.png");
	ImageResize(&padd_img, 20, 150);
	
	ImageDrawRectangleV(&padd_img, { 0, 0 }, { 20, 50 }, MAROON);
	ImageDrawRectangleV(&padd_img, { 0, 50 }, { 20, 50 }, BEIGE);
	ImageDrawRectangleV(&padd_img, { 0, 100 }, { 20, 50 }, GOLD);

	rectangle_ = LoadTextureFromImage(padd_img);

	colliders_ = { {x,y, static_cast<float>(rectangle_.width), static_cast<float>(rectangle_.height)/3},
	{x,y + static_cast<float>(rectangle_.height) / 3, static_cast<float>(rectangle_.width), static_cast<float>(rectangle_.height) / 3},
	{x,y + (2 * (static_cast<float>(rectangle_.height) / 3)), static_cast<float>(rectangle_.width), static_cast<float>(rectangle_.height) / 3} };

	UnloadImage(padd_img);
}

void Paddle::objUpdate() 
{

	if(side == 'r' || side == 'R')
	{
		if (IsKeyDown(KEY_DOWN) && y < static_cast<float>( GetScreenHeight() - rectangle_.height ))
		{
			y += y_speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_UP) && y > 0)
		{
			y -= y_speed * GetFrameTime();
		}
	}
	if(side == 'l' || side == 'L')
	{
		if (IsKeyDown(KEY_S) && y < static_cast<float>(GetScreenHeight() - rectangle_.height))
		{
			y += y_speed * GetFrameTime();
		}
		if ((IsKeyDown(KEY_Z) || IsKeyDown(KEY_W)) && y > 0)
		{
			y -= y_speed * GetFrameTime();
		}
	}

	colliders_ = { {x,y, static_cast<float>(rectangle_.width), static_cast<float>(rectangle_.height) / 3},
	{x,y + static_cast<float>(rectangle_.height) / 3, static_cast<float>(rectangle_.width), static_cast<float>(rectangle_.height) / 3},
	{x,y + 2 * (static_cast<float>(rectangle_.height) / 3), static_cast<float>(rectangle_.width), static_cast<float>(rectangle_.height) / 3} };
}



void Paddle::objDraw()
{
	DrawTexture(rectangle_, x, y, WHITE);

}

void Paddle::objUnloadTex()
{
	UnloadTexture(rectangle_);
}
