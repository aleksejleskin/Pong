#pragma once
#include "aMath.h"
#include <string>
#include "SDL.h"
#include "Object.h"
#include <vector>

using namespace aMath;
using namespace std;

struct Shape
{

};

struct ShapeCircle : Shape
{
	float radius;
	Vector2 position;
};

struct ShapeAABB : Shape
{
	Vector2 min;
	Vector2 max;
};

struct AABB 
{
	Vector2 min;
	Vector2 max;
};

struct Circle
{
	float radius;
	Vector2 position;
};

class Collision
{
public:
	Collision(void);
	~Collision(void);

	bool	AABBvsAABB(AABB a, AABB b );
	bool	CirclevsCircle(Circle a, Circle b );
	bool	CheckCollision(class Object a, class Object b);

protected:
};
