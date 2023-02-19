#pragma once


#include "ObjectsSystem.h"




class Ball : public GameObjects 
{
	Texture2D circle_{};
	float x_speed = 150.f, y_speed = 150.f;
	float x{}, y{};

	const Paddle* l_padd_ptr;
	const Paddle* r_padd_ptr;

	static bool drawn;

private:
	void CollisionToColliders();
	static void Interrupt();

public:
	void objInit() override;

	void objUpdate() override;

	void objDraw() override;

	void objUnloadTex() override;



public:
	Ball() = default;

	Ball(float ball_x, float ball_y, const Paddle* l_padd, const Paddle* r_padd)
		: x(ball_x), y(ball_y), l_padd_ptr(l_padd), r_padd_ptr(r_padd)
	{
	}

	explicit Ball(const Texture2D& srcTex) : circle_(srcTex), x(0.f), y(0.f), l_padd_ptr(nullptr), r_padd_ptr(nullptr) {}

	const Texture2D& getBallText() const { return circle_; }

};

struct Colliders
{
	Rectangle top_collider, mid_collider, bottom_collider;
};

class Paddle : public GameObjects 
{
	Texture2D rectangle_{};
	const float y_speed{250.f};
	float x{}, y{};
	char side{};

public:
	void objInit() override;

	void objUpdate() override;

	void objDraw() override;

	void objUnloadTex() override;


public:
	Paddle() = default;

	Paddle(float paddle_x, float paddle_y, char left_right)
	: x(paddle_x), y(paddle_y), side(left_right)
	{}

	explicit Paddle(const Texture2D& srcTex) : rectangle_(srcTex), x(0.f), y(0.f), side(0)
	{
	}

public:
	const Texture2D& getPaddleText() const { return rectangle_; }

	auto getPos() const { return Vector2{ x,y }; }

	Colliders colliders_{{}, {}, {}};
};

