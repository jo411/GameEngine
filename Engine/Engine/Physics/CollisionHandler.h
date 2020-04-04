#pragma once
#include "../GameObject.h"
#include "../SmartPointer.h"

struct AxisSeparationTimes
{

};
class CollisionHandler
{
public:
	static bool SweptSeparatingAxisCollisionCheck(SmartPointer<GameObject> A, SmartPointer<GameObject> B,float deltaTime );

private:
	static bool staticCollisionCheck(SmartPointer<GameObject> A, SmartPointer<GameObject> B);//Check if A collides with B in B's coordinate system. No velocity interpolation
	static std::array<float,4> SweptAxisCollisionCheck(SmartPointer<GameObject> A, SmartPointer<GameObject> B, float deltaTime);//Check if A collides or did collide with B in B's coordinate system in the last frame time. Returns open and close times for the separations in the form: [tCloseX,tOpenX, tCloseY,tOpenY]
};

