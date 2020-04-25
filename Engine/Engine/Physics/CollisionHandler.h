#pragma once
#include "../GameObject.h"
#include "../SmartPointer.h"

struct CollisionData
{
	SmartPointer<GameObject> A;
	SmartPointer<GameObject> B;
	Vector4 CollisionAxis;
	float cTime;
	bool didCollide;
};
struct CollisionTimesAndAxis;
class CollisionHandler
{
public:
	static CollisionData SweptSeparatingAxisCollisionCheck(SmartPointer<GameObject> A, SmartPointer<GameObject> B,const float deltaTime );
	static bool checkAllObjectsForCollision(const std::vector<SmartPointer<GameObject>>&collidables, const float& dt);
private:
	static bool staticCollisionCheck(SmartPointer<GameObject> A, SmartPointer<GameObject> B);//Check if A collides with B in B's coordinate system. No velocity interpolation
	static CollisionTimesAndAxis SweptAxisCollisionCheck(SmartPointer<GameObject> A, SmartPointer<GameObject> B, float deltaTime);//Check if A collides or did collide with B in B's coordinate system in the last frame time. Returns open and close times for the separations in the form: [tCloseX,tOpenX, tCloseY,tOpenY]
	static void resolveCollisionPosition(SmartPointer<GameObject> A, const float cTime);
};

