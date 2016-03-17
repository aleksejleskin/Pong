#include "Collision.h"

using namespace std;
Collision::Collision(void)
{

}

Collision::~Collision(void)
{

}

//bool Collision::BoxvsBox(RigidBodyBox a, RigidBodyBox b )

	//// Exit with no intersection if found separated along an axis
	//if(a.max.x < b.min.x || a.min.x > b.max.x) 
	//{
	//	return false;
	//}
	//if(a.max.y < b.min.y || a.min.y > b.max.y) 
	//{
	//	return false;
	//}

	//// No separating axis found, therefor there is at least one overlapping axis
	//return true;


//bool Collision::CirclevsCircle(RigidBodyCircle a, RigidBodyCircle b )

	//float r = a.radius + b.radius;
	//	r *= r;

	//	if(r < (a.position.x + b.position.x) * (a.position.x + b.position.x) 
	//		+ (a.position.y + b.position.y) *(a.position.y + b.position.y) )
	//	{
	//		return true;
	//	}
	//	return false;


bool	Collision::CheckCollision(Object a, Object b)
{
	return false;
}