#pragma once
#include <memory>
#include <vector>
#include <raylib.h>
#include <raygui.h>
#include <iostream>

class Ball;
class Paddle;
class World;

class GameObjects
{
public:
	virtual void objInit() {}
	virtual void objUpdate() {}
	virtual void objDraw() {}
	virtual void objUnloadTex() {}

	virtual ~GameObjects() = default;
};

class World
{
	std::vector<std::unique_ptr<GameObjects>> objs;


public:

	World(int w, int h, const char* title)
	{
		//=window init
		InitWindow(w, h, title);

		//===gui init
		GuiLoadStyle("dark/dark.rgs");
		GuiSetStyle(DEFAULT, TEXT_SIZE, 30);

		//=====game objs init
		initAll();

		//call functions requiring glcontext
	}

	void initAll() const
	{
		for (const auto& intiti : objs)
		{
			intiti->objInit();
		}
	}
	void updateAll() const
	{
		for (const auto& intiti : objs)
		{
			intiti->objUpdate();
		}
	}
	void drawAll() const
	{
		for (const auto& intiti : objs)
		{
			intiti->objDraw();
		}
	}
	void unloadTexAll() const
	{
		for (const auto& intiti : objs)
		{
			intiti->objUnloadTex();
		}
	}

	template <typename T, typename... TArgs>
	T& addObject(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		std::unique_ptr<GameObjects> uPtr{ c };
		objs.emplace_back(std::move(uPtr));

		//c->objInit();

		return *c;
	}


};

