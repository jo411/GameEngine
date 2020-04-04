#pragma once
#include "../GameObject.h"
#include "../SmartPointer.h"
class CollisionHandler
{
public:
	static bool SweptSeparatingAxisCollisionCheck(SmartPointer<GameObject> A, SmartPointer<GameObject> B,float deltaTime );

private:
	static bool staticCollisionCheck(SmartPointer<GameObject> A, SmartPointer<GameObject> B);//Check if A collides with B in B's coordinate system. 
};

